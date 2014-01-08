#pragma once
#include <iostream>
#include "Leap.h"

/**
	Good example of how to get info from the Controller with a Listener.
	But not used in the current example.
*/
class SampleListener : public Leap::Listener 
{
public:
    virtual void onInit(const Leap::Controller&);
    virtual void onConnect(const Leap::Controller&);
    virtual void onDisconnect(const Leap::Controller&);
    virtual void onExit(const Leap::Controller&);
    virtual void onFrame(const Leap::Controller&);
    virtual void onFocusGained(const Leap::Controller&);
    virtual void onFocusLost(const Leap::Controller&);
};

