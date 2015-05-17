#include "BasicFunktions.hpp"

CBasicFunktions::CBasicFunktions () {
	m_nTimeStampSinceLastCallSensorUpdate = 0;
	m_nTimeStampSinceLastCallSensorUpdateOdometry = 0;
	m_nTimeStampSinceLastCallLoopTicks = 0;
	m_nLoopTicks = 0;
}

void CBasicFunktions::UpdateSensorData () {

	
	if (m_nTimeStampSinceLastCallSensorUpdateOdometry + 1000 < g_pWiringPi->TimeSinceStart()) {
		int nOdometryData[4];
		
		for(int i=0;i<4;i++) {
			nOdometryData[i] = g_pSeriell->GetPhotoSensorData(i+1);
		}
		
		g_pKnowledgeBase->SetOdometryTicks(nOdometryData); //Odoemtrie updated
		g_pKnowledgeBase->SetOdometryTicksSinceLastUpdate(nOdometryData);
		g_pBasicCalculations->CalculatePositionFromOdometry (500); //Neue Position auf grund der odometrie berechnen
		m_nTimeStampSinceLastCallSensorUpdateOdometry = g_pWiringPi->TimeSinceStart();
	}
	
	if (m_nTimeStampSinceLastCallSensorUpdate + 2000 < g_pWiringPi->TimeSinceStart()) { //200 Millisekunde seit dem letzten Aufruf vergangen?
		std::cout << "X: " << g_pKnowledgeBase->OdometryPosition()->fX << std::endl;
	
		g_pKnowledgeBase->SetCurrentBatteryVoltage (g_pSeriell->GetBatteryVoltage()); //battery voltage updated
		
		if(g_pKnowledgeBase->GetIsConnected() == false) { //connect to client
			if (g_pNetwork->ConnectToClient() == 1) {
				g_pKnowledgeBase->SetIsConnected(true);
			}
		}else{
			NetworkProtocol.SendKnowledgeBase ();
		}
		m_nTimeStampSinceLastCallSensorUpdate = g_pWiringPi->TimeSinceStart();
	}
	
	//std::cout << "CDD: " << g_pKnowledgeBase->GetCalculatedDrivingDirection () << std::endl; //////DEBUG
	
}

void CBasicFunktions::CountLoopTicks () {
	m_nLoopTicks ++;
	if (m_nTimeStampSinceLastCallLoopTicks + 10000 < g_pWiringPi->TimeSinceStart()) {
		g_pKnowledgeBase->SetMainLoopTicksPerSecond (m_nLoopTicks);
		m_nLoopTicks = 0;
		m_nTimeStampSinceLastCallLoopTicks = g_pWiringPi->TimeSinceStart();
	}
}