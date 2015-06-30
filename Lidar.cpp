#include "Lidar.hpp"

CLidar::CLidar () {
	m_nTimeStampSinceLastCall = 0;
	m_nScanStepCounter = 0;
	m_nCurrentMeasurement = 0;
	m_nTimeStampLidarturn = 0;
	m_bScanActive = true;
	m_bRequestNewMeasurement = true;
	
	pinMode (0, OUTPUT);
	pinMode (2, OUTPUT);
	
	Medianfilter = new CMedianfilter (3, 100);
	Localisation = new CLocalisation ();
	
	for (int i=0;i<100;i++) {
		m_nScanData[i] = 0;
	}
}

void CLidar::Scan () {	
	if (m_bScanActive == true) {	//Scan durchführen
		
		if ((NewMeasurementAvailable() == true)&&(m_nTimeStampSinceLastCall + 45 < g_pTimer->TimeSinceStart())) { //measurement is in range
			
			m_bRequestNewMeasurement = true;
			
			if (m_nScanStepCounter < 100) {		//Läuft der Scan noch? (noch keine 100 Schritte)
				m_nScanData[m_nScanStepCounter] = m_nCurrentMeasurement;
				std::cout << m_nScanData[m_nScanStepCounter] << std::endl; ////DEBUG
				TurnLidar (1);
				m_nScanStepCounter ++;
				m_nTimeStampSinceLastCall = g_pTimer->TimeSinceStart();
			
			}else{		//Scan fertig			
				m_nScanStepCounter = 0;
				m_bScanActive = false;
				m_nTimeStampSinceLastCall = 0;
				Medianfilter->FilterData (m_nScanData);
				g_pKnowledgeBase->SetScannerData(Medianfilter->GetFilteredData());
				//g_pKnowledgeBase->SetScannerData(m_nScanData); //unfiltered data
				g_pBasicCalculations->CalculateDrivingDirection();
				Localisation->Localise ();
			}
		}
	
	}else{	//Zurückdrehen
		if (m_nTimeStampSinceLastCall + 45 < g_pTimer->TimeSinceStart()) { //3 Millisekunde seit dem letzten Aufruf vergangen?
			
			if (m_nScanStepCounter < 100) {
				TurnLidar (0);
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

bool CLidar::NewMeasurementAvailable () {
	if (m_bRequestNewMeasurement == true) {
		g_pI2C->StartLidarMeasurement ();
		m_bRequestNewMeasurement = false;
		return false;
	}else{
		m_nCurrentMeasurement = g_pI2C->GetLidarDistance ();
	}
		
	if (m_nCurrentMeasurement > 4001) {
		m_nCurrentMeasurement = 0;
		m_bRequestNewMeasurement = true;
		return false;
	}
	
	if (m_nCurrentMeasurement < 1) {
		return false;
	}
	return true;
}

void CLidar::TurnLidar (int nDirection) {
	digitalWrite (0, HIGH);
	
	if (nDirection == 0) { //Set direction
		digitalWrite (2, LOW);
	}
	if (nDirection == 1) {
		digitalWrite (2, HIGH);
	}
	//usleep (1); 
	digitalWrite (0, LOW);
}