#include "Seriell.hpp"

//Diese Funktion wartet 200 mSec auf verfügbare Seriell Daten
int CSeriell::DataAvailableNoTimeOut () {
	long nTimeStamp = g_pWiringPi->TimeSinceStart();

	while (g_pWiringPi->SeriellDataAvailable() < 1) {
		if (nTimeStamp+200 < g_pWiringPi->TimeSinceStart()) {
			Log_File->WriteTopic ("Datenuebertragung Raspberry Pi - Atmega32", 1);
			Log_File->Textout (RED, "Timeout bei dem Uebertragen von Daten.");
			return -1;
		}
	}
	return 1;
}

int CSeriell::GetInfraredDistance () {
	int nData = 0;
	
	g_pWiringPi->SendSeriellInt (0);
	
	if (DataAvailableNoTimeOut () == -1) {
		return -1;
	}
	
	if (g_pWiringPi->ReceiveSeriellData () == 0) {
		nData = g_pWiringPi->ReceiveSeriellData ();
		if (nData == 255) {
			//std::cout << "FEHLERHAFTE IR MESSUNG!" << std::endl;
			return -1;
		}else{
		return nData;
		}
	}else{
		Log_File->WriteTopic ("Datenuebertragung Raspberry Pi - Atmega32", 1);
		Log_File->Textout (RED, "Fehler bei dem Uebertragen von Daten.");
		return -1;
	}
}

int CSeriell::GetPhotoSensorData (const int nPhotoSensor) {
	int nSeriellData[2];
	
	if ((nPhotoSensor < 1)||(nPhotoSensor > 4)) {
		std::cout << "FALSCHE LICHTSCHRANKEN NUMMER!" << std::endl;
		return -1;
	}
	
	g_pWiringPi->SendSeriellInt (nPhotoSensor);
	
	if (DataAvailableNoTimeOut () == -1) {
		return -1;
	}
	
	if (g_pWiringPi->ReceiveSeriellData () == nPhotoSensor) {
		nSeriellData[0] = g_pWiringPi->ReceiveSeriellData ();
		nSeriellData[1] = g_pWiringPi->ReceiveSeriellData ();
		return ((nSeriellData[1] << 8 ) | nSeriellData[0]);
	}else{
		Log_File->WriteTopic ("Datenuebertragung Raspberry Pi - Atmega32", 1);
		Log_File->Textout (RED, "Fehler bei dem Uebertragen von Daten.");
		return -1;
	}
}

float CSeriell::GetBatteryVoltage () {
	float fData = 0;
	int nSeriellData[2];
	
	g_pWiringPi->SendSeriellInt (5);
	
	if (DataAvailableNoTimeOut () == -1) {
		return -1;
	}
	
	if (g_pWiringPi->ReceiveSeriellData () == 5) {
		nSeriellData[0] = g_pWiringPi->ReceiveSeriellData ();
		nSeriellData[1] = g_pWiringPi->ReceiveSeriellData ();
		fData = (nSeriellData[1] << 8 ) | nSeriellData[0];
		
		if (fData == 255) {
			Log_File->WriteTopic ("Datenuebertragung Atmega32 - Sensor", 1);
			Log_File->Textout (RED, "ATmega32 kann die Batteriespannung nicht messen.");
			return -1;
		}else{
		return (fData*0.028); //Batteriespannung berechnen
		}
	}else{
		Log_File->WriteTopic ("Datenuebertragung Raspberry Pi - Atmega32", 1);
		Log_File->Textout (RED, "Fehler bei dem Uebertragen von Daten.");
		return -1;
	}
}

int CSeriell::SetMotorPower (const int nMotor, const int nPower) {
	int nSeriellData[2];
	nSeriellData[0] = nPower;
	nSeriellData[1] = (nPower >> 8);
	
	if ((nMotor < 1)||(nMotor > 4)) {
		std::cout << "FALSCHE MOTOR NUMMER!" << std::endl;
		return -1;
	}
	
	if ((nPower < -255)||(nPower > 255)) {
		std::cout << "FALSCHE NUMMER FUER DIE MOTORKRAFT!" << std::endl;
		return -1;
	}
	
	g_pWiringPi->SendSeriellInt (nMotor+20);
	
	if (DataAvailableNoTimeOut () == -1) {
		return -1;
	}
	
	if (g_pWiringPi->ReceiveSeriellData () == (nMotor+20)) {
		g_pKnowledgeBase->SetCurrentMotorPower (nPower, nMotor);
		g_pWiringPi->SendSeriellInt (nSeriellData[0]);
		g_pWiringPi->SendSeriellInt (nSeriellData[1]);
	}else{
		Log_File->WriteTopic ("Datenuebertragung Raspberry Pi - Atmega32", 1);
		Log_File->Textout (RED, "Fehler bei dem Uebertragen von Daten.");
		return -1;
	}
	return 1;
}

int CSeriell::MovePML (const int nDirection) { //1 Dreht das PML in Fahrtrichtung links
	if ((nDirection < 0)||(nDirection > 1)) {
		std::cout << "FALSCHE NUMMER FUER DIE RICHTUNG!" << std::endl;
		return -1;
	}
	
	g_pWiringPi->SendSeriellInt (20);
	
	if (DataAvailableNoTimeOut () == -1) {
		return -1;
	}
	
	if (g_pWiringPi->ReceiveSeriellData () == 20) {
		g_pWiringPi->SendSeriellInt (nDirection);
	}else{
		Log_File->WriteTopic ("Datenuebertragung Raspberry Pi - Atmega32", 1);
		Log_File->Textout (RED, "Fehler bei dem Uebertragen von Daten.");
		return -1;
	}
	return 1;
}