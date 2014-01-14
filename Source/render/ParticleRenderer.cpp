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
		float distance = 0.f;
		glm::vec3 direction = glm::vec3(0.f);
		for(uint32_t i = 0; i < lineCount; i+=2) {
			glColor3f(colorArray[i].x, colorArray[i].y, colorArray[i].z);
			glTranslatef(positionArray[i].x,  positionArray[i].y, positionArray[i].z);
			direction = positionArray[i+1] - positionArray[i];
			direction = glm::normalize(direction);
			distance = sqrt(pow(positionArray[i+1].x-positionArray[i].x, 2)+pow(positionArray[i+1].y-positionArray[i].y, 2)+pow(positionArray[i+1].z-positionArray[i].z, 2));
			LeapUtilGL::drawCylinder(LeapUtilGL::eStyle::kStyle_Outline, distance, direction);
		}
	}
}
