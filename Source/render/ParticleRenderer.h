#ifndef _IMAC3_PARTICULE_RENDERER_HPP
#define _IMAC3_PARTICULE_RENDERER_HPP


#include <glm/glm.hpp>
#include <utility>
#include <stdint.h>

#include <vector>

namespace render
{
		typedef std::vector<std::pair<unsigned int, unsigned int>> ParticleGraph;
	class ParticleRenderer
	{
	public:
		ParticleRenderer(float massScale = 0.05);
		~ParticleRenderer();
		
		//ParticleRenderer(const ParticleRenderer&) = delete; //doesn't work with the VS Compiler...
		//ParticleRenderer& operator =(const ParticleRenderer&) = delete; //doesn't work with the VS Compiler...
		
		void clear();

		void drawParticles(uint32_t count,
						const glm::vec3* positionArray,
						const float* massArray,
						const glm::vec3* colorArray);

		void drawLines(uint32_t lineCount,
					const ParticleGraph* lines,
					uint32_t vertexCount,
					const glm::vec3* positionArray,
					const glm::vec3* colorArray,
					float lineWidth = 1.f);

	private:
		// Scale appliqué sur la masse de chaque particule pour obtenir sa taille
		float m_fMassScale;
	};
}

#endif // _IMAC3_PARTICULE_RENDERER_HPP