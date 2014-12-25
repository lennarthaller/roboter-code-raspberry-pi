#include "KnowledgeBase.hpp"

CKnowledgeBase::CKnowledgeBase () {
	m_fCalculatedDrivingDirection = 0;
	for (int i=0;i<100;i++) {
		m_nScannerData[i] = 0;
	}
}

void CKnowledgeBase::SetScannerData (int nScanerData[]) {
	for (int i=0; i<100;i++) {
		m_nScannerData[i] = nScanerData[i];
	}
}