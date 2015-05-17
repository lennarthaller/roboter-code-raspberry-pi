#include "BasicCalculations.hpp"

CBasicCalculations::CBasicCalculations () {
	m_fLegthOfAxis = 34.4;
	m_fTireCircumference = 61.26f;
	m_nTicksPerTurn = 32;
}

void CBasicCalculations::CalculateDrivingDirection () {
	int nInfraredData[100];
	int nDrivingAngle = static_cast<int>(g_pKnowledgeBase->GetTargetDrivingDirection());
	int nCounterRight = 0;
	int nCounterLeft = 0;
	int nAverage = 0;
	int nStartForSearching = 50 + static_cast<int>(nDrivingAngle/1.8);
	int i = 0;
	int nDrivingDirectionRight = 0;
	int nDrivingDirectionLeft = 0;

	for (int i=0; i<100; i++) {
		nInfraredData[i] = *(g_pKnowledgeBase->GetScannerData() +i);
	}
	
	for (int i=0;i<100;i++) { //Durschnittliche Entfernung des Scans
		nAverage += nInfraredData[i];
	}
	nAverage /= 100;

	i = 5;
	while (nStartForSearching + i > 0) { //Das Array richtung 0 durchlaufen
		if ((nInfraredData[nStartForSearching + i] >= nAverage)&&(nInfraredData[nStartForSearching + i] >= 25)) {
			nCounterRight ++;
			if (nCounterRight == 11) {
			
			nDrivingDirectionRight = (nStartForSearching + i -45) *1.8;
				break;
			}
		}else{
			nCounterRight = 0;		
		}
		i--;
	} 

	i = -5;
	while (nStartForSearching + i < 100) { //Das Array richtung 100 durchlaufen
		if ((nInfraredData[nStartForSearching + i] >= nAverage)&&(nInfraredData[nStartForSearching + i] >= 25)) {
			nCounterLeft ++;
			if (nCounterLeft == 11) {
				nDrivingDirectionLeft = (nStartForSearching + i -55) *1.8;
				break;
			}
		}else{
			nCounterLeft = 0;		
		}
		i++;
	}

	//Welcher Wert soll zurückgegeben werden:
	
	/*if (nDrivingDirectionLeft > (nDrivingDirectionRight*-1)) {
		g_pKnowledgeBase->SetCalculatedDrivingDirection (nDrivingDirectionRight);
	}else{
		g_pKnowledgeBase->SetCalculatedDrivingDirection (nDrivingDirectionLeft);
	}*/
	if ((nCounterRight >= 11)&&(nCounterLeft < 11)) {
		g_pKnowledgeBase->SetCalculatedDrivingDirection (nDrivingDirectionRight);
	} 

	if ((nCounterLeft >= 11)&&(nCounterRight < 11)) {
		g_pKnowledgeBase->SetCalculatedDrivingDirection (nDrivingDirectionLeft);
	}

	if ((nCounterRight >= 11)&&(nCounterLeft >= 11)) {
		if (nCounterRight >= nCounterLeft) {
			g_pKnowledgeBase->SetCalculatedDrivingDirection (nDrivingDirectionLeft);
			}else{
			g_pKnowledgeBase->SetCalculatedDrivingDirection (nDrivingDirectionRight);
			}
	} 

	if ((nCounterRight < 11)&&(nCounterLeft < 11)) {
		g_pKnowledgeBase->SetCalculatedDrivingDirection (-180);
	}
}

void CBasicCalculations::CalculatePositionFromOdometry (const int nDeltaT) {
	float fVL = 0.0f;
	float fVR = 0.0f;
	const float fElapsedTime = ((1/10000) * nDeltaT);
	float fDeltaTheta = 0.0f;
	
	const float fXPosOld = g_pKnowledgeBase->OdometryPosition()->fX;
	const float fYposOld = g_pKnowledgeBase->OdometryPosition()->fY;
	const float fThetaOld = g_pKnowledgeBase->OdometryPosition()->fTheta;
	
	float fX = 0.0f;
	float fY = 0.0f;
	float fTheta = 0.0f;
	
	fVL = ((((*g_pKnowledgeBase->GetOdometryTicksSinceLastUpdate()+1) + (*g_pKnowledgeBase->GetOdometryTicksSinceLastUpdate()+2)) / 2) * m_fTireCircumference) / m_nTicksPerTurn;
	fVL *= fElapsedTime;
	fVR = ((((*g_pKnowledgeBase->GetOdometryTicksSinceLastUpdate()+0) + (*g_pKnowledgeBase->GetOdometryTicksSinceLastUpdate()+3)) / 2) * m_fTireCircumference) / m_nTicksPerTurn;
	fVR *= fElapsedTime;
	
	fDeltaTheta = (fVL - fVR) / m_fLegthOfAxis;
	
	fX = fXPosOld + (((fVL+fVR)/2) * fElapsedTime * sin (fThetaOld + (0.5 * fDeltaTheta * fElapsedTime)));
	fY = fYposOld + (((fVL+fVR)/2) * fElapsedTime * cos (fThetaOld + (0.5 * fDeltaTheta * fElapsedTime)));
	fTheta = fThetaOld + (fDeltaTheta * fElapsedTime);
	
	g_pKnowledgeBase->OdometryPosition()->fX = fX;
	g_pKnowledgeBase->OdometryPosition()->fY = fY;
	g_pKnowledgeBase->OdometryPosition()->fTheta = fTheta;
}