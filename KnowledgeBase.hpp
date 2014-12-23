#ifndef KNOWLEDGEBASE_HPP
#define KNOWLEDGEBASE_HPP

#include "WiringPi.hpp"
#include "Network.hpp"

#define g_pKnowledgeBase CKnowledgeBase::Get()

class CKnowledgeBase : public TSingleton<CKnowledgeBase>
{
	public:
	CKnowledgeBase ();
	
	void 	SetScannerData (int nSensorData[]);
	int* 	GetScannerData () {return m_nScannerData;}
	void 	SetDrivingDirection (float fDirection) {m_fCalculatedDrivingDirection = fDirection;}
	float 	GetCalculateDrivingDirection () {return m_fCalculatedDrivingDirection;}
	
	private:
	int 	m_nScannerData[100];
	float 	m_fCalculatedDrivingDirection;
};

#endif