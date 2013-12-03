#ifndef RENDERER_H
#define RENDERER_H


#include "JuceHeader.h"
#include "util\LeapUtilGL.h"
#include "Leap.h"
#include "SampleListener.h"


// intermediate class for convenient conversion from JUCE color
// to float vector argument passed to GL functions
struct GLColor 
{
	GLfloat r, g, b, a; 

	GLColor() : r(1), g(1), b(1), a(1) {}

	GLColor( float _r, float _g, float _b, float _a=1 ):r(_r), g(_g), b(_b), a(_a)
	{}

	explicit GLColor( const Colour& juceColor ) 
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


class OpenGLCanvas  : public Component,
                      public OpenGLRenderer,
                      Leap::Listener
{
private:
    OpenGLContext               m_openGLContext;
    LeapUtilGL::CameraGL        m_camera;
    Leap::Frame                 m_lastFrame;
    double                      m_fLastUpdateTimeSeconds;
    double                      m_fLastRenderTimeSeconds;
    Leap::Matrix                m_mtxFrameTransform;
    float                       m_fFrameScale;
    float                       m_fPointableRadius;
    LeapUtil::RollingAverage<>  m_avgUpdateDeltaTime;
    LeapUtil::RollingAverage<>  m_avgRenderDeltaTime;
    String                      m_strUpdateFPS;
    String                      m_strRenderFPS;
    String                      m_strPrompt;
    String                      m_strHelp;
    Font                        m_fixedFont;
    CriticalSection             m_renderMutex;
    bool                        m_bShowHelp;
    bool                        m_bPaused;

    enum  { kNumColors = 256 };
    Leap::Vector				m_avColors[kNumColors];

	SampleListener*				m_plistener;

public:
	//return the controller (singleton)
    static Leap::Controller& getController() 
    {
        static Leap::Controller s_controller;
        return  s_controller;
    }

	//alloc and desacolloc the openGL context
    OpenGLCanvas();
    ~OpenGLCanvas();

	//create and close the openGL environment
    void newOpenGLContextCreated();
    void openGLContextClosing();

	//manage inputs
    bool keyPressed(const KeyPress& keyPress);
    void mouseDown (const MouseEvent& e);
    void mouseDrag (const MouseEvent& e);
    void mouseWheelMove(const MouseEvent& e, const MouseWheelDetails& wheel);
    void resized();

	//update renderer
    void paint(Graphics&);
    void renderOpenGL2D();

    // calculations that should only be done once per leap data frame but may be drawn many times should go here.
    void update( Leap::Frame frame );

    /// affects model view matrix. Needs to be inside a glPush/glPop matrix block!
    void setupScene();

    // data should be drawn here but no heavy calculations done.
    // any major calculations that only need to be updated per leap data frame
    // should be handled in update and cached in members.
    void renderOpenGL();

    void drawPointables( Leap::Frame frame );

    virtual void onInit(const Leap::Controller&);
    virtual void onConnect(const Leap::Controller&);
    virtual void onDisconnect(const Leap::Controller&);
    virtual void onFrame(const Leap::Controller& controller);

    void resetCamera();

    void initColors();
};


#endif //RENDERER_H