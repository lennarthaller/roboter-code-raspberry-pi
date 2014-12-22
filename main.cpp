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
	
	CLidarScan Scaner;
	
	cout << "Roboter test Programm v0.1" << endl;
	cout << "von" << endl << "Lennart Haller" << endl;
	
	int nSeriellData[2];
	int nDaten = 0;
	//wiringPi init
	if (g_pWiringPi->InitWiringPi() != 1) {
		cout << "Fehler" << endl;
	}else{
	}
	
	if (g_pNetwork->InitNetwork () != 1) {
		cout << "Fehler" << endl;
	}

	/*if (g_pNetwork->ConnectToClient () != 1) {
		cout << "Fehler" << endl;
	} */
	
	//cout << "Aktuelle Entfernung zu naechstem Hinderniss: " << g_pSeriell->GetInfraredDistance () << endl;
	//cout << "Atueller Kompas Wert: " << g_pWiringPi->GetCompassData() << endl;
	//g_pSeriell->SetMotorPower (1,150);
	cout << "Lichtschranke 1: " << g_pSeriell->GetPhotoSensorData(1) << endl;
	//cout << "Betriebsspannung: " << g_pSeriell->GetBatteryVoltage() << endl;
	
	while (1==1) { 
	
		Scaner.Scan();
		
		//cout << "Berechnet: " << g_pSeriell->GetPMLDistance () << endl;
		/*g_pWiringPi->SendSeriellInt (6);
		nSeriellData[0] = g_pWiringPi->ReceiveSeriellData ();
		nSeriellData[1] = g_pWiringPi->ReceiveSeriellData ();
	nDaten = (nSeriellData[1] << 8) | nSeriellData[0];
		cout << "Daten des Sensors: " << nDaten << endl;
		cout << "-----------" << endl;
		usleep (500000); */
		
		/*for (int i=0;i<100;i++) {
		g_pNetwork->Send (g_pSeriell->GetInfraredDistance ());
		g_pSeriell->MovePML (1);
		usleep (30000);
		//cout << i << endl;
		}
		for (int i=0;i<100;i++) {
		g_pSeriell->MovePML (0);
		usleep (800);
		}
		g_pNetwork->Send (1025);*/
	}
	
	Log_File->Del ();
	g_pNetwork->Del ();
	g_pWiringPi->Del ();
	g_pSeriell->Del ();
	
	return 0;
}