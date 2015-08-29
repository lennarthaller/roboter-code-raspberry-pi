#include <iostream>
#include <unistd.h>
#include <cmath>
#include <cstdlib> //standart c lib for atoi

#include "Seriell.hpp"
#include "Network.hpp"
#include "Tracer.hpp"
#include "Lidar.hpp"
#include "BasicFunktions.hpp"
#include "I2C.hpp"

int main (int argc, char* argv[]) {

/*if ((argc != 2)||(atoi(argv[1] < 0))||(atoi(argv[1] > 3))) { //Checking if the cmd line parameter was valid
	std::cout << "You have to specify a valid debug level (0-3)." << std::endl;
	std::cout << "Exiting." << std::endl;
	return 0;
}else{ */
	g_pTracer->TracerInit(atoi(argv[1]));
//}

	g_pTracer->Trace (NOTE, "Roboter test Programm v0.1");
	g_pTracer->Trace (NOTE, "2015, Lennart Haller");

	if (g_pI2C->InitWiringPi() != 1) {
		g_pTracer->Trace (ERROR, "Failed to initialise WiringPi.");
	}

	if (g_pTimer->InitTimer() != 1) {
		g_pTracer->Trace (ERROR, "Failed to initialise the timer.");
	}

	if (g_pSeriell->InitSeriell() != 1) {
		g_pTracer->Trace (ERROR, "Failed to initialise the seriell driver.");
	}

	if (g_pNetwork->InitNetwork () != 1) {
		g_pTracer->Trace (ERROR, "Failed to initialise the network.");
	}

	if (g_pI2C->InitI2C() != 1) {
		g_pTracer->Trace (ERROR, "Failed to initialise the I2C driver.");
	}

	if (g_pNetwork->ConnectToClient () != 1) {
		g_pTracer->Trace (ERROR, "Failed to connect to the network client.");
	}

	CLidar Lidar;

	//cout << "Aktuelle Entfernung zu naechstem Hinderniss: " << g_pSeriell->GetInfraredDistance () << endl;
	//cout << "Atueller Kompas Wert: " << g_pWiringPi->GetCompassData() << endl;
	//g_pSeriell->SetMotorPower (1,150);
	//cout << "Lichtschranke 1: " << g_pSeriell->GetPhotoSensorData(1) << endl;
	g_pTracer->Trace (DEBUG, "Betriebsspannung: " + std::to_string(g_pSeriell->GetBatteryVoltage()));

	for (int i=1; i<5; i++) {
		g_pSeriell->SetMotorPower(i, 0);
		g_pSeriell->GetPhotoSensorData(i); // init readout
	}

	std::cout << "Test" << std::endl;

	while (1==1) {
		//cout << "Aktuelle Entfernung zu naechstem Hinderniss: " << g_pSeriell->GetInfraredDistance () << endl;
		//cout << "Betriebsspannung: " << g_pSeriell->GetBatteryVoltage() << endl;
		//cout << endl;
		/*usleep (200000);
		g_pI2C->StartLidarMeasurement ();
		usleep (300000);
		std::cout << g_pI2C->GetLidarDistance () << std::endl;  */
		Lidar.Scan();
		g_pCBasicFunktions->UpdateSensorData ();
		g_pCBasicFunktions->CountLoopTicks ();
	}
	g_pNetwork->Del ();
	g_pSeriell->Del ();
	g_pKnowledgeBase->Del ();
	g_pBasicCalculations->Del ();

	return 0;
}
