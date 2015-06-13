#ifndef LIDARSCAN_HPP
#define LIDARSCAN_HPP

#include "Timer.hpp"
#include "Seriell.hpp"
#include "KnowledgeBase.hpp"
#include "BasicCalculations.hpp" 
#include "Medianfilter.hpp"
#include "I2C.hpp"

#include <iostream>
#include <unistd.h>

class CLidarScan
{
	public:
		CLidarScan ();
		
		void 	Scan ();
		
	private:
		int 	m_nScanData[100];
		long    m_nTimeStampSinceLastCall;
		int		m_nScanStepCounter;
		bool 	m_bScanActive;
		bool 	m_bNewMeasurement;
		CMedianfilter *Medianfilter;
};

#endif