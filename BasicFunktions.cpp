#include "BasicFunktions.hpp"

CBasicFunktions::CBasicFunktions () (
	m_nTimeStampSinceLastCall = 0;
)

CBasicFunktions::UpdateSensorData () {
	unsigned long nOdometryData[4];
	
	if (m_nTimeStampSinceLastCall + 2000 < g_pWiringPi->TimeSinceStart()) { //200 Millisekunde seit dem letzten Aufruf vergangen?
		for(int i=0;i<4;i++) {
			nOdometryData[i] = g_pSeriell->GetPhotoSensorData(i+1);
		}
		g_pKnowledgeBase->SetOdometryTicks(nOdometryData); //Odoemtrie updated
		g_pKnowledgeBase->SetCurrentBatteryVoltage (g_pSeriell->GetBatteryVoltage); //battery voltage updated
		g_pBasicCalculations->CalculatePositionFromOdometry (); //Neue Position auf grund der odometrie berechnen
	}
}