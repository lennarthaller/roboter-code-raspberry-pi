#ifndef LOCALISATION_HPP
#define LOCALISATION_HPP

#include "KnowledgeBase.hpp"

#include <iostream>
#include <math.h>

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
		
		sind (float fAngle);
		cosd (float fAngle);
		atand (float fAngle);
};

#endif