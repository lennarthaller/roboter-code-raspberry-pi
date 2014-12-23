#include "BasicCalculations.hpp"

void CBasicCalculations::CalculateDrivingDirection () {
	int nScannerData[100];
	float fSineValue = 0;
	float fCosineValue = 0;
	
	float b, c, d, x = 0;
	
	for (int i=0; i<100; i++) {
		nScannerData[i] = *(g_pKnowledgeBase->GetScannerData() +i);
	}	
	
		for (int i=0;i<100;i++) {
		x = DegreeToRadian(-90 + (1.8f * i));

		b = sin (x);
		c = -0.4f * pow (x, 2) + 1;
		d = (atan ((nScannerData[i] / 10.0f) - 11) + 1.5f) / 3;

		fSineValue += b * c * d; 
		b = cos (x);
		fCosineValue += b * c * d; 
	}
	
	std::cout << RadianToDegree (atan2 (fSineValue, fCosineValue)) << std::endl;
	g_pNetwork->Send (1026);
	g_pNetwork->Send(atan2 (fSineValue, fCosineValue) * -1);
	
	g_pKnowledgeBase->SetDrivingDirection (RadianToDegree (atan2 (fSineValue, fCosineValue)));
}

float CBasicCalculations::DegreeToRadian (float fDegree) {
	float radianValue = fDegree * (3.14159265359 / 180.0); 
	return radianValue;
}

float CBasicCalculations::RadianToDegree (float fRadian) {
	float degreeValue = fRadian * (180.0 / 3.14159265359);
	return degreeValue;
}
