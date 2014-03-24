#include "Renderer.h"
#include "WindowScreen.h"

namespace render
{
	Renderer::Renderer(const unsigned int width, const unsigned int height){
		//set var for Leap Motion
		m_fLastUpdateTimeSeconds = Time::highResolutionTicksToSeconds(Time::getHighResolutionTicks());
		m_fLastRenderTimeSeconds = m_fLastUpdateTimeSeconds;
		m_mtxFrameTransform = Leap::Matrix();

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
		m_pSkybox = new Skybox();

		//other renderer
		m_pRenderer2D = new Renderer2D(Component::getWidth(), Component::getHeight());
	}

	Renderer::~Renderer(){
		m_openGLContext.detach();

		delete m_pRenderer2D;
		delete m_pSkybox;
	}

	void Renderer::newOpenGLContextCreated(){
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


		//create textures
		m_pModel->getGround()->createTexture();
		m_pSkybox->createTexture();
	}

	void Renderer::openGLContextClosing(){
	}

	// affects model view matrix. Needs to be inside a glPush/glPop matrix block!
	void Renderer::setupScene(){
		OpenGLHelpers::clear(Colours::black.withAlpha(1.0f));

		m_camera.SetAspectRatio( Component::getWidth() / static_cast<float>( Component::getHeight()) );
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

	void Renderer::renderOpenGL(){
		{
			MessageManagerLock mm (Thread::getCurrentThread());
			if (! mm.lockWasGained())
				return;
		}

		// ************************* //
		//     Check game state      //
		// ************************* //
		if(m_pModel->isGameEnded()){
			m_pModel->reset();
		}

		// ******************** //
		//     Leap Motion      //
		// ******************** //
		Leap::Frame	frame = m_lastFrame;
		double	curSysTimeSeconds = Time::highResolutionTicksToSeconds(Time::getHighResolutionTicks());
		//compute updateFPS => leap motion
		float	fUpdateDT = static_cast<float>(curSysTimeSeconds - m_fLastUpdateTimeSeconds);
		fUpdateDT = m_avgUpdateDeltaTime.AddSample( fUpdateDT );
		float	fUpdateFPS = (fUpdateDT > 0) ? 1.0f/fUpdateDT : 0.0f;
		//compute renderFPS => rendering
		float	fRenderDT = static_cast<float>(curSysTimeSeconds - m_fLastRenderTimeSeconds);
		//compute physicsFPS => physics(time between each frame)
		float fPhysicsFPS = fRenderDT;
		fRenderDT =	m_avgRenderDeltaTime.AddSample(fRenderDT);
		m_fLastRenderTimeSeconds = curSysTimeSeconds;
		float	fRenderFPS = (fRenderDT > 0) ? 1.0f/fRenderDT : 0.0f;

		{
			//!!! lock sensitive data !!!
			juce::ScopedLock sceneLock(m_renderMutex);
			
			if(!isPaused()){
				setupScene();
				// ******************** //
				//   Draw OpenGL 3D     //
				// ******************** //
				glPushMatrix();
					//The skybox is only subjected to the same rotation as the scene (it is the same comportement as if you moved your camera)
					glMultMatrixf(m_mtxTotalMotionRotation.toArray4x4());
					m_pSkybox->draw(m_mtxTotalMotionRotation, m_vTotalMotionTranslation, m_fTotalMotionScale);
				glPopMatrix();
			
				//The scene is moreover subjected to translation and scale transformations : 
				glPushMatrix();
					glTranslatef(m_vTotalMotionTranslation.x, m_vTotalMotionTranslation.y, m_vTotalMotionTranslation.z);
					glMultMatrixf(m_mtxTotalMotionRotation.toArray4x4());
					glScalef(m_fTotalMotionScale, m_fTotalMotionScale, m_fTotalMotionScale);
					//draw the scene (ground, axes, particles and links)
					LeapUtilGL::drawAxes();
					m_pModel->getGround()->draw();
					m_pModel->getParticuleManager()->drawParticles();
					m_pModel->getLinkManager()->drawLinks();
				glPopMatrix();
				//Fingers are always drawn in the middle of our window they are not subjected to translation, rotation and scaled
				drawPointables(frame);

				// ******************** //
				//  Physical simulation //
				// ******************** //
				m_pModel->startSimulation(fPhysicsFPS);

				// ******************** //
				//   Draw 2D IN GAME    //
				// ******************** //
				m_pRenderer2D->setHumanAlive(m_pModel->getParticuleManager()->getNbPlayerParticles(), curSysTimeSeconds);
				m_pRenderer2D->render2DInGame(&m_openGLContext, getBounds());
			}

			if(m_pRenderer2D->isShowHelp()){
				// ******************** //
				//    Draw 2D HELP      //
				// ******************** //
				m_pRenderer2D->render2DHelp(&m_openGLContext);
			}

			if(m_pRenderer2D->isShowDebug()){
				// ******************** //
				//   Draw 2D DEBUG      //
				// ******************** //
				m_pRenderer2D->setUpdateFPS(fUpdateFPS);
				m_pRenderer2D->setRenderFPS(fRenderFPS);
				m_pRenderer2D->setPhysicsFPS(fPhysicsFPS);
				m_pRenderer2D->setNbParticles(m_pModel->getParticuleManager()->getNbPlayerParticles());
				m_pRenderer2D->setNbParticlesLeft(m_pModel->getNbMaxParticle()-m_pModel->getParticuleManager()->getNbPlayerParticles());
				m_pRenderer2D->setHighestPosition(m_pModel->getParticuleManager()->getHighestPosition());
				m_pRenderer2D->setGravity(m_pModel->getConstantForceArray()[0]->getForce());
				m_pRenderer2D->setRigidity(m_pModel->getLinkManager()->getRigidity());
				m_pRenderer2D->setBrake(m_pModel->getLinkManager()->getBrake());
				m_pRenderer2D->render2DDebug(&m_openGLContext, getBounds(), m_bPaused);
			}

			//draw the scene even if there is not Leap Motion
			if(!BadaboumWindow::getController().isConnected()) 
				m_openGLContext.triggerRepaint();
		}
	}

	void Renderer::resized(){
	}

	void Renderer::paint(Graphics&){
	}

	void Renderer::drawPointables(Leap::Frame frame){
		LeapUtilGL::GLAttribScope colorScope( GL_CURRENT_BIT | GL_LINE_BIT );
		const Leap::PointableList& pointables = frame.pointables();

		glLineWidth( 5.f );
		float pointableRadius = 0.05f;
		glColor3f(1, 1, 1);

		for (size_t i = 0, e = pointables.count(); i < e; i++){
			const Leap::Pointable&  pointable   = pointables[i];
			Leap::Vector            vStartPos   = m_mtxFrameTransform.transformPoint( pointable.tipPosition() * m_fFrameScale );
			Leap::Vector            vEndPos     = m_mtxFrameTransform.transformDirection( pointable.direction() ) * -0.25f; //why -0.25f ?

			LeapUtilGL::GLMatrixScope fingersScope;

			//draw fingers
			glTranslatef(vStartPos.x, vStartPos.y, vStartPos.z);
			glBegin(GL_LINES);
			glVertex3f( 0, 0, 0 );
			glVertex3fv( vEndPos.toFloatPointer() );
			glEnd();

			//draw end of fingers
			glScalef( pointableRadius, pointableRadius, pointableRadius );
			LeapUtilGL::drawSphere( LeapUtilGL::eStyle::kStyle_Solid, 15.f );
		}
	}

	void Renderer::resetCamera(){
		m_camera.SetOrbitTarget( Leap::Vector::zero() );
		m_camera.SetPOVLookAt( Leap::Vector( 0, 1, 10 ), m_camera.GetOrbitTarget() );
	}

	void Renderer::resetScene(){
		m_mtxTotalMotionRotation  = Leap::Matrix::identity();
		m_vTotalMotionTranslation = Leap::Vector::zero();
		m_fTotalMotionScale       = 1.0f;
	}

	void Renderer::initColors(){
		float fMin      = 0.0f;
		float fMax      = 1.0f;
		float fNumSteps = static_cast<float>(pow( kNumColors, 1.0/3.0 ));
		float fStepSize = (fMax - fMin)/fNumSteps;
		float fR = fMin, fG = fMin, fB = fMin;

		for ( uint32_t i = 0; i < kNumColors; i++ ){
			m_avColors[i] = Leap::Vector( fR, fG, LeapUtil::Min(fB, fMax) );

			fR += fStepSize;

			if ( fR > fMax ){
				fR = fMin;
				fG += fStepSize;

				if ( fG > fMax ){
					fG = fMin;
					fB += fStepSize;
				}
			}
		}

		juce::Random rng(0x13491349);

		for ( uint32_t i = 0; i < kNumColors; i++ ){
			uint32_t      uiRandIdx    = i + (rng.nextInt() % (kNumColors - i));
			Leap::Vector  vSwapTemp    = m_avColors[i];

			m_avColors[i]          = m_avColors[uiRandIdx];
			m_avColors[uiRandIdx]  = vSwapTemp;
		}
	}

	void Renderer::set3DTransformations(){
		//Set the 3D grid transformation matrix
		glTranslatef(m_vTotalMotionTranslation.x, m_vTotalMotionTranslation.y, m_vTotalMotionTranslation.z);
		glMultMatrixf(m_mtxTotalMotionRotation.toArray4x4());
		glScalef(m_fTotalMotionScale, m_fTotalMotionScale, m_fTotalMotionScale);
	}
}