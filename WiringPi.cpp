#include "WiringPi.hpp"

int CWiringPi::InitWiringPi () {
Log_File->WriteTopic ("Init WiringPi", 1);

if (wiringPiSetup () == -1) { //wiringPi initalisierung
	Log_File->Textout (RED, "WiringPi Setup Fehlgeschlagen!");
	return -1;
  }else{
	Log_File->Textout (BLACK, "WiringPi initialisiert.");
  }
  m_nOwnSeriellAdress = serialOpen ("/dev/ttyAMA0", 9600); //initalisierung der rs232 Schnittstelle
  m_nCompassAdress = wiringPiI2CSetup (0x60); //initalisieren des cmps10
return 1;
}

int CWiringPi::SendSeriellInt (int nData) {
	if ((nData < 256)&&(nData > -1)) {
	serialPutchar (m_nOwnSeriellAdress, static_cast<char> (nData));	
	return 1;
	}
	std::cout << "ZU GROSSE ZAHL!" << std::endl;
return -1;
}

int CWiringPi::ReceiveSeriellData () {
	return static_cast<int> (serialGetchar (m_nOwnSeriellAdress));
 }
 
 int CWiringPi::SeriellDataAvailable () {
	return serialDataAvail (m_nOwnSeriellAdress); 
 }
 
float CWiringPi::GetCompassData () {
	return static_cast<float>  (((wiringPiI2CReadReg8 (m_nCompassAdress, 2) << 8) | wiringPiI2CReadReg8 (m_nCompassAdress, 3)) / 10);
}

clock_t CWiringPi::TimeSinceStart () {
	return  (clock () / (CLOCKS_PER_SEC/1000));
}