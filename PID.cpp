#include "PID.hpp"

CPidController::CPidController (float fDt, float fP, float fI, float fD) {
	for (int i=0; i<3; i++) {
		m_nDeviation[i] = 0;
	}
	m_fCalculatedValue = 0.0f;
	
	m_fDt = fDt;
	m_fP = fP;
	m_fI = fI;
	m_fD = fD;
}

int CPidController::Calculate (int nSetpointValue, int nActualValue) {
	m_nDeviation[1] = m_nDeviation[0];
	m_nDeviation[2] = m_nDeviation[1];
	m_nDeviation[0] = nSetpointValue - nActualValue;
	
	int nCalculatedValue = static_cast<int> ((m_fP * m_nDeviation[0]) + (m_fD * (m_nDeviation[0]-m_nDeviation[1]) / m_fDt) + (m_fI * m_fDt * (m_nDeviation[0]+m_nDeviation[1]+m_nDeviation[2])));
	
	return nCalculatedValue;
}