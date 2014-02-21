#include "Renderer.h"
#include "WindowScreen.h"
#include "../old/SampleListener.h"
#include "../physical/forces/ConstantForce.h"

namespace render
{
	Renderer::Renderer(const unsigned int width, const unsigned int height)
	{
		//set var for Leap Motion
		m_fLastUpdateTimeSeconds = Time::highResolutionTicksToSeconds(Time::getHighResolutionTicks());
		m_fLastRenderTimeSeconds = m_fLastUpdateTimeSeconds;
		m_mtxFrameTransform = Leap::Matrix();
		m_fPointableRadius = 0.05f;

		//set the openGL context
		setBounds(0, 0, width, height);
		m_openGLContext.setRenderer(this);
		m_openGLContext.setComponentPaintingEnabled(true);
		m_openGLContext.attachTo(*this);
		setWantsKeyboardFocus(true);
		m_bPaused = false;
		m_fFrameScale = 0.0075f;
		initColors();
		resetCamera();
		resetScene();
		m_pSkybox = new Skybox("../data/skybox.png");

		//other renderer
		m_pRenderer2D = new Renderer2D(getWidth(), getHeight());
	}

	Renderer::~Renderer()
	{
		m_openGLContext.detach();

		delete m_pRenderer2D;
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

		ScopedLock sceneLock(m_renderMutex);

		//calculations for Leap Motion
		Leap::Frame	frame = m_lastFrame;
		double		curSysTimeSeconds = Time::highResolutionTicksToSeconds(Time::getHighResolutionTicks());
		float		fRenderDT = static_cast<float>(curSysTimeSeconds - m_fLastRenderTimeSeconds);
					fRenderDT =	m_avgRenderDeltaTime.AddSample( fRenderDT );
					m_fLastRenderTimeSeconds = curSysTimeSeconds;
		float		fRenderFPS = (fRenderDT > 0) ? 1.0f/fRenderDT : 0.0f;
		
		//update renderer2D
		m_pRenderer2D->setRenderFPS(fRenderFPS);
		m_pRenderer2D->setNbParticles(m_pModel->getParticuleManager()->getNbParticles());
		m_pRenderer2D->setHighestPosition(m_pModel->getParticuleManager()->getHighestPosition());

		// ******************** //
		//   Draw with OpenGL   //
		// ******************** //
		LeapUtilGL::GLMatrixScope sceneMatrixScope;
		setupScene();

		//draw axis
		LeapUtilGL::drawAxes();
		// draw the ground
		m_pModel->getGround()->draw();
		// draw particles
		m_pModel->getParticuleManager()->drawParticles(m_particleRenderer);
		m_pModel->getLinkManager()->drawLinks();
		// draw fingers/tools as lines with sphere at the tip.
		drawPointables( frame );
		// draw the text overlay
		m_pRenderer2D->renderOpenGL2D(&m_openGLContext, getBounds(), m_bPaused);
		
		// ******************** //
		//  Physical simulation //
		// ******************** //
		m_pModel->startSimulation(fRenderDT);
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
			//m_camera.RotateOrbit( 0, 0, LeapUtil::kfHalfPi * -0.05f );
			m_camera.Move(Leap::Vector(0.f, 0.2f, 0.f));
			return true;
		}
		//DOWN
		if ( iKeyCode == KeyPress::downKey )
		{
			//m_camera.RotateOrbit( 0, 0, LeapUtil::kfHalfPi * 0.05f );
			m_camera.Move(Leap::Vector(0.f, -0.2f, 0.f));
			return true;
		}
		//LEFT
		if ( iKeyCode == KeyPress::leftKey )
		{
			//m_camera.RotateOrbit( 0, LeapUtil::kfHalfPi * -0.05f, 0 );
			m_camera.Move(Leap::Vector(-0.2f, 0.f, 0.f));
			return true;
		}
		//RIGHT
		if ( iKeyCode == KeyPress::rightKey )
		{
			//m_camera.RotateOrbit( 0, LeapUtil::kfHalfPi * 0.05f, 0 );
			m_camera.Move(Leap::Vector(0.2f, 0.f, 0.f));
			return true;
		}
		//ESCAPE
		if ( iKeyCode == KeyPress::escapeKey )
		{
			m_bPaused = !m_bPaused;
			return true;
		}
		//Caracters
		switch( iKeyCode )
		{
			case ' ':
				m_bPaused = !m_bPaused;
				break;
			case 'R':
				resetCamera();
				resetScene();
				break;
			case 'H':
				m_pRenderer2D->isShowHelp(!m_pRenderer2D->isShowHelp());
				break;
			case 'P': //add a particle
				m_pModel->addRandomParticle(1);
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

		set3DTransformations();
	}

	void Renderer::drawPointables( Leap::Frame frame )
	{
		LeapUtilGL::GLAttribScope colorScope( GL_CURRENT_BIT | GL_LINE_BIT );
		const Leap::PointableList& pointables = frame.pointables();

		glLineWidth( 3.0f );

		for ( size_t i = 0, e = pointables.count(); i < e; i++ )
		{
			const Leap::Pointable&  pointable   = pointables[i];
			Leap::Vector            vStartPos   = m_mtxFrameTransform.transformPoint( pointable.tipPosition() * m_fFrameScale );
			Leap::Vector            vEndPos     = m_mtxFrameTransform.transformDirection( pointable.direction() ) * -0.25f; //why -0.25f ?
			const uint32_t          colorIndex  = static_cast<uint32_t>(pointable.id()) % kNumColors;

			glColor3fv( m_avColors[colorIndex].toFloatPointer() );
			{
				LeapUtilGL::GLMatrixScope matrixScope;
				//apply transformations to have the fingers at the center at any time
				glMultMatrixf(m_mtxTotalMotionRotation.rigidInverse().toArray4x4());
				glScalef(1/m_fTotalMotionScale, 1/m_fTotalMotionScale, 1/m_fTotalMotionScale);
				glTranslatef(-m_vTotalMotionTranslation.x, -m_vTotalMotionTranslation.y, -m_vTotalMotionTranslation.z);
				//apply transformations to see several fingers
				glTranslatef(vStartPos.x, vStartPos.y, vStartPos.z);

				glBegin(GL_LINES);
				glVertex3f( 0, 0, 0 );
				glVertex3fv( vEndPos.toFloatPointer() );
				glEnd();

				glScalef( m_fPointableRadius, m_fPointableRadius, m_fPointableRadius );

				LeapUtilGL::drawArrow( LeapUtilGL::kAxis_X );
			}
		}
	}

	void Renderer::resetCamera()
	{
		m_camera.SetOrbitTarget( Leap::Vector::zero() );
		m_camera.SetPOVLookAt( Leap::Vector( 0, 4, 10 ), m_camera.GetOrbitTarget() );
	}

	void Renderer::resetScene()
	{
		m_mtxTotalMotionRotation  = Leap::Matrix::identity();
        m_vTotalMotionTranslation = Leap::Vector::zero();
        m_fTotalMotionScale       = 1.0f;
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

	void Renderer::set3DTransformations(){
		//Set the 3D grid transformation matrix
        glMultMatrixf(m_mtxTotalMotionRotation.toArray4x4());
        glScalef(m_fTotalMotionScale, m_fTotalMotionScale, m_fTotalMotionScale);
        glTranslatef(m_vTotalMotionTranslation.x, m_vTotalMotionTranslation.y, m_vTotalMotionTranslation.z);
	}
}