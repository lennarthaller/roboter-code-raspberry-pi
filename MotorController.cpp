#include "MotorController.hpp"

CMotorController::CMotorController () {
	const float fUpdateTime = 0.1f;
	const float fP = 0.2f;
	const float fI = 0.3f;
	const float fD = 0.4f;
	
	for (int i=0;i<4;i++) {
		PidMotor[i] = new CPidController (fUpdateTime, fP, fI, fD);;
	}
	
	for (int i=0;i<4;i++) {
		m_nControlValue[i] = 0;
	}
}

void CMotorController::UpdateMotors () {
	for (int i=0;i<4;i++) {
		m_nControlValue[i] += (PidMotor[i]->Calculate (5, *(g_pKnowledgeBase->GetOdometryTicksSinceLastUpdate()+i))*2);
		
		if (m_nControlValue[i] > 255) {
			m_nControlValue[i] = 255;
		}
		if (m_nControlValue[i] < 0) {
			m_nControlValue[i] = 0;
		}
		g_pSeriell->SetMotorPower (i+1, m_nControlValue[i]);
	}	
}
