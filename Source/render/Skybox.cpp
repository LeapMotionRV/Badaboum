#include "Skybox.h"


namespace render
{
	Skybox::Skybox(std::string imagePath)
	{
		// bug en Debug...?
		/*File fileSkybox = File("../../data/skybox.png");
		if(!fileSkybox.existsAsFile()){
			std::cout << "Error" << std::endl;
		}
		else {
			Image imageSkybox = ImageCache::getFromFile(fileSkybox);
			this->loadImage(imageSkybox);
		}*/
	}

	Skybox::~Skybox()
	{
	}

	void Skybox::draw()
	{	
		{
			LeapUtilGL::GLMatrixScope gridMatrixScope;
			//LeapUtilGL::drawBox(LeapUtilGL::eStyle::kStyle_Solid, 10.f);
			glColor3f( 1, 1, 0 );
			glBindTexture(GL_TEXTURE_2D, this->getTextureID());
			glBegin(GL_QUADS);
				glTexCoord2i(0,0);glVertex3i(-1,-1,-1);
				glTexCoord2i(1,0);glVertex3i(+1,-1,-1);
				glTexCoord2i(1,1);glVertex3i(+1,+1,-1); 
				glTexCoord2i(0,1);glVertex3i(-1,+1,-1);

				//1 face
				glTexCoord2i(0,0);glVertex3i(-1,-1,+1);
				glTexCoord2i(1,0);glVertex3i(+1,-1,+1); 
				glTexCoord2i(1,1);glVertex3i(+1,+1,+1); 
				glTexCoord2i(0,1);glVertex3i(-1,+1,+1);

				//2 faces
				glTexCoord2i(0,0);glVertex3i(+1,-1,-1); 
				glTexCoord2i(1,0);glVertex3i(+1,-1,+1);
				glTexCoord2i(1,1);glVertex3i(+1,+1,+1);
				glTexCoord2i(0,1);glVertex3i(+1,+1,-1);

				//3 faces
				glTexCoord2i(0,0);glVertex3i(-1,-1,-1); 
				glTexCoord2i(1,0);glVertex3i(-1,-1,+1); 
				glTexCoord2i(1,1);glVertex3i(-1,+1,+1);
				glTexCoord2i(0,1);glVertex3i(-1,+1,-1);

				//4 faces
				glTexCoord2i(1,0);glVertex3i(-1,+1,-1); 
				glTexCoord2i(1,1);glVertex3i(+1,+1,-1); 
				glTexCoord2i(0,1);glVertex3i(+1,+1,+1);
				glTexCoord2i(0,0);glVertex3i(-1,+1,+1);

				//5 faces
				glTexCoord2i(1,0);glVertex3i(-1,-1,+1); 
				glTexCoord2i(1,1);glVertex3i(+1,-1,+1);
				glTexCoord2i(0,1);glVertex3i(+1,-1,-1);
				glTexCoord2i(0,0);glVertex3i(-1,-1,-1);
			glEnd();
		}
	}
}