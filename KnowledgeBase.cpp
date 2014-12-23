#include "KnowledgeBase.hpp"

CKnowledgeBase::CKnowledgeBase () {

}

void CKnowledgeBase::SetScannerData (int nScanerData[]) {
	for (int i=0; i<100;i++) {
		m_nScannerData[i] = nScanerData[i];
	}
}