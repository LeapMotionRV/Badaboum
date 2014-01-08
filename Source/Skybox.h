#ifndef SKYBOX_H
#define SKYBOX_H


#include "JuceHeader.h"
#include "util\LeapUtilGL.h"


class Skybox : public OpenGLTexture
{
public:
	Skybox(String imagePath);
	~Skybox();

	void draw();
};


#endif