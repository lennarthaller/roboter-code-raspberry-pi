#ifndef LOCALISATION_HPP
#define LOCALISATION_HPP

#include "KnowledgeBase.hpp"

#include <math.h>
#include <iostream>

class CLocalisation
{
	public:
		CLocalisation ();
		void Localise ();
		
	private:
		typedef struct {
			float fX;
			float fY;
		} ScanDataCartesianCoordinates;
	
		ScanDataCartesianCoordinates m_CurrentScan[100];
		ScanDataCartesianCoordinates m_LastScan[100];
		
		float sind (float fAngle);
		float cosd (float fAngle);
};

#endif