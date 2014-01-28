#ifndef SHAPE_H
#define SHAPE_H


#include "../ParticleManager.h"


namespace physical
{
	/**
		Represent a shape, with an empty list of links between particles.
	*/
	class Shape
	{
	public:
		Shape();
		~Shape();
		
		virtual void applyInternalForces(ParticleManager* pParticleManager, float dt) = 0;
		virtual void draw(ParticleManager* pParticuleManager) = 0;

		glm::vec3 getHookForce(float K, float L, const glm::vec3& P1, const glm::vec3& P2);
		glm::vec3 getBrakeForce(float V, float dt, const glm::vec3& v1, const glm::vec3& v2);


		//getter
		ParticleGraph*	getGraph() const{return m_graph;}

	protected:
		ParticleGraph*	m_graph;
	};
}

#endif //SHAPE_H