#include <iostream>
#include <unistd.h>
#include <cmath>

#include "Seriell.hpp"
#include "Network.hpp"
#include "Logfile.hpp"
#include "Lidar.hpp"
#include "BasicFunktions.hpp"
#include "I2C.hpp"

using namespace std;

int main () {
	Log_File->CreateLogfile();
	
	cout << "Roboter test Programm v0.1" << endl;
	cout << "von" << endl << "Lennart Haller" << endl;

	if (g_pI2C->InitWiringPi() != 1) {
		cout << "Fehler" << endl;
	}
	
	if (g_pTimer->InitTimer() != 1) {
		cout << "Fehler" << endl;
	}
	
	if (g_pSeriell->InitSeriell() != 1) {
		cout << "Fehler" << endl;
	}
	
	if (g_pNetwork->InitNetwork () != 1) {
		cout << "Fehler" << endl;
	}
	
	if (g_pI2C->InitI2C() != 1) {
		cout << "Fehler" << endl;
	}

	CLidar Lidar;
	
	/*if (g_pNetwork->ConnectToClient () != 1) {
		cout << "Fehler" << endl;
	}*/ 
	
	//cout << "Aktuelle Entfernung zu naechstem Hinderniss: " << g_pSeriell->GetInfraredDistance () << endl;
	//cout << "Atueller Kompas Wert: " << g_pWiringPi->GetCompassData() << endl;
	//g_pSeriell->SetMotorPower (1,150);
	//cout << "Lichtschranke 1: " << g_pSeriell->GetPhotoSensorData(1) << endl;
	cout << "Betriebsspannung: " << g_pSeriell->GetBatteryVoltage() << endl;
	
	for (int i=0; i<4; i++) {
		g_pSeriell->SetMotorPower(i+1, 0);
		int a = g_pSeriell->GetPhotoSensorData(i+1); // init readout
	}
	
	while (1==1) { 
		//cout << "Aktuelle Entfernung zu naechstem Hinderniss: " << g_pSeriell->GetInfraredDistance () << endl;
		//cout << "Betriebsspannung: " << g_pSeriell->GetBatteryVoltage() << endl;
		//cout << endl;
		/*usleep (200000); 
		g_pI2C->StartLidarMeasurement ();
		usleep (300000); 
		std::cout << g_pI2C->GetLidarDistance () << std::endl; */
		
		Lidar.Scan();
		g_pCBasicFunktions->UpdateSensorData ();
		g_pCBasicFunktions->CountLoopTicks ();
	}
	
	Log_File->Del ();
	g_pNetwork->Del ();
	g_pSeriell->Del ();
	g_pKnowledgeBase->Del ();
	g_pBasicCalculations->Del ();
	
	return 0;
}