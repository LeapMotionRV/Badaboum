#include "Renderer.h"
#include "Window.h"
namespace render
{
	Renderer::Renderer(const unsigned int width, const unsigned int height)
	{
		//set the openGL context
		setBounds(0, 0, width, height);
		m_openGLContext.setRenderer(this);
		m_openGLContext.setComponentPaintingEnabled(true);
		m_openGLContext.attachTo(*this);
		setWantsKeyboardFocus(true);
		m_bPaused = false;
		initColors();
		resetCamera();
		m_pSkybox = new Skybox("../data/skybox.png");

		//set var for Leap Motion
		m_fLastUpdateTimeSeconds = Time::highResolutionTicksToSeconds(Time::getHighResolutionTicks());
		m_fLastRenderTimeSeconds = m_fLastUpdateTimeSeconds;
		m_fFrameScale = 0.0075f;
		m_mtxFrameTransform.origin = Leap::Vector( 0.0f, -2.0f, 0.5f );
		m_fPointableRadius = 0.05f;

		//add the listener to the controller (Leap Motion)
		BadaboumWindow::getController().addListener(*this);

		//set var for the help
		m_bShowHelp = false;
		m_strHelp = "ESC - quit\n"
					"h - Toggle help and frame rate display\n"
					"p - Toggle pause\n"
					"Mouse Drag  - Rotate camera\n"
					"Mouse Wheel - Zoom camera\n"
					"Arrow Keys  - Rotate camera\n"
					"Space       - Reset camera";
		m_strPrompt = "Press 'h' for help";
	}

	Renderer::~Renderer()
	{
		BadaboumWindow::getController().removeListener(*this);
		m_openGLContext.detach();

		delete m_pSkybox;
	}

	void Renderer::newOpenGLContextCreated()
	{
		glEnable(GL_BLEND);
		glEnable(GL_DEPTH_TEST);//added by us
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		glFrontFace(GL_CCW);

		glEnable(GL_DEPTH_TEST);
		glDepthMask(true);
		glDepthFunc(GL_LESS);

		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
		glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
		glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
		glEnable(GL_COLOR_MATERIAL);
		glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
		glShadeModel(GL_SMOOTH);

		glEnable(GL_LIGHTING);

		m_fixedFont = Font("Courier New", 24, Font::plain );
	}

	void Renderer::openGLContextClosing()
	{
	}

	void Renderer::renderOpenGL()
	{
		{
			MessageManagerLock mm (Thread::getCurrentThread());
			if (! mm.lockWasGained())
				return;
		}

		//calculations for Leap Motion
		Leap::Frame frame = m_lastFrame;
		double  curSysTimeSeconds = Time::highResolutionTicksToSeconds(Time::getHighResolutionTicks());
		float   fRenderDT = static_cast<float>(curSysTimeSeconds - m_fLastRenderTimeSeconds);
		fRenderDT = m_avgRenderDeltaTime.AddSample( fRenderDT );
		m_fLastRenderTimeSeconds = curSysTimeSeconds;
		float fRenderFPS = (fRenderDT > 0) ? 1.0f/fRenderDT : 0.0f;
		m_strRenderFPS = String::formatted( "RenderFPS: %4.2f", fRenderFPS );

		// ******************** //
		//   Draw with OpenGL   //
		// ******************** //
		LeapUtilGL::GLMatrixScope sceneMatrixScope;
		setupScene();

		// draw skybox (with a texture)
		/*
		m_pSkybox->bind();
		m_pSkybox->draw();
		m_pSkybox->unbind();
		*/
		
		//draw axis
		LeapUtilGL::drawAxes();
		// draw the ground
		m_model.getGround()->draw();
		// draw particles
		//m_model.getParticuleManager()->drawParticles(m_particleRenderer);
		//draw cubes
		//m_model.getCube()->drawCube(m_model.getParticuleManager());

		m_model.getFlag()->getFlagParticles().drawParticles(m_particleRenderer);

		// draw fingers/tools as lines with sphere at the tip.
		drawPointables( frame );
		// draw the text overlay
		{
			ScopedLock renderLock(m_renderMutex);
			renderOpenGL2D();
		}

		// Physical simulation
		m_model.startSimulation(fRenderDT);
	}

