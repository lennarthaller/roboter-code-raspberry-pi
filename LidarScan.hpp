#include "WiringPi.hpp"
#include "Seriell.hpp"
#include "KnowledgeBase.hpp"
#include "BasicCalculations.hpp" 

#include <iostream>
#include <unistd.h>

class CLidarScan
{
	public:
		CLidarScan ();
		
		void 	Scan ();
		
	private:
		int 	m_nScanData[100];
		std::clock_t m_nTimeStampSinceLastCall;
		int		m_nScanStepCounter;
		bool 	m_bScanActive;
};