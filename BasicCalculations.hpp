#ifndef BASICCALCULATIONS_HPP
#define BASICCALCULATIONS_HPP

#include "KnowledgeBase.hpp"
#include <iostream>

#include <math.h>

#define g_pBasicCalculations CBasicCalculations::Get()

class CBasicCalculations : public TSingleton<CBasicCalculations>
{
	public:
	CBasicCalculations ();
	
	void 	CalculateDrivingDirection ();
	void 	CalculatePositionFromOdometry ();
	
	private:
	float m_fLegthOfAxis;
	float m_fTireCircumference;
	int m_nTicksPerTurn;
};

#endif