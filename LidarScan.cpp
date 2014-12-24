#include "LidarScan.hpp"

CLidarScan::CLidarScan () {
	m_nTimeStampSinceLastCall = 0;
	m_nScanStepCounter = 0;
	m_bScanActive = true;
	
	for (int i=0;i<100;i++) {
		m_nScanData[i] = 0;
	}
}

void CLidarScan::Scan () {
	if (m_bScanActive == true) {	//Scan durchführen
		
		if (m_nTimeStampSinceLastCall + 150 < g_pWiringPi->TimeSinceStart()) { //15 Millisekunden seit dem letzten Aufruf vergangen?
			
			if (m_nScanStepCounter < 100) {		//Läuft der Scan noch? (noch keine 100 Schritte)
				m_nScanData[m_nScanStepCounter] = g_pSeriell->GetInfraredDistance ();
							
				std::cout << m_nScanData[m_nScanStepCounter] << std::endl
				
				g_pSeriell->MovePML (1);
				m_nScanStepCounter ++;
				m_nTimeStampSinceLastCall = g_pWiringPi->TimeSinceStart();
			
			}else{		//Scan fertig
				m_nScanStepCounter = 0;
				m_bScanActive = false;
				m_nTimeStampSinceLastCall = 0;
				
				g_pKnowledgeBase->SetScannerData(m_nScanData);
				g_pBasicCalculations->CalculateDrivingDirection();
			}
		}
	
	}else{	//Zurückdrehen
		if (m_nTimeStampSinceLastCall + 1 < g_pWiringPi->TimeSinceStart()) { //0.1 Millisekunde seit dem letzten Aufruf vergangen?
			
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