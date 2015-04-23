#include "BasicCalculations.hpp"

CBasicCalculations::CBasicCalculations () {
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
	}
	/**/
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

void CBasicCalculations::CalculatePositionFromOdometry () {
	int nOdometryLeft = (*(g_pKnowledgeBase->GetOdometryTicksSinceLastUpdate()+3) +  *(g_pKnowledgeBase->GetOdometryTicksSinceLastUpdate()+2)) / 2; //jeweils die Mittelwerte von beiden Lichtschranken auf einer seite minus den alten wert
	int nOdometryRight = (*(g_pKnowledgeBase->GetOdometryTicksSinceLastUpdate()) +  *(g_pKnowledgeBase->GetOdometryTicksSinceLastUpdate()+4)) / 2;
	
	std::cout << *(g_pKnowledgeBase->GetOdometryTicks()) << std::endl; ///////DEBUG
	std::cout << *(g_pKnowledgeBase->GetOdometryTicks()+1) << std::endl;
	std::cout << *(g_pKnowledgeBase->GetOdometryTicks()+2) << std::endl;
	std::cout << *(g_pKnowledgeBase->GetOdometryTicks()+3) << std::endl;
	std::cout << "--------" << std::endl;
	std::cout << nOdometryLeft << std::endl;
	std::cout << nOdometryRight << std::endl;
	std::cout << std::endl;
	
	if (nOdometryLeft == nOdometryRight) { //Der Bot ist gerade aus gefahren
		g_pKnowledgeBase->GetOdometryPosition()->fX += nOdometryRight * cos (g_pKnowledgeBase->GetOdometryPosition()->fX);
		g_pKnowledgeBase->GetOdometryPosition()->fY += nOdometryRight * sin (g_pKnowledgeBase->GetOdometryPosition()->fY);
	}else{ //Der Bot fährt nicht gerade aus
		int n = (nOdometryLeft + nOdometryRight) / 2.0 / (nOdometryRight - nOdometryLeft);
		
		g_pKnowledgeBase->GetOdometryPosition()->fX += n * (sin ((nOdometryRight-nOdometryLeft) / g_pKnowledgeBase->GetOdometryPosition()->fTheta - sin (g_pKnowledgeBase->GetOdometryPosition()->fTheta)));
		g_pKnowledgeBase->GetOdometryPosition()->fY += n * (cos ((nOdometryRight-nOdometryLeft) / g_pKnowledgeBase->GetOdometryPosition()->fTheta - cos (g_pKnowledgeBase->GetOdometryPosition()->fTheta)));
		g_pKnowledgeBase->GetOdometryPosition()->fTheta += (nOdometryRight-nOdometryLeft) / 0.335;
		
		while (g_pKnowledgeBase->GetOdometryPosition()->fTheta > 3.1415)
			g_pKnowledgeBase->GetOdometryPosition()->fTheta -= (2*3.1415);
		while (g_pKnowledgeBase->GetOdometryPosition()->fTheta < 3.1415)
			g_pKnowledgeBase->GetOdometryPosition()->fTheta += (2*3.1415);
		
		std::cout << g_pKnowledgeBase->GetOdometryPosition()->fTheta << std::endl; //////DEBUG
	}
}