	bool Renderer::keyPressed( const KeyPress& keyPress )
	{
		int iKeyCode = toupper(keyPress.getKeyCode());

		//ECHAP
		if ( iKeyCode == KeyPress::escapeKey )
		{
			JUCEApplication::quit();
			return true;
		}
		//UP
		if ( iKeyCode == KeyPress::upKey )
		{
			m_camera.RotateOrbit( 0, 0, LeapUtil::kfHalfPi * -0.05f );
			return true;
		}
		//DOWN
		if ( iKeyCode == KeyPress::downKey )
		{
			m_camera.RotateOrbit( 0, 0, LeapUtil::kfHalfPi * 0.05f );
			return true;
		}
		//LEFT
		if ( iKeyCode == KeyPress::leftKey )
		{
			m_camera.RotateOrbit( 0, LeapUtil::kfHalfPi * -0.05f, 0 );
			return true;
		}
		//RIGHT
		if ( iKeyCode == KeyPress::rightKey )
		{
			m_camera.RotateOrbit( 0, LeapUtil::kfHalfPi * 0.05f, 0 );
			return true;
		}
		//Caracters
		switch( iKeyCode )
		{
			case ' ':
				resetCamera();
				break;
			case 'H':
				m_bShowHelp = !m_bShowHelp;
				break;
			case 'P':
				m_bPaused = !m_bPaused;
				break;
			default:
				return false;
		}

		return true;
	}

	void Renderer::mouseDown (const MouseEvent& e)
	{
		m_camera.OnMouseDown( LeapUtil::FromVector2( e.getPosition() ) );
	}

	void Renderer::mouseDrag (const MouseEvent& e)
	{
		m_camera.OnMouseMoveOrbit( LeapUtil::FromVector2( e.getPosition() ) );
		m_openGLContext.triggerRepaint();
	}

	void Renderer::mouseWheelMove ( const MouseEvent& e, const MouseWheelDetails& wheel )
	{
		(void)e;
		m_camera.OnMouseWheel( wheel.deltaY );
		m_openGLContext.triggerRepaint();
	}

	void Renderer::resized()
	{
	}

	void Renderer::paint(Graphics&)
	{
	}

	void Renderer::renderOpenGL2D() 
	{
		LeapUtilGL::GLAttribScope attribScope( GL_ENABLE_BIT );

		// when enabled text draws poorly.
		glDisable(GL_CULL_FACE);

		ScopedPointer<LowLevelGraphicsContext> glRenderer (createOpenGLGraphicsContext (m_openGLContext, getWidth(), getHeight()));

		if (glRenderer != nullptr)
		{
			Graphics g(*glRenderer.get());

			int iMargin   = 10;
			int iFontSize = static_cast<int>(m_fixedFont.getHeight());
			int iLineStep = iFontSize + (iFontSize >> 2);
			int iBaseLine = 20;
			Font origFont = g.getCurrentFont();

			const Rectangle<int>& rectBounds = getBounds();

			if ( m_bShowHelp )
			{
				g.setColour( Colours::seagreen );
				g.setFont( static_cast<float>(iFontSize) );

				if ( !m_bPaused )
				{
					g.drawSingleLineText( m_strUpdateFPS, iMargin, iBaseLine );
				}

				g.drawSingleLineText( m_strRenderFPS, iMargin, iBaseLine + iLineStep );

				g.setFont( m_fixedFont );
				g.setColour( Colours::slateblue );

				g.drawMultiLineText(  m_strHelp,
										iMargin,
										iBaseLine + iLineStep * 3,
										rectBounds.getWidth() - iMargin*2 );
			}

			g.setFont( origFont );
			g.setFont( static_cast<float>(iFontSize) );

			g.setColour( Colours::salmon );
			g.drawMultiLineText(  m_strPrompt,
									iMargin,
									rectBounds.getBottom() - (iFontSize + iFontSize + iLineStep),
									rectBounds.getWidth()/4 );
		}
	}

	//
	// calculations that should only be done once per leap data frame but may be drawn many times should go here.
	//   
	void Renderer::update(Leap::Frame frame)
	{
		ScopedLock sceneLock(m_renderMutex);

		double curSysTimeSeconds = Time::highResolutionTicksToSeconds(Time::getHighResolutionTicks());

		float deltaTimeSeconds = static_cast<float>(curSysTimeSeconds - m_fLastUpdateTimeSeconds);
      
		m_fLastUpdateTimeSeconds = curSysTimeSeconds;
		float fUpdateDT = m_avgUpdateDeltaTime.AddSample( deltaTimeSeconds );
		float fUpdateFPS = (fUpdateDT > 0) ? 1.0f/fUpdateDT : 0.0f;
		m_strUpdateFPS = String::formatted( "UpdateFPS: %4.2f", fUpdateFPS );
	}

	// affects model view matrix. Needs to be inside a glPush/glPop matrix block!
	void Renderer::setupScene()
	{
		OpenGLHelpers::clear(Colours::black.withAlpha(1.0f));

		m_camera.SetAspectRatio( getWidth() / static_cast<float>(getHeight()) );
		m_camera.SetupGLProjection();
		m_camera.ResetGLView();

		// left, high, near - corner light
		LeapUtilGL::GLVector4fv vLight0Position( -3.0f, 3.0f, -3.0f, 1.0f );
		// right, near - side light
		LeapUtilGL::GLVector4fv vLight1Position(  3.0f, 0.0f, -1.5f, 1.0f );
		// near - head light
		LeapUtilGL::GLVector4fv vLight2Position( 0.0f, 0.0f,  -3.0f, 1.0f );

		/// JUCE turns off the depth test every frame when calling paint.
		glEnable(GL_DEPTH_TEST);
		glDepthMask(true);
		glDepthFunc(GL_LESS);

		glEnable(GL_BLEND);
		glEnable(GL_TEXTURE_2D);

		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, GLColor(Colours::darkgrey));

