#include "Model.h"


namespace physical 
{
	void Model::startSimulation(float dt) {
		//m_hookForce.apply(m_particleManager);
		m_gravity.apply(m_particleManager);
		m_leapfrogSolver.solve(m_particleManager, dt);
	}
}