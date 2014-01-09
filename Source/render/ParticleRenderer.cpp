#include "ParticleRenderer.h"
#include "../util/LeapUtilGL.h"

#include <glm/gtc/type_ptr.hpp>


namespace physical 
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
			glColor3f(colorArray[i].x, colorArray[i].y, colorArray[i].z);
			glTranslatef(positionArray[i].x,  positionArray[i].y, positionArray[i].z);
			LeapUtilGL::drawSphere(LeapUtilGL::eStyle::kStyle_Solid, massArray[i]);
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
		/*
		glBindBuffer(GL_ARRAY_BUFFER, m_LinePositionVBOID);
		glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(positionArray[0]), positionArray, GL_DYNAMIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, m_LineColorVBOID);
		glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(colorArray[0]), colorArray, GL_DYNAMIC_DRAW);

		glDisable(GL_DEPTH_TEST);

		glLineWidth(lineWidth);

		glUseProgram(m_LineProgramID);

		glBindVertexArray(m_LineVAOID);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_LineIBOID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, lineCount * sizeof(lines[0]), lines, GL_DYNAMIC_DRAW);

		glDrawElements(GL_LINES, lineCount * 2, GL_UNSIGNED_INT, 0);

		glBindVertexArray(0);
		*/
	}

}
