#include <iostream>

#include "Seriell.hpp"
#include "Network.hpp"
#include "Logfile.hpp"

using namespace std;

int main () {
	Log_File->CreateLogfile();
	
	cout << "Roboter test Programm v0.1" << endl;
	cout << "von" << endl << "Lennart Haller" << endl;
	
	//wiringPi init
	if (g_pWiringPi->InitWiringPi() != 1) {
		cout << "Fehler" << endl;
	}else{
	}
	
	if (g_pNetwork->InitNetwork () != 1) {
		cout << "Fehler" << endl;
	}
	
	//cout << "Aktuelle Entfernung zu naechstem Hinderniss: " << g_pSeriell->GetPMLDistance () << endl;
	//cout << "Atueller Kompas Wert: " << g_pWiringPi->GetCompassData() << endl;
	//g_pSeriell->SetMotorPower (1,150);
	
	cout << "Lichtschranke 1: " << g_pSeriell->GetPhotoSensorData(1) << endl;
	cout << "Betriebsspannung: " << g_pSeriell->GetBatteryVoltage() << endl;
	
	Log_File->Del ();
	g_pNetwork->Del ();
	g_pWiringPi->Del ();
	g_pSeriell->Del ();
	
	return 0;
}