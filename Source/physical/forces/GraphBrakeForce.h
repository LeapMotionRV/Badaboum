#ifndef __GRAPHBRAKEFORCE_HPP__
#define __GRAPHBRAKEFORCE_HPP__

#include "Force.h"
#include "../ParticleManager.h"
namespace physical {
	class GraphBrakeForce : public Force {
	public:
				GraphBrakeForce 	(float fV);

		void	setDt		(float fDt) { m_fDt = fDt; }	
		void	setGraph		(const ParticleGraph* pGraph) { m_pGraph = pGraph; }

		void	apply		(ParticleManager* pm);

	private:
		float					m_fV;
		float					m_fDt;
		const ParticleGraph* 	m_pGraph;
	};
}

#endif //__GRAPHBRAKEFORCE_HPP__ 