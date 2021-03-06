#ifndef _IMAC3_GROUND_HPP
#define _IMAC3_GROUND_HPP

#include <vector>
#include <JuceHeader.h>

#include "forces/PolygonForce.h"
#include "shapes/Polygon.h"

namespace physical 
{
	/**
	* contains all polygons forming the ground 
	**/
	class Ground : public juce::OpenGLTexture
	{
	public:
		Ground(LeapfrogSolver* pLeapfrogSolver);
		~Ground();

		/**
		* Manage data of the ground
		*/
		void apply(ParticleManager* pm, float dt);
		void addPolygonAndForce(Polygon* pPolygon, PolygonForce* pPolygonForce);
		void addPolygonAndForce(glm::vec3 pos1, glm::vec3 pos2, glm::vec3 pos3, glm::vec3 pos4, glm::vec3 color, float elasticity);

		/**
		* Draw
		*/
		void createTexture();
		void draw();

		/**
		* Getters
		*/
		std::vector<Polygon*>		getPolygonArray(){return m_polygonArray;}
		std::vector<PolygonForce*>	getPolygonForce(){return m_polygonForceArray;}

	private:
		LeapfrogSolver*				m_pLeapfrogSolver;
		std::vector<Polygon*>		m_polygonArray;
		std::vector<PolygonForce*>	m_polygonForceArray;
	};
}

#endif