#ifndef RENDERER_H
#define RENDERER_H

#include <JuceHeader.h>
#include <Leap.h>

#include "Skybox.h"
#include "Renderer2D.h"
#include "../physical/Model.h"

namespace render
{
	// intermediate class for convenient conversion from JUCE color
	// to float vector argument passed to GL functions
	struct GLColor 
	{
		GLfloat r, g, b, a; 

		GLColor() : r(1), g(1), b(1), a(1) {}

		GLColor( float _r, float _g, float _b, float _a=1 ):r(_r), g(_g), b(_b), a(_a)
		{}

		explicit GLColor(const juce::Colour& juceColor) 
		: r(juceColor.getFloatRed()), 
			g(juceColor.getFloatGreen()),
			b(juceColor.getFloatBlue()),
			a(juceColor.getFloatAlpha())
		{}

		operator const GLfloat*() const 
		{
			return &r;
		}
	};

	/**
		This component is contained in the MainComponent. This is where we display all frame of openGL.
	*/
	class Renderer : public juce::Component, public juce::OpenGLRenderer
	{
	public:
		//alloc and desacolloc the openGL context
		Renderer(const unsigned int width, const unsigned int height);
		~Renderer();

		//getters
		Leap::Frame						getLastFrame() const {return m_lastFrame;}
		bool							isPaused() const {return m_bPaused;}
		juce::OpenGLContext*			getOpenGLContext() const {return const_cast<juce::OpenGLContext*>(&m_openGLContext);}
		const juce::CriticalSection*	getRenderMutex() const {return &m_renderMutex;}
		double							getLastUpdateTimeSeconds() const {return m_fLastUpdateTimeSeconds;}
		LeapUtil::RollingAverage<>		getAvgUpdateDeltaTime() const {return m_avgUpdateDeltaTime;}
		Renderer2D*						getRenderer2D() const {return m_pRenderer2D;}
		physical::Model*				getModel() const {return m_pModel;}
		Leap::Matrix					getTotalMotionRotation() const {return m_mtxTotalMotionRotation;}
		Leap::Vector					getTotalMotionTranslation() const {return m_vTotalMotionTranslation;}
		float							getTotalMotionScale() const {return m_fTotalMotionScale;}
		float							getFrameScale() const {return m_fFrameScale;}
		//setters
		void							isPaused(bool flag) {m_bPaused = flag;}
		void							setModel(physical::Model* newModel) {m_pModel = newModel;}
		void							setLastFrame(Leap::Frame lastFrame) {m_lastFrame = lastFrame;}
		void							setLastUpdateTimeSeconds(double lastUpdateTimeSeconds) {m_fLastUpdateTimeSeconds = lastUpdateTimeSeconds;}
		void							setTotalMotionRotation(Leap::Matrix rotation) {m_mtxTotalMotionRotation = rotation;}
		void							setTotalMotionTranslation(Leap::Vector translation) {m_vTotalMotionTranslation = translation;}
		void							setTotalMotionScale(float scale) {m_fTotalMotionScale = scale;}

		//create and close the openGL environment
		void newOpenGLContextCreated();
		void openGLContextClosing();
		/// affects model view matrix. Needs to be inside a glPush/glPop matrix block!
		void setupScene();
		// data should be drawn here but no heavy calculations done.
		// any major calculations that only need to be updated per leap data frame
		// should be handled in update and cached in members.
		void renderOpenGL();
		//functions from Component
		void paint(juce::Graphics&);
		void resized();
		//draw the fingers
		void drawPointables(Leap::Frame frame);

		//tools
		void resetCamera();
		void resetScene();
		void initColors();
		void set3DTransformations();

	private:
		enum  { kNumColors = 256 };
		
		//var for render
		Renderer2D*					m_pRenderer2D;
		juce::OpenGLContext         m_openGLContext;
		Skybox*						m_pSkybox;
		LeapUtilGL::CameraGL        m_camera;
		juce::CriticalSection       m_renderMutex;
		Leap::Vector				m_avColors[kNumColors];
		bool                        m_bPaused;
		
		//var for Leap Motion
		float						m_fFrameScale;
		Leap::Frame					m_lastFrame;
		double                      m_fLastUpdateTimeSeconds;
		double                      m_fLastRenderTimeSeconds;
		Leap::Matrix                m_mtxFrameTransform;
		float                       m_fPointableRadius;
		LeapUtil::RollingAverage<>  m_avgUpdateDeltaTime;
		LeapUtil::RollingAverage<>  m_avgRenderDeltaTime;
		/// accumulated rotation/translation and scale from Leap Motion API
		Leap::Matrix                m_mtxTotalMotionRotation;
		Leap::Vector                m_vTotalMotionTranslation;
		float                       m_fTotalMotionScale;
		
		//var for physical
		physical::Model*			m_pModel;
	};
}

#endif //RENDERER_H