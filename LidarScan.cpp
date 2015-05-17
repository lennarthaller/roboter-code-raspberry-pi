#include "LidarScan.hpp"

CLidarScan::CLidarScan () {
	m_nTimeStampSinceLastCall = 0;
	m_nScanStepCounter = 0;
	m_bScanActive = true;
	
	Medianfilter = new CMedianfilter (5, 100);
	
	for (int i=0;i<100;i++) {
		m_nScanData[i] = 0;
	}
}

void CLidarScan::Scan () {
	if (m_bScanActive == true) {	//Scan durchf�hren
		
		if (m_nTimeStampSinceLastCall + 400 < g_pWiringPi->TimeSinceStart()) { //45 Millisekunde seit dem letzten Aufruf vergangen? (350)
			
			if (m_nScanStepCounter < 100) {		//L�uft der Scan noch? (noch keine 100 Schritte)
				m_nScanData[m_nScanStepCounter] = g_pSeriell->GetInfraredDistance ();
				//std::cout << m_nScanData[m_nScanStepCounter] << std::endl; ////DEBUG
				g_pSeriell->MovePML (1);
				m_nScanStepCounter ++;
				m_nTimeStampSinceLastCall = g_pWiringPi->TimeSinceStart();
			
			}else{		//Scan fertig			
				m_nScanStepCounter = 0;
				m_bScanActive = false;
				m_nTimeStampSinceLastCall = 0;
				Medianfilter->FilterData (m_nScanData);
				g_pKnowledgeBase->SetScannerData(Medianfilter->GetFilteredData());
				g_pBasicCalculations->CalculateDrivingDirection();
			}
		}
	
	}else{	//Zur�ckdrehen
		if (m_nTimeStampSinceLastCall + 20 < g_pWiringPi->TimeSinceStart()) { //0.1 Millisekunde seit dem letzten Aufruf vergangen?
			
			if (m_nScanStepCounter < 100) {
				g_pSeriell->MovePML (0);
				m_nScanStepCounter ++;
				m_nTimeStampSinceLastCall = g_pWiringPi->TimeSinceStart();
				
			}else{
				m_nScanStepCounter = 0;
				m_nTimeStampSinceLastCall = 0;
				m_bScanActive = true;
			}
		}
	}
}