		glLightfv(GL_LIGHT0, GL_POSITION, vLight0Position);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, GLColor(Colour(0.5f, 0.40f, 0.40f, 1.0f)));
		glLightfv(GL_LIGHT0, GL_AMBIENT, GLColor(Colours::black));

		glLightfv(GL_LIGHT1, GL_POSITION, vLight1Position);
		glLightfv(GL_LIGHT1, GL_DIFFUSE, GLColor(Colour(0.0f, 0.0f, 0.25f, 1.0f)));
		glLightfv(GL_LIGHT1, GL_AMBIENT, GLColor(Colours::black));

		glLightfv(GL_LIGHT2, GL_POSITION, vLight2Position);
		glLightfv(GL_LIGHT2, GL_DIFFUSE, GLColor(Colour(0.15f, 0.15f, 0.15f, 1.0f)));
		glLightfv(GL_LIGHT2, GL_AMBIENT, GLColor(Colours::black));

		glEnable(GL_LIGHT0);
		glEnable(GL_LIGHT1);
		glEnable(GL_LIGHT2);

		m_camera.SetupGLView();
	}

	void Renderer::drawPointables( Leap::Frame frame )
	{
		LeapUtilGL::GLAttribScope colorScope( GL_CURRENT_BIT | GL_LINE_BIT );

		const Leap::PointableList& pointables = frame.pointables();

		const float fScale = m_fPointableRadius;

		glLineWidth( 3.0f );

		for ( size_t i = 0, e = pointables.count(); i < e; i++ )
		{
			const Leap::Pointable&  pointable   = pointables[i];
			Leap::Vector            vStartPos   = m_mtxFrameTransform.transformPoint( pointable.tipPosition() * m_fFrameScale );
			Leap::Vector            vEndPos     = m_mtxFrameTransform.transformDirection( pointable.direction() ) * -0.25f;
			const uint32_t          colorIndex  = static_cast<uint32_t>(pointable.id()) % kNumColors;

			glColor3fv( m_avColors[colorIndex].toFloatPointer() );

			{
				LeapUtilGL::GLMatrixScope matrixScope;

				glTranslatef( vStartPos.x, vStartPos.y, vStartPos.z );

				glBegin(GL_LINES);

				glVertex3f( 0, 0, 0 );
				glVertex3fv( vEndPos.toFloatPointer() );

				glEnd();

				glScalef( fScale, fScale, fScale );

				LeapUtilGL::drawArrow( LeapUtilGL::kAxis_X );
			}
		}
	}

	void Renderer::onInit(const Leap::Controller&) 
	{
	}

	void Renderer::onConnect(const Leap::Controller&) 
	{
	}

	void Renderer::onDisconnect(const Leap::Controller&) 
	{
	}

	void Renderer::onFrame(const Leap::Controller& controller)
	{
		if ( !m_bPaused )
		{
			Leap::Frame frame = controller.frame();
			update(frame);
			m_lastFrame = frame;
			m_openGLContext.triggerRepaint();
		}
	}

	void Renderer::resetCamera()
	{
		m_camera.SetOrbitTarget( Leap::Vector::zero() );
		m_camera.SetPOVLookAt( Leap::Vector( 0, 2, 4 ), m_camera.GetOrbitTarget() );
	}

	void Renderer::initColors()
	{
		float fMin      = 0.0f;
		float fMax      = 1.0f;
		float fNumSteps = static_cast<float>(pow( kNumColors, 1.0/3.0 ));
		float fStepSize = (fMax - fMin)/fNumSteps;
		float fR = fMin, fG = fMin, fB = fMin;

		for ( uint32_t i = 0; i < kNumColors; i++ )
		{
			m_avColors[i] = Leap::Vector( fR, fG, LeapUtil::Min(fB, fMax) );

			fR += fStepSize;

			if ( fR > fMax )
			{
				fR = fMin;
				fG += fStepSize;

				if ( fG > fMax )
				{
					fG = fMin;
					fB += fStepSize;
				}
			}
		}

		Random rng(0x13491349);

		for ( uint32_t i = 0; i < kNumColors; i++ )
		{
			uint32_t      uiRandIdx    = i + (rng.nextInt() % (kNumColors - i));
			Leap::Vector  vSwapTemp    = m_avColors[i];

			m_avColors[i]          = m_avColors[uiRandIdx];
			m_avColors[uiRandIdx]  = vSwapTemp;
		}
	}
}