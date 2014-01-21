#include "BrakeForce.h"

namespace physical {

    void BrakeForce::apply(ParticleManager* pm){
        //pour chaque particule on regarde toutes les autres et on calcule la force qu'elles exercent dessus
        for(size_t particleIdx = 0; particleIdx < pm->getSpeedArray().size(); particleIdx++){
            for(size_t otherParticleIdx = 0; otherParticleIdx < pm->getSpeedArray().size(); otherParticleIdx++){
                if(otherParticleIdx != particleIdx){
                    glm::vec3 newForce = m_fV * ((pm->getSpeedArray()[otherParticleIdx] - pm->getSpeedArray()[particleIdx])/m_fDt);
                    //est-ce qu'il faut vraiment adder ou plutôt setter ?
                    pm->addForceToParticle(newForce, particleIdx);
                }
            }       
        }
    }

    void BrakeForce::setDt(float dt){
        m_fDt = dt;
    }

    BrakeForce::~BrakeForce(){}
}
