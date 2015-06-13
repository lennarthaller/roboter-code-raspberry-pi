#include "Lidar.hpp"

CLidar::CLidar () {
	m_nTimeStampSinceLastCall = 0;
	m_nScanStepCounter = 0;
	m_bScanActive = true;
	m_bNewMeasurement = true;
	
	Medianfilter = new CMedianfilter (5, 100);
	
	for (int i=0;i<100;i++) {
		m_nScanData[i] = 0;
	}
}

void CLidar::Scan () {
	int nCurrentMeasurement = 0;
	
	if (m_bScanActive == true) {	//Scan durchführen
		
		if (m_bNewMeasurement == true) {
			g_pI2C->StartLidarMeasurement ();
			m_bNewMeasurement = false;
		}else{
			nCurrentMeasurement = g_pI2C->GetLidarDistance ();
		}
		
		if (nCurrentMeasurement > 4000) {
			nCurrentMeasurement = 0;
			m_bNewMeasurement = true;
		}
		
		if ((nCurrentMeasurement > 0)&&(m_nTimeStampSinceLastCall + 250 < g_pTimer->TimeSinceStart())) { //measurement is in range
			
			m_bNewMeasurement = true;
			
			if (m_nScanStepCounter < 100) {		//Läuft der Scan noch? (noch keine 100 Schritte)
				m_nScanData[m_nScanStepCounter] = nCurrentMeasurement;
				std::cout << m_nScanData[m_nScanStepCounter] << std::endl; ////DEBUG
				g_pSeriell->MovePML (1);
				m_nScanStepCounter ++;
				m_nTimeStampSinceLastCall = g_pTimer->TimeSinceStart();
			
			}else{		//Scan fertig			
				m_nScanStepCounter = 0;
				m_bScanActive = false;
				m_nTimeStampSinceLastCall = 0;
				Medianfilter->FilterData (m_nScanData);
				g_pKnowledgeBase->SetScannerData(Medianfilter->GetFilteredData());
				g_pBasicCalculations->CalculateDrivingDirection();
			}
		}
	
	}else{	//Zurückdrehen
		if (m_nTimeStampSinceLastCall + 45 < g_pTimer->TimeSinceStart()) { //3 Millisekunde seit dem letzten Aufruf vergangen?
			
			if (m_nScanStepCounter < 100) {
				g_pSeriell->MovePML (0);
				m_nScanStepCounter ++;
				m_nTimeStampSinceLastCall = g_pTimer->TimeSinceStart();
				
			}else{
				m_nScanStepCounter = 0;
				m_nTimeStampSinceLastCall = 0;
				m_bScanActive = true;
			}
		}
	}
}