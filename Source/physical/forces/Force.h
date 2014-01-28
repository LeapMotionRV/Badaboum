#ifndef _IMAC3_FORCE_HPP
#define _IMAC3_FORCE_HPP


#include "../ParticleManager.h"


namespace physical 
{
	class Force 
	{
	public:
		virtual ~Force() = 0;
		virtual void apply(ParticleManager* pm) = 0;
	};

}

#endif // IMAC3_FORCE_HPP
