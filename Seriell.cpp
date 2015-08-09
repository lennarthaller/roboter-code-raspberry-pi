#include "Seriell.hpp"

int CSeriell::InitSeriell () {
	Log_File->WriteTopic ("Initialising Seriell bus", 1);
	m_nOwnSeriellAdress = serialOpen ("/dev/ttyAMA0", 38400); //initalisierung der rs232 Schnittstelle

	if (m_nOwnSeriellAdress == -1) {
		Log_File->Textout (RED, "Failed to initialise the seriell bus!");
		return -1;
	}else{
		Log_File->Textout (BLACK, "Seriell bus initialised.");
		return 1;
	}
}

//Diese Funktion wartet 200 mSec auf verfügbare Seriell Daten
int CSeriell::DataAvailableNoTimeOut () {
	long nTimeStamp = g_pTimer->TimeSinceStart();

	while (serialDataAvail (m_nOwnSeriellAdress) < 1) {
		if (nTimeStamp+200 < g_pTimer->TimeSinceStart()) {
			Log_File->WriteTopic ("Communication Raspberry Pi - Atmega32", 1);
			Log_File->Textout (RED, "Communication error: timeout.");
			return -1;
		}
	}
	return 1;
}

int CSeriell::GetPhotoSensorData (const int nPhotoSensor) {
	if ((nPhotoSensor < 1)||(nPhotoSensor > 4)) {
		std::cout << "FALSCHE LICHTSCHRANKEN NUMMER!" << std::endl;
		return -1;
	}

	SendSeriellInt (nPhotoSensor);

	if (DataAvailableNoTimeOut () == -1) {
		return -1;
	}

	if (ReceiveSeriellData () == nPhotoSensor) {
		return ReceiveSeriellData ();
	}else{
		Log_File->WriteTopic ("Communication Raspberry Pi - Atmega32", 1);
		Log_File->Textout (RED, "Communication error.");
		return -1;
	}
}

float CSeriell::GetBatteryVoltage () {
	float fData = 0;
	int nSeriellData[2];

	SendSeriellInt (5);

	if (DataAvailableNoTimeOut () == -1) {
		return -1;
	}

	if (ReceiveSeriellData () == 5) {
		nSeriellData[0] = ReceiveSeriellData ();
		nSeriellData[1] = ReceiveSeriellData ();
		fData = (nSeriellData[1] << 8 ) | nSeriellData[0];

		if (fData == 255) {
			Log_File->WriteTopic ("Communication Atmega32 - Sensor", 1);
			Log_File->Textout (RED, "ATmega32 failed to measure the battary voltage.");
			return -1;
		}else{
		return (fData*0.028); //Batteriespannung berechnen
		}
	}else{
		Log_File->WriteTopic ("Communication Raspberry Pi - Atmega32", 1);
		Log_File->Textout (RED, "Communication error.");
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

	SendSeriellInt (nMotor+20);

	if (DataAvailableNoTimeOut () == -1) {
		return -1;
	}

	if (ReceiveSeriellData () == (nMotor+20)) {
		SendSeriellInt (nSeriellData[0]);
		SendSeriellInt (nSeriellData[1]);
	}else{
		Log_File->WriteTopic ("Communication Raspberry Pi - Atmega32", 1);
		Log_File->Textout (RED, "Communication error.");
		return -1;
	}
	return 1;
}

int CSeriell::MovePML (const int nDirection) { //1 Dreht das PML in Fahrtrichtung links
	if ((nDirection < 0)||(nDirection > 1)) {
		std::cout << "FALSCHE NUMMER FUER DIE RICHTUNG!" << std::endl;
		return -1;
	}

	SendSeriellInt (20);

	if (DataAvailableNoTimeOut () == -1) {
		return -1;
	}

	if (ReceiveSeriellData () == 20) {
		SendSeriellInt (nDirection);
	}else{
		Log_File->WriteTopic ("Communication Raspberry Pi - Atmega32", 1);
		Log_File->Textout (RED, "Communication error.");
		return -1;
	}
	return 1;
}

int CSeriell::SendSeriellInt (int nData) {
	if ((nData < 256)&&(nData > -1)) {
		serialPutchar (m_nOwnSeriellAdress, static_cast<char> (nData));
		return 1;
	}
	std::cout << "ZU GROSSE ZAHL! (SERIELL)" << std::endl;
	return -1;
}

int CSeriell::ReceiveSeriellData () {
	return static_cast<int> (serialGetchar (m_nOwnSeriellAdress));
 }
