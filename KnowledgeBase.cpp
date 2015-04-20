#include "KnowledgeBase.hpp"

CKnowledgeBase::CKnowledgeBase () {
	OdometryPosition.fX = 0.0;
	OdometryPosition.fY = 0.0;
	OdometryPosition.fTheta = 0.0;
	m_fCalculatedDrivingDirection = 0;
	m_fTargetDrivingAngle = 0;
	
	for (int i=0;i<100;i++) {
		m_nScannerData[i] = 0;
	}
	
	for (int i=0;i<4;i++) {
		m_nOdometryTicks[i] = 0;
	}
}

void CKnowledgeBase::SetScannerData (int nScanerData[]) {
	for (int i=0; i<100;i++) {
		m_nScannerData[i] = nScanerData[i];
	}
}

void CKnowledgeBase::SetOdometryTicks (unsigned long nOdometryTicks[]) {
	for (int i=0; i<4;i++) {
		m_nOdometryTicks[i] += nOdometryTicks[i];
	}
}