#include "BasicFunktions.hpp"

CBasicFunktions::CBasicFunktions () {
	m_nTimeStampSinceLastCallPhotoSensorsUpdate = 0;
	m_nTimeStampSinceLastCallSensorUpdateOdometry = 0;
	m_nTimeStampSinceLastCallSensorUpdateLaserScanner = 0;
	m_nTimeStampSinceLastCallNetwork = 0;
	m_nTimeStampSinceLastCallLoopTicks = 0;
	m_nTimeStampSinceLastBatteryvoltage = 0;
	m_nTimeStampSinceLastScanMatching = 0;
	m_nLoopTicks = 0;

	LaserScanner = new CTiM551Driver ();
	if (LaserScanner->InitLaserScanner () != 1) {
		g_pTracer->Trace (ERROR, "Failed to initialise the laser scanner.");
	}
}

//Update the photo sensors
void CBasicFunktions::UpdatePhotoSensors () {
	if (m_nTimeStampSinceLastCallPhotoSensorsUpdate + 1000 < g_pTimer->TimeSinceStart()) {
		int nOdometryData[4];

		for(int i=0;i<4;i++) {
			nOdometryData[i] = g_pSeriell->GetPhotoSensorData(i+1);
		}

		g_pKnowledgeBase->SetOdometryTicks(nOdometryData); //Odoemtrie updated
		g_pKnowledgeBase->SetOdometryTicksSinceLastUpdate(nOdometryData);
		g_pBasicCalculations->CalculatePositionFromOdometry (); //Neue Position auf grund der odometrie berechnen
		//g_pMotorController->UpdateMotors (); //Control Motors
		m_nTimeStampSinceLastCallPhotoSensorsUpdate = g_pTimer->TimeSinceStart();
	}
}

//Update the laser scanner
void CBasicFunktions::UpdateLaserScanner () {
	if (m_nTimeStampSinceLastCallSensorUpdateLaserScanner + 660 < g_pTimer->TimeSinceStart()) {
		LaserScanner->UpdateData();
		g_pKnowledgeBase->SetScannerData(LaserScanner->GetCurrentData());
		m_nTimeStampSinceLastCallSensorUpdateLaserScanner = g_pTimer->TimeSinceStart();
	}
}

//Count the ticks of a loop per second
void CBasicFunktions::CountLoopTicks () {
	m_nLoopTicks ++;
	if (m_nTimeStampSinceLastCallLoopTicks + 10000 < g_pTimer->TimeSinceStart()) {
		g_pKnowledgeBase->SetMainLoopTicksPerSecond (m_nLoopTicks);
		m_nLoopTicks = 0;
		m_nTimeStampSinceLastCallLoopTicks = g_pTimer->TimeSinceStart();
	}
}

//Check if there is an incoming connection. If the robot is connected, send the KnowledgeBase
void CBasicFunktions::ManageNetwork () {
	if (m_nTimeStampSinceLastCallNetwork + 200 < g_pTimer->TimeSinceStart()) {
		if(g_pKnowledgeBase->GetIsConnected() == false) { //connect to client
			if (g_pNetwork->ConnectToClient() == 1) {
				g_pKnowledgeBase->SetIsConnected(true);
			}
		}else{
			if (NetworkProtocol.SendKnowledgeBase () != 1) {
				g_pKnowledgeBase->SetIsConnected(false);
			}
		}
		m_nTimeStampSinceLastCallNetwork = g_pTimer->TimeSinceStart();
	}
}

//Update the battery voltage
void CBasicFunktions::UpdateBatteryVoltage () {
	if (m_nTimeStampSinceLastBatteryvoltage + 5000 < g_pTimer->TimeSinceStart()) {
		g_pKnowledgeBase->SetCurrentBatteryVoltage (g_pSeriell->GetBatteryVoltage()); //battery voltage updated
		m_nTimeStampSinceLastBatteryvoltage = g_pTimer->TimeSinceStart();
	}
}

void CBasicFunktions::MatchScans () {
	if (m_nTimeStampSinceLastScanMatching + 5000 < g_pTimer->TimeSinceStart()) {
		Localisation.Localize ();
	}
}