#include "KnowledgeBase.hpp"

CKnowledgeBase::CKnowledgeBase () {
	OdometryPosition.fX = 0.0;
	OdometryPosition.fY = 0.0;
	OdometryPosition.fTheta = 0.0;
	m_fCalculatedDrivingDirection = 0;
	m_fTargetDrivingAngle = 0;
	m_nMainLoopTicksPerSecond = 0;
	m_fCurrentBattteryVoltage = 0.0;
	m_bIsConnected = false;

	
	for (int i=0;i<100;i++) {
		m_nScannerData[i] = 0;
	}
	
	for (int i=0;i<4;i++) {
		m_nOdometryTicks[i] = 0;
	}
	
	for (int i=0;i<4;i++) {
		m_nCurrentMotorPower[i] = 0;
	}
}

void CKnowledgeBase::SetScannerData (int nScanerData[]) {
	for (int i=0; i<100;i++) {
		m_nScannerData[i] = nScanerData[i];
	}
}

void CKnowledgeBase::SetOdometryTicks (int nOdometryTicks[]) {
	for (int i=0; i<4;i++) {
		m_nOdometryTicks[i] += nOdometryTicks[i];
	}
}

void CKnowledgeBase::SetOdometryTicksSinceLastUpdate (int nOdometryTicks[]) {
	for (int i=0; i<4;i++) {
		m_nOdometryTicksSinceLastupdate[i] = nOdometryTicks[i];
	}
}

void CKnowledgeBase::SetCurrentMotorPower (int nCurrentMotorPower, int nMotorNumber) {
	m_nCurrentMotorPower[nMotorNumber-1] = nCurrentMotorPower;
}