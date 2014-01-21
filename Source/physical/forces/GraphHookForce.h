#ifndef __GRAPHHOOKFORCE__HPP__
#define __GRAPHHOOKFORCE__HPP__

#include "Force.h"
#include "../ParticleManager.h"
namespace physical {
	class GraphHookForce : public Force{

	public:
				GraphHookForce 	(float raideur, float longueur);

		void	setGraph		(const ParticleGraph* pGraph) { m_pGraph = pGraph; }
	
		void 	apply			(ParticleManager* pm);

	private:
		float 					m_fK;
		float 					m_fL;
		const ParticleGraph* 	m_pGraph;
	};
}
#endif //__GRAPHHOOKFORCE__HPP__