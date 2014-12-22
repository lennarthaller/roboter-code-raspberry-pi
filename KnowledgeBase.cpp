#include "KnowledgeBase"

CKnowledgeBase::CKnowledgeBase () {

}

void CKnowledgeBase::SetScanerData (int nScanerData[]) {
	for (int i=0; i<100;i++) {
		m_nScanerData[i] = nScanerData[i];
	}
}