#include "BasicFunktions.hpp"

CBasicFunktions::CBasicFunktions () {
	m_nTimeStampSinceLastCallSensorUpdate = 0;
	m_nTimeStampSinceLastCallLoopTicks = 0;
	m_nLoopTicks = 0;
}

void CBasicFunktions::UpdateSensorData () {
	int nOdometryData[4];
	
	if (m_nTimeStampSinceLastCallSensorUpdate + 2000 < g_pWiringPi->TimeSinceStart()) { //200 Millisekunde seit dem letzten Aufruf vergangen?
		for(int i=0;i<4;i++) {
			nOdometryData[i] = g_pSeriell->GetPhotoSensorData(i+1);
		}
		g_pKnowledgeBase->SetOdometryTicks(nOdometryData); //Odoemtrie updated
		g_pKnowledgeBase->SetOdometryTicksSinceLastUpdate(nOdometryData);
		//g_pBasicCalculations->CalculatePositionFromOdometry (); //Neue Position auf grund der odometrie berechnen
		g_pKnowledgeBase->SetCurrentBatteryVoltage (g_pSeriell->GetBatteryVoltage()); //battery voltage updated
		
		if(g_pKnowledgeBase->GetNetworkStatus() == 0) { //connect to client
			if (g_pNetwork->ConnectToClient() == 1) {
				g_pKnowledgeBase->SetNetworkStatus (1);
			}
		}
		if (g_pKnowledgeBase->GetNetworkStatus() == 1) {
			NetworkProtocol.SendKnowledgeBase ();
		}
		m_nTimeStampSinceLastCallSensorUpdate = g_pWiringPi->TimeSinceStart();
	}
}

void CBasicFunktions::CountLoopTicks () {
	m_nLoopTicks ++;
	if (m_nTimeStampSinceLastCallLoopTicks + 10000 < g_pWiringPi->TimeSinceStart()) {
		g_pKnowledgeBase->SetMainLoopTicksPerSecond (m_nLoopTicks);
		m_nLoopTicks = 0;
		m_nTimeStampSinceLastCallLoopTicks = g_pWiringPi->TimeSinceStart();
	}
}