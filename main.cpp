#include <iostream>
#include <unistd.h>
#include <cmath>
#include <sstream> //lib for stringstream

#include "Seriell.hpp"
#include "Network.hpp"
#include "Tracer.hpp"
#include "BasicFunktions.hpp"
#include "I2C.hpp"

int main (int argc, char* argv[]) {

	std::istringstream ss(argv[1]);
	int debugLevel;

if ((argc != 2)||(!(ss >> debugLevel))) { //Checking if the cmd line parameter was valid
	std::cout << "You have to specify a valid debug level (0-3)." << std::endl;
	std::cout << "Exiting." << std::endl;
	return 0;
}else{
	if ((debugLevel < 0)||(debugLevel > 3)) { //Checking if the cmd line parameter is in range
		std::cout << "You have to specify a valid debug level (0-3)." << std::endl;
		std::cout << "Exiting." << std::endl;
		return 0;
	}else{
		g_pTracer->TracerInit(debugLevel);
	}
}

	g_pTracer->Trace (NOTE, "Robot operation programm v0.1");
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

	g_pTracer->Trace (DEBUG, "Current operating voltage: " + std::to_string(g_pSeriell->GetBatteryVoltage()));

	for (int i=1; i<5; i++) {
		g_pSeriell->SetMotorPower(i, 0);
		g_pSeriell->GetPhotoSensorData(i); // init readout
	}

	while (1==1) {
		//cout << "Aktuelle Entfernung zu naechstem Hinderniss: " << g_pSeriell->GetInfraredDistance () << endl;
		//cout << "Betriebsspannung: " << g_pSeriell->GetBatteryVoltage() << endl;
		//cout << endl;
		/*usleep (200000);
		g_pI2C->StartLidarMeasurement ();
		usleep (300000);
		std::cout << g_pI2C->GetLidarDistance () << std::endl;  */
		g_pCBasicFunktions->UpdatePhotoSensors ();
		g_pCBasicFunktions->UpdateLaserScanner ();
		g_pCBasicFunktions->CountLoopTicks ();
		g_pCBasicFunktions->ManageNetwork ();
		g_pCBasicFunktions->UpdateBatteryVoltage ();
	}
	g_pNetwork->Del ();
	g_pSeriell->Del ();
	g_pKnowledgeBase->Del ();
	g_pBasicCalculations->Del ();

	return 0;
}
