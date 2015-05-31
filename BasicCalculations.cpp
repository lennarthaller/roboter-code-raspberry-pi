#include "BasicCalculations.hpp"

CBasicCalculations::CBasicCalculations () {
	m_fLegthOfAxis = 34.4f;
	m_fTireCircumference = 61.26f;
	m_nTicksPerTurn = 32;
}

void CBasicCalculations::CalculateDrivingDirection () {
	const int nPointsRequired = 13;
	
	int nInfraredData[100];
	float fDrivingAngle = g_pKnowledgeBase->GetTargetDrivingDirection();
	int nCounterRight = 0;
	int nCounterLeft = 0;
	int nAverage = 0;
	int nStartForSearching = 50 + static_cast<int>(fDrivingAngle/1.8);
	int i = 0;
	int nDrivingDirectionRight = 0;
	int nDrivingDirectionLeft = 0;
	int nStepsRequiredRight = 0;
	int nStepsRequiredLeft = 0;

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
			nStepsRequiredRight ++;
			if (nCounterRight == nPointsRequired) {
				nDrivingDirectionRight = (nStartForSearching + i - 55) *1.8;
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
			nStepsRequiredLeft ++;
			if (nCounterLeft == nPointsRequired) {
				nDrivingDirectionLeft = (nStartForSearching + i -45) *1.8;
				break;
			}
		}else{
			nCounterLeft = 0;		
		}
		i++;
	}

	//Welcher Wert soll zurückgegeben werden:	
	if ((nCounterLeft >= nPointsRequired)&&(nCounterRight >= nPointsRequired)) {
		if (nStepsRequiredRight <= nStepsRequiredLeft) {
			g_pKnowledgeBase->SetCalculatedDrivingDirection (nDrivingDirectionRight);
		}else{
			g_pKnowledgeBase->SetCalculatedDrivingDirection (nDrivingDirectionLeft);
		}
	}else{
		if (nCounterRight >= nPointsRequired) {
			g_pKnowledgeBase->SetCalculatedDrivingDirection (nDrivingDirectionRight);
		}
		if (nCounterLeft >= nPointsRequired){
			g_pKnowledgeBase->SetCalculatedDrivingDirection (nDrivingDirectionLeft);
		}
	}
	if ((nCounterLeft < nPointsRequired)&&(nCounterRight < nPointsRequired)) {
		g_pKnowledgeBase->SetCalculatedDrivingDirection (-180);
	}
}

void CBasicCalculations::CalculatePositionFromOdometry () {
	float fVL = 0.0f;
	float fVR = 0.0f;
	float fDeltaTheta = 0.0f;
	
	const float fXPosOld = static_cast <float> (g_pKnowledgeBase->OdometryPosition()->nX);
	const float fYposOld = static_cast <float> (g_pKnowledgeBase->OdometryPosition()->nY);
	const float fThetaOld = g_pKnowledgeBase->OdometryPosition()->fTheta;
	
	float fX = 0.0f;
	float fY = 0.0f;
	float fTheta = 0.0f;
	
	float fTicksL = static_cast<float>((*(g_pKnowledgeBase->GetOdometryTicksSinceLastUpdate()+1) + *(g_pKnowledgeBase->GetOdometryTicksSinceLastUpdate()+2)) / 2);
	float fTicksR = static_cast<float>((*(g_pKnowledgeBase->GetOdometryTicksSinceLastUpdate()+0) + *(g_pKnowledgeBase->GetOdometryTicksSinceLastUpdate()+3)) / 2);
	
	fVL = fTicksL * m_fTireCircumference / m_nTicksPerTurn;
	fVR = fTicksR * m_fTireCircumference / m_nTicksPerTurn;
	
	fDeltaTheta = (fVL - fVR) / m_fLegthOfAxis; //length of axis
	
	fX = fXPosOld + (((fVL+fVR)/2) * sin (fThetaOld + (0.5 * fDeltaTheta)));
	fY = fYposOld + (((fVL+fVR)/2) * cos (fThetaOld + (0.5 * fDeltaTheta)));
	fTheta = fThetaOld + (fDeltaTheta);
	
	if (fTheta > 2 * M_PI) {
		fTheta -= 2 * M_PI;
	}
	
	if (fTheta < 0) {
		fTheta += 2 * M_PI;
	}
	
	g_pKnowledgeBase->OdometryPosition()->nX = static_cast <int> (fX);
	g_pKnowledgeBase->OdometryPosition()->nY = static_cast <int> (fY);
	g_pKnowledgeBase->OdometryPosition()->fTheta = fTheta;
}