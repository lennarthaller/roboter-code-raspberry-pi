#ifndef LOCALISATION_HPP
#define LOCALISATION_HPP

#include "KnowledgeBase.hpp"
#include "Tracer.hpp"
#include <math.h>

class CLocalisation
{
	public:
		CLocalisation ();
		void Localize ();

	private:
		typedef struct {
			float fX;
			float fY;
		} ScanDataCartesianCoordinates;

		ScanDataCartesianCoordinates m_CurrentScan[271];
		ScanDataCartesianCoordinates m_LastScan[271];

		float sind (float fAngle);
		float cosd (float fAngle);
};

#endif
