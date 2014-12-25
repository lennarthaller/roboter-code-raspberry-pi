#include <iostream>
#include <unistd.h>
#include <cmath>

#include "Seriell.hpp"
#include "Network.hpp"
#include "Logfile.hpp"
#include "LidarScan.hpp"

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
	
	while (1==1) { 
		Scanner.Scan();
	}
	
	Log_File->Del ();
	g_pNetwork->Del ();
	g_pWiringPi->Del ();
	g_pSeriell->Del ();
	g_pKnowledgeBase->Del ();
	g_pBasicCalculations->Del ();
	
	return 0;
}