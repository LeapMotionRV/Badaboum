#include "ParticleRenderer.h"
#include "../util/LeapUtilGL.h"

#include <glm/gtc/type_ptr.hpp>

namespace render
{
	ParticleRenderer::ParticleRenderer(float massScale):m_fMassScale(massScale) 
	{}

	ParticleRenderer::~ParticleRenderer() 
	{}

	void ParticleRenderer::clear() 
	{}

	void ParticleRenderer::drawParticles(uint32_t count,
							const glm::vec3* positionArray,
							const float* massArray,
							const glm::vec3* colorArray) 
	{
		// Dessine chacune des particules
		for(uint32_t i = 0; i < count; ++i) {
			{
				LeapUtilGL::GLMatrixScope gridMatrixScope;
				glColor3f(colorArray[i].x, colorArray[i].y, colorArray[i].z);
				glTranslatef(positionArray[i].x,  positionArray[i].y, positionArray[i].z);
				LeapUtilGL::drawSphere(LeapUtilGL::eStyle::kStyle_Solid, massArray[i]);
			}
		}
	}

	void ParticleRenderer::drawLines(
							uint32_t lineCount,
							const std::pair<unsigned int, unsigned int>* lines,
							uint32_t vertexCount,
							const glm::vec3* positionArray,
							const glm::vec3* colorArray,
							float lineWidth) 
	{
		/*for(uint32_t i = 0; i < lineCount; ++i) {
			glColor3f(colorArray[i].x, colorArray[i].y, colorArray[i].z);
			glTranslatef(positionArray[i].x,  positionArray[i].y, positionArray[i].z);
			LeapUtilGL::drawCylinder(LeapUtilGL::eStyle::kStyle_Outline, );
		}*/
		glm::vec3 p1;
		glm::vec3 p2;
		glm::vec3 direction;
		for(uint32_t i = 0; i < lineCount; i+=2) {
			{
				//compute norme and direction
				p1 = positionArray[i];
				p2 = positionArray[i+1];
				float norme = sqrt(pow(p2.x-p1.x, 2)+pow(p2.y-p1.y, 2)+pow(p2.z-p1.z, 2));
				direction = p2 + p1;
				float t = glm::atan(direction.y/direction.x);
				float p = glm::acos(direction.z/norme);
				//tranformations
				LeapUtilGL::GLMatrixScope gridMatrixScope;
				glTranslatef(p1.x, p1.y, p1.z);
				glRotatef(t, 1, 0, 0);
				glRotatef(t, 0, 1, 0);
				glRotatef(p, 0, 0, 1);
				//draw
				glColor3f(colorArray[i].x, colorArray[i].y, colorArray[i].z);
				LeapUtilGL::drawCylinder(LeapUtilGL::eStyle::kStyle_Outline, norme);
			}
		}
	}
}
