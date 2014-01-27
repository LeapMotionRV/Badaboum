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
				LeapUtilGL::drawSphere(LeapUtilGL::eStyle::kStyle_Solid, massArray[i]/10.);
			}
		}
	}

	void ParticleRenderer::drawLines(
							uint32_t lineCount,
							const ParticleGraph* lines,
							uint32_t vertexCount,
							const glm::vec3* positionArray,
							const glm::vec3* colorArray,
							float lineWidth) 
	{
		glm::vec3 p1;
		glm::vec3 p2;
		glm::vec3 direction;

		for(uint32_t i = 0; i < lineCount; ++i) {
			//get the 2 particles of the line
			unsigned int idParticule1 = (*lines)[i].first;
			unsigned int idParticule2 = (*lines)[i].second;
			p1 = positionArray[idParticule1];
			p2 = positionArray[idParticule2];
			//compute direction, norm
			direction = glm::vec3(p2.x-p1.x, p2.y-p1.y, p2.z-p1.z);
			float norm = sqrt(pow(direction.x, 2)+pow(direction.y, 2)+pow(direction.z, 2));
			//compute angles
			float signeX = 1.f;
			float signeY = 1.f;
			float signeZ = 1.f;

			glm::vec3 x_axis = glm::vec3(1.f, 0.f, 0.f);
			glm::vec3 y_axis = glm::vec3(0.f, 1.f, 0.f);
			glm::vec3 z_axis = glm::vec3(0.f, 0.f, 1.f);

			if(glm::dot(direction, x_axis)<0) signeX = signeX*-1;
			if(glm::dot(direction, y_axis)<0) signeY = signeY*-1;
			if(glm::dot(direction, z_axis)<0) signeZ = signeZ*-1;

			float x_angle_radians = glm::acos(glm::dot(direction, x_axis)/(norm*1));
			float y_angle_radians = glm::acos(glm::dot(direction, y_axis)/(norm*1));
			float z_angle_radians = glm::acos(glm::dot(direction, z_axis)/(norm*1));

			float x_angle_degrees = x_angle_radians * (180/3.14) ;
			float y_angle_degrees = y_angle_radians * (180/3.14) ;
			float z_angle_degrees = z_angle_radians * (180/3.14) ;

			//tranformations
			LeapUtilGL::GLMatrixScope gridMatrixScope;
			glTranslatef(p1.x, p1.y, p1.z);

			glRotatef(x_angle_degrees*signeX, 1.f, 0.f, 0.f);
			glRotatef(y_angle_degrees*signeY, 0.f, 1.f, 0.f);
			glRotatef(z_angle_degrees*signeZ, 0.f, 0.f, 1.f);
			//draw
			glColor3f(colorArray[idParticule1].x, colorArray[idParticule1].y, colorArray[idParticule1].z);
			LeapUtilGL::drawCylinder(LeapUtilGL::eStyle::kStyle_Outline, norm);
		}
	}
}
