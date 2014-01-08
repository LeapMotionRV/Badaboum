#include "Context.h"


Context::Context(OpenGLCanvas& renderer)
{
	this->setRenderer(&renderer);
	this->attachTo(renderer);
	this->makeActive();
}


Context::~Context()
{
	this->detach();
}
