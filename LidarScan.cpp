#include "LidarScan.hpp"

CLidarScan::CLidarScan () [
	m_nTimeStampSinceLastCall = 0;
	m_nScanStepCounter = 0;
	m_bScanActive = true;
}

CLidarScan::Scan () {
	if (m_bScanActive == true) {	//Scan durchführen
		if (m_nTimeStampSinceLastCall + 30 < g_pWiringPi->TimeSinceStart()) { //30 Millisekunden seit dem letzten Aufruf vergangen?
			if (m_nScanStepCounter < 100) {		//Läuft der Scan noch? (noch keine 100 Schritte)
				m_nScanData[m_nScanStepCounter] = g_pSeriell->GetInfraredDistance ();
				g_pSeriell->MovePML (1);
				m_nScanStepCounter ++;
				m_nTimeStampSinceLastCall = g_pWiringPi->TimeSinceStart();
			}else{		//Scan fertig
				m_nScanStepCounter = 0;
				m_bScanActive = false;
				m_nTimeStampSinceLastCall = 0;
			}
		}
	}else{	//Zurückdrehen
		if (m_nTimeStampSinceLastCall + 1 < g_pWiringPi->TimeSinceStart()) { //1 Millisekunde seit dem letzten Aufruf vergangen?
			if (m_nScanStepCounter < 100) {
				g_pSeriell->MovePML (0);
				m_nScanStepCounter ++;
			}else{
				m_nScanStepCounter = 0;
				m_nTimeStampSinceLastCall = 0;
				m_bScanActive = true;
			}
		}
	}
}