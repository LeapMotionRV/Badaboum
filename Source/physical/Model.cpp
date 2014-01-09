#include "Model.h"


namespace physical 
{
	void Model::startSimulation(float dt) {
		m_hookForce.apply(m_particuleManager);
		m_leapfrogSolver.solve(m_particuleManager, dt);
	}
}