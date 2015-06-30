#include "Localisation.hpp"

CLocalisation::CLocalisation () {
	for (int i=0;i<100;i++) {
		m_CurrentScan[i].fX = 0.0f;
		m_CurrentScan[i].fY = 0.0f;
		m_LastScan[i].fX = 0.0f;
		m_LastScan[i].Y = 0.0f;
	}
}

void CLocalisation::Localise () {
	ScanDataCartesianCoordinates MatchedPoints[100];
	for (int i=0;i<100;i++) {
		MatchedPoints[i].fX = 0.0f;
		MatchedPoints[i].fY = 0.0f;
	}
	float fDistananceBetweenPoints = 0.0f;
	float fDistananceBetweenPointsOld = 100.0f;
	int nMatchedPoints = 0;
	int nSummOfError = 0;
	bool bWasMatched = false;

	for (int i=0;i<100;i++) {
		m_LastScan[i].fX = m_CurrentScan[i].fX;
		m_LastScan[i].fY = m_CurrentScan[i].fY;
		
		m_CurrentScan[i].fX = (*(g_pKnowledgeBase->GetScannerData()+i)) * cosd (1.8*i);
		m_CurrentScan[i].fY = (*(g_pKnowledgeBase->GetScannerData()+i)) * sind (1.8*i);
	}
	
	for (int i=0;i<100;i++) {
		m_CurrentScan[i].fX = ((cosd (g_pKnowledgeBase->OdometryPosition()->fTheta) + (-sind(g_pKnowledgeBase->OdometryPosition()->fTheta))) * m_CurrentScan[i].fX) + g_pKnowledgeBase->OdometryPosition()->nX;
		m_CurrentScan[i].fY = ((sind (g_pKnowledgeBase->OdometryPosition()->fTheta) + cos(g_pKnowledgeBase->OdometryPosition()->fTheta)) * m_CurrentScan[i].fY) + g_pKnowledgeBase->OdometryPosition()->nY;
	}
	
	for (int i=0;i<100;i++) {
		fDistananceBetweenPointsOld = 100.0f; ///THRESHOLD
		for (int j=0;j<100;j++) {
			fDistananceBetweenPoints = static_cast<float> (sqrt (m_LastScan[i].fX - m_CurrentScan[j].fX) + sqrt (m_LastScan[i].fY - m_CurrentScan[j].fY));
			if (fDistananceBetweenPoints < fDistananceBetweenPointsOld) {
				fDistananceBetweenPointsOld = fDistananceBetweenPoints;
				MatchedPoints[i].fX =  m_LastScan[j].fX;
				MatchedPoints[i].fY =  m_LastScan[j].fY;
				bWasMatched = true;
			}
		}
		if (bWasMatched == true) {
			bWasMatched = false;
			nMatchedPoints ++;
			nSummOfError += fDistananceBetweenPoints;
		}
	}
	
	g_pKnowledgeBase->OdometryPosition()->nX = 0;
	g_pKnowledgeBase->OdometryPosition()->nY = 0;
	g_pKnowledgeBase->OdometryPosition()->fTheta = 0.0;
}

float CLocalisation::sind(float fAngle) {
    float fAngleradians = fAngle * M_PI / 180.0f;
    return sin(fAngleradians) * 180.0f / M_PI;
}

float CLocalisation::cosd(float fAngle) {
    float fAngleradians = fAngle * M_PI / 180.0f;
    return cos(fAngleradians) * 180.0f / M_PI;
}