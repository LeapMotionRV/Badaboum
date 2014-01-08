#ifndef CONTEXT_H
#define CONTEXT_H


#include "JuceHeader.h"
#include "Renderer.h"


class Context : public OpenGLContext
{
public:
	Context(OpenGLCanvas& renderer);
	~Context();
};

#endif