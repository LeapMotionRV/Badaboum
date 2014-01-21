#ifndef _IMAC3_BRAKFORCE_HPP
#define _IMAC3_BRAKFORCE_HPP

#include <glm/glm.hpp>

#include "Force.h"
#include "../ParticleManager.h"

namespace physical {
	//force servant de frein cin�tique et obligeant les particules � bouger de la m�me fa�on
    class BrakeForce : public Force{
    public:
        BrakeForce(float fV, float fDt):m_fV(fV), m_fDt(fDt){};
        ~BrakeForce();

        void apply(ParticleManager* pm);
        void setDt(float fDt);
	private:
        float m_fV;//constante de frein
        float m_fDt;//pas du temps
    };

}

#endif // IMAC3_BRAKFORCE_HPP
