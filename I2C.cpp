#include "I2C.hpp"

int CI2C::InitI2C () {
	Log_File->WriteTopic ("Init I2C bus", 1);
	m_bError = false;

	m_nCompassAdress = wiringPiI2CSetup (0x60); //initialisation of the cmps10
	if (m_nCompassAdress == -1) {
		Log_File->Textout (RED, "Failed to initialise the compass!");
		m_bError = true;
	}

	m_nLidarAdress = wiringPiI2CSetup (0x62); //initialisation of the LiDAR
	if (m_nLidarAdress == -1) {
		Log_File->Textout (RED, "Failed to initialise the LiDAR!");
		m_bError = true;
	}else{
		I2CWrite (m_nLidarAdress, 0, 0); //set LiDAR acquisition count (128 = default)
	}

	if (m_bError == false) {
		Log_File->Textout (BLACK, "I2C bus initialised.");
		return 1;
	}else{
		return -1;
	}
}

int CI2C::InitWiringPi () {
Log_File->WriteTopic ("Init WiringPi", 1);

if (wiringPiSetup () == -1) { //wiringPi initalisation
	Log_File->Textout (RED, "Failed to initialise WiringPi!");
	return -1;
  }else{
	Log_File->Textout (BLACK, "WiringPi initialised.");
  }
return 1;
}

float CI2C::GetCompassData () {
	return static_cast<float>  (((wiringPiI2CReadReg8 (m_nCompassAdress, 2) << 8) | wiringPiI2CReadReg8 (m_nCompassAdress, 3)) / 10);
}

void CI2C::StartLidarMeasurement () {
	I2CWrite (m_nLidarAdress, 0, 4);
}

int CI2C::GetLidarDistance () {
	return ((wiringPiI2CReadReg8 (m_nLidarAdress, 15) << 8) | wiringPiI2CReadReg8 (m_nLidarAdress, 16));
}

void CI2C::I2CWrite (int nDevice, int nRegister, int nData) {
	if ((nData < 256)&&(nData > -1)) {
		wiringPiI2CWriteReg8 (nDevice, nRegister, nData);
	}else{
		std::cout << "ZU GROSSE ZAHL! (I2C)" << std::endl;
	}
}