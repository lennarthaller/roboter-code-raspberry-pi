#include "Localisation.hpp"

CLocalisation::CLocalisation () {
	for (int i=0;i<100;i++) {
		m_CurrentScan[i].fX = 0.0f;
		m_CurrentScan[i].fY = 0.0f;
		m_LastScan[i].fX = 0.0f;
		m_LastScan[i].fY = 0.0f;
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
	
	for (int l=0;l<10;l++) { //Number of ICP iterations
	
		for (int i=0;i<100;i++) {
			TranslatedScan[i].fX = ((cos (fTheta) + (-sin(fTheta))) * m_CurrentScan[i].fX) + fXPos;
			TranslatedScan[i].fY = ((sin (fTheta) + cos(fTheta)) * m_CurrentScan[i].fY) + fYPos;
		}
	
		for (int i=0;i<100;i++) {
			fDistananceBetweenPointsOld = 1000.0f;
			for (int j=0;j<100;j++) {
				fDistananceBetweenPoints = static_cast<float> (sqrt (m_LastScan[j].fX - TranslatedScan[i].fX) + sqrt (m_LastScan[j].fY - TranslatedScan[i].fY));
				if (fDistananceBetweenPoints < fDistananceBetweenPointsOld) {
					fDistananceBetweenPointsOld = fDistananceBetweenPoints;
					MatchedPoints[i].fX = m_LastScan[j].fX;
					MatchedPoints[i].fY = m_LastScan[j].fY;
					//bWasMatched = true;
				}
			}
			if (fDistananceBetweenPointsOld < 5.0f - (l*0.5)) { /////THRESHOLD
				//bWasMatched = false;
				nMatchedPoints ++;
				fSummOfError += fDistananceBetweenPointsOld;
				fSummOfMatchedXMatchedScan += MatchedPoints[i].fX;
				fSummOfMatchedXNewScann += m_CurrentScan[i].fX;
				fSummOfMatchedYMatchedScan += MatchedPoints[i].fY;
				fSummOfMatchedYNewScan += m_CurrentScan[i].fY;
				fSXMatchedNew += MatchedPoints[i].fX + m_CurrentScan[i].fX;
				fSXMatchedYNew += MatchedPoints[i].fX + m_CurrentScan[i].fY;
				fSYMatchedXNew += MatchedPoints[i].fY + m_CurrentScan[i].fX;
				fSYMatchedNew += MatchedPoints[i].fY + m_CurrentScan[i].fY;
			}
		}
		float fA, fB;
		fA = (fSummOfMatchedXMatchedScan*fSummOfMatchedYNewScan)+(nMatchedPoints*fSYMatchedXNew)-(nMatchedPoints*fSXMatchedYNew)-(fSummOfMatchedXNewScann*fSummOfMatchedYMatchedScan);
		fB = (nMatchedPoints*fSXMatchedNew)+(nMatchedPoints*fSYMatchedNew)-(fSummOfMatchedXMatchedScan*fSummOfMatchedXNewScann)-(fSummOfMatchedYMatchedScan*fSummOfMatchedYNewScan);
		
		fTheta = atan (fA/fB);
		fXPos = (fSummOfMatchedXMatchedScan - (cos(fTheta)*fSummOfMatchedXNewScann) + (sin(fTheta)*fSummOfMatchedYNewScan)) / nMatchedPoints;
		fYPos = (fSummOfMatchedYMatchedScan - (sin(fTheta)*fSummOfMatchedXNewScann) - (cos(fTheta)*fSummOfMatchedYNewScan)) / nMatchedPoints;
		
		std::cout << "Matched Points: " << nMatchedPoints << std::endl << std::endl; ///DEBUG
		std::cout << "X: " << fXPos << std::endl; ///DEBUG
		std::cout << "Y: " << fYPos << std::endl; ///DEBUG
		std::cout << "Theta: " << fTheta << std::endl; ///DEBUG
		
		fDistananceBetweenPointsOld = 0.0f;
		nMatchedPoints = 0;
		fSummOfError = 0.0f;
	
		fSummOfMatchedXMatchedScan = 0.0f;
		fSummOfMatchedXNewScann = 0.0f;
		fSummOfMatchedYMatchedScan = 0.0f;
		fSummOfMatchedYNewScan = 0.0f;
		fSXMatchedNew = 0.0f;
		fSXMatchedYNew = 0.0f;
		fSYMatchedXNew = 0.0f;
		fSYMatchedNew = 0.0f;
	}
	
	g_pKnowledgeBase->LidarPosition()->nX += static_cast<int> (fXPos);
	g_pKnowledgeBase->LidarPosition()->nY += static_cast<int> (fYPos);
	g_pKnowledgeBase->LidarPosition()->fTheta += fTheta;
	
	//std::cout << "X: " << fXPos << std::endl; ///DEBUG
	//std::cout << "Y: " << fYPos << std::endl; ///DEBUG
	//std::cout << "Theta: " << fTheta << std::endl; ///DEBUG
	//std::cout << "Matched Points: " << nMatchedPoints << std::endl << std::endl; ///DEBUG
	
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