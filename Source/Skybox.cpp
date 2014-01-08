#include "Skybox.h"


Skybox::Skybox(String imagePath)
{
	File fileSkybox = File("../../data/skybox.png");
	if(!fileSkybox.existsAsFile()){
		std::cout << "Error" << std::endl;
	}
	else {
		Image imageSkybox = ImageCache::getFromFile(fileSkybox);
		this->loadImage(imageSkybox);
	}
}

Skybox::~Skybox()
{
}

void Skybox::draw()
{	
	/*glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();
	glBegin(GL_QUADS);
		//1 face
		glTexCoord2i(0,0);glVertex3i(-10,-10,-10);
		glTexCoord2i(1,0);glVertex3i(+10,-10,-10);
		glTexCoord2i(1,1);glVertex3i(+10,+10,-10); 
		glTexCoord2i(0,1);glVertex3i(-10,+10,-10);

		//2 face
		glTexCoord2i(0,0);glVertex3i(-10,-10,+10);
		glTexCoord2i(1,0);glVertex3i(+10,-10,+10); 
		glTexCoord2i(1,1);glVertex3i(+10,+10,+10); 
		glTexCoord2i(0,1);glVertex3i(-10,+10,+10);

		//3 face
		glTexCoord2i(0,0);glVertex3i(+10,-10,-10); 
		glTexCoord2i(1,0);glVertex3i(+10,-10,+10);
		glTexCoord2i(1,1);glVertex3i(+10,+10,+10);
		glTexCoord2i(0,1);glVertex3i(+10,-10,+10);//++-

		//4 face
		glTexCoord2i(0,0);glVertex3i(-10,-10,-10); 
		glTexCoord2i(1,0);glVertex3i(-10,-10,+10); 
		glTexCoord2i(1,1);glVertex3i(-10,+10,+10);
		glTexCoord2i(0,1);glVertex3i(-10,+10,-10);

		//5 face
		glTexCoord2i(1,0);glVertex3i(-10,+10,-10); 
		glTexCoord2i(1,1);glVertex3i(+10,+10,-10); 
		glTexCoord2i(0,1);glVertex3i(+10,+10,+10);
		glTexCoord2i(0,0);glVertex3i(-10,+10,+10);

		//6 face
		glTexCoord2i(1,0);glVertex3i(-10,-10,+10); 
		glTexCoord2i(1,1);glVertex3i(+10,-10,+10);
		glTexCoord2i(0,1);glVertex3i(+10,-10,-10);
		glTexCoord2i(0,0);glVertex3i(-10,-10,-10);
	glEnd();*/
}