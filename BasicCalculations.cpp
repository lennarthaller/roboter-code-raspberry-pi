#include "BasicCalculations.hpp"

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
		if ((nInfraredData[nStartForSearching + i] >= nAverage - 10)&&(nStartForSearching + i >= 25)) {
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
		if ((nInfraredData[nStartForSearching + i] >= nAverage - 10)&&(nStartForSearching + i >= 25)) {
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
	if ((nCounterRight >= 11)&(nCounterLeft < 11)) {
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