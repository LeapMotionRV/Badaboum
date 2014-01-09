#include <glm/glm.hpp>

#include "LeapfrogSolver.h"


namespace physical {

	void LeapfrogSolver::solve(ParticleManager& pm, float dt) {
		for(size_t i = 0; i < pm.getForceArray().size(); i++){
			glm::vec3 nextSpeed = pm.getSpeedArray()[i] + dt * (pm.getForceArray()[i] / pm.getMassArray()[i]);
			glm::vec3 nextPosition = pm.getPositionArray()[i] + dt * nextSpeed;
			pm.setSpeedOfParticle(nextSpeed, i);
			pm.setPositionOfParticle(nextPosition, i);
			pm.resetForceOfParticle(i);
		}
	}

	ParticleState LeapfrogSolver::getNextState(uint32_t particleIdx, ParticleManager& pm, float dt) const {
		ParticleState particleState;
		
		glm::vec3 nextSpeed = pm.getSpeedArray()[particleIdx] + dt * (pm.getForceArray()[particleIdx] / pm.getMassArray()[particleIdx]);
		glm::vec3 nextPosition = pm.getPositionArray()[particleIdx] + dt * nextSpeed;

		particleState.m_position = nextPosition;
		particleState.m_speed = nextSpeed;
		return particleState;
	}
}