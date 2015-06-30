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
	ScanDataCartesianCoordinates TranslatedScan[100];
	for (int i=0;i<100;i++) {
		MatchedPoints[i].fX = 0.0f;
		MatchedPoints[i].fY = 0.0f;
		TranslatedScan[i].fX = 0.0f;
		TranslatedScan[i].fY = 0.0f;
	}
	float fDistananceBetweenPoints = 0.0f;
	float fDistananceBetweenPointsOld = 0.0f;
	float nMatchedPoints = 0;
	float fSummOfError = 0.0f;
	
	float fSummOfMatchedXMatchedScan = 0.0f;
	float fSummOfMatchedXNewScann = 0.0f;
	float fSummOfMatchedYMatchedScan = 0.0f;
	float fSummOfMatchedYNewScan = 0.0f;
	float fSXMatchedNew = 0.0f;
	float fSXMatchedYNew = 0.0f;
	float fSYMatchedXNew = 0.0f;
	float fSYMatchedNew = 0.0f;
	
	float fXPos = static_cast<float> (g_pKnowledgeBase->OdometryPosition()->nX);
	float fYPos = static_cast<float> (g_pKnowledgeBase->OdometryPosition()->nY);
	float fTheta = g_pKnowledgeBase->OdometryPosition()->fTheta;
	bool bWasMatched = false;

	for (int i=0;i<100;i++) {
		m_LastScan[i].fX = m_CurrentScan[i].fX;
		m_LastScan[i].fY = m_CurrentScan[i].fY;
		
		m_CurrentScan[i].fX = (*(g_pKnowledgeBase->GetScannerData()+i)) * cosd (1.8*i);
		m_CurrentScan[i].fY = (*(g_pKnowledgeBase->GetScannerData()+i)) * sind (1.8*i);
	}
	
	for (int l=0;l<5;l++) { //Number of ICP iterations
	
		for (int i=0;i<100;i++) {
			TranslatedScan[i].fX = ((cosd (fTheta) + (-sind(fTheta))) * m_CurrentScan[i].fX) + fXPos;
			TranslatedScan[i].fY = ((sind (fTheta) + cos(fTheta)) * m_CurrentScan[i].fY) + fYPos;
		}
	
		for (int i=0;i<100;i++) {
			fDistananceBetweenPointsOld = 10.0f; ///THRESHOLD
			for (int j=0;j<100;j++) {
				fDistananceBetweenPoints = static_cast<float> (sqrt (m_LastScan[i].fX - TranslatedScan[j].fX) + sqrt (m_LastScan[i].fY - TranslatedScan[j].fY));
				if (fDistananceBetweenPoints < fDistananceBetweenPointsOld) {
					fDistananceBetweenPointsOld = fDistananceBetweenPoints;
					MatchedPoints[i].fX = m_LastScan[j].fX;
					MatchedPoints[i].fY = m_LastScan[j].fY;
					bWasMatched = true;
				}
			}
			if (bWasMatched == true) {
				bWasMatched = false;
				nMatchedPoints ++;
				fSummOfError += fDistananceBetweenPoints;
				fSummOfMatchedXMatchedScan += MatchedPoints[i].fX;
				fSummOfMatchedXNewScann += m_CurrentScan[i].fX;
				fSummOfMatchedYMatchedScan += MatchedPoints[i].fY;
				fSummOfMatchedYNewScan += m_CurrentScan[i].fY;
				fSXMatchedNew += MatchedPoints[i].fX * m_CurrentScan[i].fX;
				fSXMatchedYNew += MatchedPoints[i].fX * m_CurrentScan[i].fY;
				fSYMatchedXNew += MatchedPoints[i].fY * m_CurrentScan[i].fX;
				fSYMatchedNew += MatchedPoints[i].fY * m_CurrentScan[i].fY;
			}
		}
		float fA, fB;
		fA = (fSummOfMatchedXMatchedScan*fSummOfMatchedYNewScan)+(nMatchedPoints*fSYMatchedXNew)-(nMatchedPoints*fSXMatchedYNew)-(fSummOfMatchedXNewScann*fSummOfMatchedYMatchedScan);
		fB = (nMatchedPoints*fSXMatchedNew)+(nMatchedPoints*fSYMatchedNew)-(fSummOfMatchedXMatchedScan*fSummOfMatchedXNewScann)-(fSummOfMatchedYMatchedScan*fSummOfMatchedYNewScan);
		
		fTheta = atand (fA/fB);
		fXPos = (fSummOfMatchedXMatchedScan - (cosd(fTheta)*fSummOfMatchedXNewScann) + (sind(fTheta)*fSummOfMatchedYNewScan)) / nMatchedPoints;
		fYPos = (fSummOfMatchedYMatchedScan - (sind(fTheta)*fSummOfMatchedXNewScann) + (cosd(fTheta)*fSummOfMatchedYNewScan)) / nMatchedPoints;
	}
	
	g_pKnowledgeBase->LidarPosition()->nX = static_cast<int> (fXPos);
	g_pKnowledgeBase->LidarPosition()->nY = static_cast<int> (fYPos);
	g_pKnowledgeBase->LidarPosition()->fTheta = fTheta;
	
	g_pKnowledgeBase->OdometryPosition()->nX = 0;
	g_pKnowledgeBase->OdometryPosition()->nY = 0;
	g_pKnowledgeBase->OdometryPosition()->fTheta = 0.0f;
}

float CLocalisation::sind(float fAngle) {
    float fAngleradians = fAngle * M_PI / 180.0f;
    return sin(fAngleradians) * 180.0f / M_PI;
}

float CLocalisation::cosd(float fAngle) {
    float fAngleradians = fAngle * M_PI / 180.0f;
    return cos(fAngleradians) * 180.0f / M_PI;
}

float CLocalisation::atand(float fAngle) {
    float fAngleradians = fAngle * M_PI / 180.0f;
    return atan(fAngleradians) * 180.0f / M_PI;
}