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
			LeapUtilGL::GLMatrixScope gridMatrixScope;
			glColor3f(colorArray[i].x, colorArray[i].y, colorArray[i].z);
			glTranslatef(positionArray[i].x,  positionArray[i].y, positionArray[i].z);
			LeapUtilGL::drawSphere(LeapUtilGL::eStyle::kStyle_Solid, massArray[i]);
		}
	}
}
