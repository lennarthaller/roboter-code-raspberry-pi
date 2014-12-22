#ifndef KNOWLEDGEBASE_HPP
#define KNOWLEDGEBASE_HPP

#define g_pKnowledgeBase KnowledgeBase::Get()

class CKnowledgeBase : public TSingleton<CKnowledgeBase>
{
	public:
	CKnowledgeBase ();
	
	void SetScanerData (int nSensorData[]);
	
	private:
	int m_nScanerData[100];
	float m_fCalculatedDrivingDirection;
};

#endif