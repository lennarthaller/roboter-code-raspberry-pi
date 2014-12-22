#include "WiringPi.hpp"
#include "Seriell.hpp"
#include "KnowledgeBase.hpp"

#include <iostream>

class CLidarScan
{
	public:
		CLidarScan ();
		
		void 	Scan ();
		int* 	GetScanData () {return m_nScanData;}
		
	private:
		int 	m_nScanData[100];
		std::clock_t m_nTimeStampSinceLastCall;
		int		m_nScanStepCounter;
		bool 	m_bScanActive;
};