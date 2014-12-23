#ifndef BASICCALCULATIONS_HPP
#define BASICCALCULATIONS_HPP

#include "KnowledgeBase.hpp"
#include <cmath>

#define g_pBasicCalculations CBasicCalculations::Get()

class CBasicCalculations : public TSingleton<CBasicCalculations>
{
	public:
	void 	CalculateDrivingDirection ();
	
	private:
	float 	DegreeToRadian (float fDegree);
	float 	RadianToDegree (float fRadian);
};

#endif