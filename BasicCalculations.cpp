#include "BasicCalculations.hpp"

void CBasicCalculations::CalculateDrivingDirection () {
	int nInfraredData[100];
	int nDrivingAngle = -50;
	int nCounterRight = 0;
	int nCounterLeft = 0;
	int nAverage = 0;
	int nStartForSearching = 50 + static_cast<int>(nDrivingAngle/1.8);
	int i = 0;
	int nDrivingDirectionRight = 0;
	int nDrivingDirectionLeft = 0;

	for (int i=0; i<100; i++) {
		nScannerData[i] = *(g_pKnowledgeBase->GetScannerData() +i);
	}
	
	for (int i=0;i<100;i++) {
		nAverage += nInfraredData[i];
	}
	nAverage /= 100;

	i = 5;
	while (nStartForSearching + i > 0) {
		if (nInfraredData[nStartForSearching + i] >= nAverage) {
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
	while (nStartForSearching + i < 100) {
		if (nInfraredData[nStartForSearching + i] >= nAverage) {
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

	if (nCounterRight >= 11) {
		if (nCounterLeft < 11) {
			g_pKnowledgeBase->SetDrivingDirection (nDrivingDirectionRight);
			
				g_pNetwork->Send (1026);
	g_pNetwork->Send(atan2 (g_pKnowledgeBase->SetDrivingDirection (nDrivingDirectionRight));
	g_pNetwork->Send(atan2 (g_pKnowledgeBase->SetDrivingDirection (nDrivingDirectionRight));
		}
	}

	if (nCounterLeft >= 11) {
		if (nCounterRight < 11) {
			g_pKnowledgeBase->SetDrivingDirection (nDrivingDirectionLeft);
			
				g_pNetwork->Send (1026);
	g_pNetwork->Send(atan2 (g_pKnowledgeBase->SetDrivingDirection (nDrivingDirectionLeft));
	g_pNetwork->Send(atan2 (g_pKnowledgeBase->SetDrivingDirection (nDrivingDirectionLeft));
		}
	}

	if (nCounterRight >= 11) {
		if (nCounterLeft >= 11) {
			if (nCounterRight >= nCounterLeft) {
				g_pKnowledgeBase->SetDrivingDirection (nDrivingDirectionLeft);
				
					g_pNetwork->Send (1026);
	g_pNetwork->Send(atan2 (g_pKnowledgeBase->SetDrivingDirection (nDrivingDirectionLeft));
	g_pNetwork->Send(atan2 (g_pKnowledgeBase->SetDrivingDirection (nDrivingDirectionLeft));
			}
		}
	}

	if (nCounterRight < 11) {
		if (nCounterLeft < 11) {
			g_pKnowledgeBase->SetDrivingDirection (-1000);
		}
	}
}