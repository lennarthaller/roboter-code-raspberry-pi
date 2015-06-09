#include "WiringPi.hpp"

int CWiringPi::InitWiringPi () {
	
Log_File->WriteTopic ("Init WiringPi", 1);

if (wiringPiSetup () == -1) { //wiringPi initalisierung
	Log_File->Textout (RED, "Failed to initialize WiringPi!");
	return -1;
  }else{
	Log_File->Textout (BLACK, "WiringPi initialized.");
  }
  m_nOwnSeriellAdress = serialOpen ("/dev/ttyAMA0", 38400); //initalisierung der rs232 Schnittstelle
return 1;
}

int CWiringPi::I2CRead (int nDevice, int nRegister) {
	return wiringPiI2CReadReg8 (nDevice, nRegister);
}

void CWiringPi::I2CWrite (int nDevice, int nRegister, int nData) {
	if ((nData < 256)&&(nData > -1)) {
		wiringPiI2CWriteReg8 (int nDevice, int nRegister, int nData);
	}else{
		std::cout << "ZU GROSSE ZAHL! (I2C)" << std::endl;
	}
}

int CWiringPi::SendSeriellInt (int nData) {
	if ((nData < 256)&&(nData > -1)) {
		serialPutchar (m_nOwnSeriellAdress, static_cast<char> (nData));	
		return 1;
	}
	std::cout << "ZU GROSSE ZAHL! (SERIELL)" << std::endl;
	return -1;
}

int CWiringPi::ReceiveSeriellData () {
	return static_cast<int> (serialGetchar (m_nOwnSeriellAdress));
 }
 
 int CWiringPi::SeriellDataAvailable () {
	return serialDataAvail (m_nOwnSeriellAdress); 
 }
 
long CWiringPi::TimeSinceStart () {
	timespec Time;
	if (clock_gettime (CLOCK_REALTIME, &Time) == -1) {
		std::cout << "ERROR: SYSTEM CLOCK OFFLINE" << std::endl;
	}	
	//return (((Time.tv_sec - 1429623010) * 10000) + Time.tv_nsec / 100000);
	return (((Time.tv_sec - m_nTimerToZero) * 10000) + Time.tv_nsec / 100000);
}

int CWiringPi::InitTimer () {
	Log_File->WriteTopic ("Init system timer", 1);
	timespec Time;
	if (clock_gettime (CLOCK_REALTIME, &Time) == -1) {
		Log_File->Textout (RED, "Failed to initialize the timer!");
		return -1;
	}	
	m_nTimerToZero = Time.tv_sec;
	Log_File->Textout (BLACK, "Sytem timer initialized.");
	return 1;
}