#ifndef BASICCALCULATIONS_HPP
#define BASICCALCULATIONS_HPP

#include "KnowledgeBase.hpp"
#include <iostream>

#include <cmath>

#define g_pBasicCalculations CBasicCalculations::Get()

class CBasicCalculations : public TSingleton<CBasicCalculations>
{
	public:
	CBasicCalculations ();
	
	void 	CalculateDrivingDirection ();
	void 	CalculatePositionFromOdometry ();
	
	private:
};

#endif