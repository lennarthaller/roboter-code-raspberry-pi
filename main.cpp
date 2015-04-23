#include <iostream>
#include <unistd.h>
#include <cmath>

#include "Seriell.hpp"
#include "Network.hpp"
#include "Logfile.hpp"
#include "LidarScan.hpp"
#include "BasicFunktions.hpp"

using namespace std;

int main () {
	Log_File->CreateLogfile();
	
	CLidarScan Scanner;
	
	cout << "Roboter test Programm v0.1" << endl;
	cout << "von" << endl << "Lennart Haller" << endl;
	
	int nSeriellData[2];
	int nDaten = 0;
	if (g_pWiringPi->InitWiringPi() != 1) {
		cout << "Fehler" << endl;
	}else{
	}
	
	if (g_pNetwork->InitNetwork () != 1) {
		cout << "Fehler" << endl;
	}

	/*if (g_pNetwork->ConnectToClient () != 1) {
		cout << "Fehler" << endl;
	}*/ 
	
	//cout << "Aktuelle Entfernung zu naechstem Hinderniss: " << g_pSeriell->GetInfraredDistance () << endl;
	//cout << "Atueller Kompas Wert: " << g_pWiringPi->GetCompassData() << endl;
	//g_pSeriell->SetMotorPower (1,150);
	cout << "Lichtschranke 1: " << g_pSeriell->GetPhotoSensorData(1) << endl;
	//cout << "Betriebsspannung: " << g_pSeriell->GetBatteryVoltage() << endl;
	
	g_pSeriell->SetMotorPower (1,50);
	g_pSeriell->SetMotorPower (2,60);
	g_pSeriell->SetMotorPower (3,60);
	g_pSeriell->SetMotorPower (4,45);
	int n = 0;
	while (1==1) { 
		//cout << "Aktuelle Entfernung zu naechstem Hinderniss: " << g_pSeriell->GetInfraredDistance () << endl;
		//cout << "Betriebsspannung: " << g_pSeriell->GetBatteryVoltage() << endl;
		//cout << endl;
		//usleep (2000000); 
		Scanner.Scan();
		g_pCBasicFunktions->UpdateSensorData ();
		g_pCBasicFunktions->CountLoopTicks ();
	}
	
	Log_File->Del ();
	g_pNetwork->Del ();
	g_pWiringPi->Del ();
	g_pSeriell->Del ();
	g_pKnowledgeBase->Del ();
	g_pBasicCalculations->Del ();
	
	return 0;
}