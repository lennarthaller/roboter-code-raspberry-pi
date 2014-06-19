#include "Seriell.hpp"

//Diese Funktion wartet 200 mSec auf verfügbare Seriell Daten
int CSeriell::DataAvailableNoTimeOut () {
clock_t nTimeStamp = g_pWiringPi->TimeSinceStart();

while (g_pWiringPi->SeriellDataAvailable() < 1) {
		if (nTimeStamp+200 < g_pWiringPi->TimeSinceStart()) {
			Log_File->WriteTopic ("Datenuebertragung Raspberry Pi - Atmega32", 1);
			Log_File->Textout (RED, "Timeout bei dem Uebertragen von Daten.");
			return -1;
		}
	}
	return 1;
}

int CSeriell::GetPMLDistance () {
	int nData = 0;
	
	g_pWiringPi->SendSeriellInt (0);
	
	if (DataAvailableNoTimeOut () == -1) {
		return -1;
	}
	
	if (g_pWiringPi->ReceiveSeriellData () == 0) {
		nData = g_pWiringPi->ReceiveSeriellData ();
		if (nData == 255) {
			Log_File->WriteTopic ("Datenuebertragung Atmega32 - Sensor", 1);
			Log_File->Textout (RED, "Atmega32 hat keine Verbinung zu dem PML Sensor.");
			return -1;
		}else{
		return nData;
		}
	}else{
		Log_File->WriteTopic ("Datenuebertragung Raspberry Pi - Atmega32", 1);
		Log_File->Textout (RED, "Fehler bei dem Übertragen von Daten.");
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
		Log_File->Textout (RED, "Fehler bei dem Übertragen von Daten.");
		return -1;
	}
}

int CSeriell::GetBatteryVoltage () {
	int nData = 0;
	
	g_pWiringPi->SendSeriellInt (5);
	
	if (DataAvailableNoTimeOut () == -1) {
		return -1;
	}
	
	if (g_pWiringPi->ReceiveSeriellData () == 5) {
		nData = g_pWiringPi->ReceiveSeriellData ();
		if (nData == 255) {
			Log_File->WriteTopic ("Datenuebertragung Atmega32 - Sensor", 1);
			Log_File->Textout (RED, "ATmega32 kann die Batteriespannung nicht messen.");
			return -1;
		}else{
		return nData;
		}
	}else{
		Log_File->WriteTopic ("Datenuebertragung Raspberry Pi - Atmega32", 1);
		Log_File->Textout (RED, "Fehler bei dem Übertragen von Daten.");
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
	
	if (g_pWiringPi->ReceiveSeriellData () == nMotor) { //nicht nMotor+20?
		g_pWiringPi->SendSeriellInt (nSeriellData[0]);
		g_pWiringPi->SendSeriellInt (nSeriellData[1]);
	}else{
		Log_File->WriteTopic ("Datenuebertragung Raspberry Pi - Atmega32", 1);
		Log_File->Textout (RED, "Fehler bei dem Übertragen von Daten.");
		return -1;
	}
	return 1;
}

int CSeriell::SetPMLPosition (int nPosition) {
	return 1;
}