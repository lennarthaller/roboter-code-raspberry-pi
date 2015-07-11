#ifndef LIDAR_HPP
#define LIDAR_HPP

#include "Timer.hpp"
#include "Seriell.hpp"
#include "KnowledgeBase.hpp"
#include "BasicCalculations.hpp" 
#include "Medianfilter.hpp"
#include "Localisation.hpp"
#include "I2C.hpp"

#include <iostream>
#include <unistd.h>
#include <wiringPi.h>

class CLidar
{
	public:
		CLidar ();
		void *StartScanning ();
		static void *GetScanner (void *context) {return ((CLidar *)context)->StartScanning();}
		
	private:
		bool NewMeasurementAvailable ();
		void TurnLidar (int nDirection);
	
		int 	m_nScanData[100];
		long    m_nTimeStampSinceLastCall;
		long    m_nTimeStampLidarturn;
		int		m_nScanStepCounter;
		int 	m_nCurrentMeasurement;
		bool 	m_bScanActive;
		bool 	m_bRequestNewMeasurement;
		CMedianfilter *Medianfilter;
		CLocalisation *Localisation;
};

#endif