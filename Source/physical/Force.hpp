#ifndef _IMAC3_FORCE_HPP
#define _IMAC3_FORCE_HPP


#include "ParticuleManager.h"


namespace physical 
{

	class Force 
	{
	public:
		virtual ~Force() = 0;
		virtual void apply(ParticuleManager& pm) = 0;
	};

}

#endif // IMAC3_FORCE_HPP
