#ifndef PID_HPP
#define PID_HPP

class CNetworkProtocol
{
public:
	CNetworkProtocol (float fDt, float fP, float fI, float fD);
	int Calculate (int nSetpointValue, int nActualValue);
	
private:
	int m_nDeviation[3];
	float m_fCalculatedValue;
	
	float m_fDt;
	float m_fP;
	float m_fI;
	float m_fD;
};

#endif