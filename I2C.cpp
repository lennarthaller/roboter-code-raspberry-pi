#include "I2C.hpp"

int CI2C::InitI2C () {
	Log_File->WriteTopic ("Init I2C bus", 1);
	m_bError = false;
	
	m_nCompassAdress = wiringPiI2CSetup (0x60); //initialisation of the cmps10
	if (m_nCompassAdress == -1) {
		Log_File->Textout (RED, "Failed to initialize the compass!");
		m_bError = true;
	}
	
	m_nLidarAdress = wiringPiI2CSetup (0x62); //initialisation of the LiDAR
	if (m_nLidarAdress == -1) {
		Log_File->Textout (RED, "Failed to initialize the LiDAR!");
		m_bError = true;
	}else{
		g_pWiringPi->I2CWrite (m_nLidarAdress, 2, 128); //set LiDAR acquisition count (128 = default)
	}
	
	if (m_bError == false) {
		Log_File->Textout (BLACK, "I2C bus initialized.");
		return 1;
	}else{
		return -1;
	}
}

float CI2C::GetCompassData () {
	return static_cast<float>  (((g_pWiringPi->I2CRead (m_nCompassAdress, 2) << 8) | g_pWiringPi->I2CRead (m_nCompassAdress, 3)) / 10);
}

void CI2C::StartLidarMeasurement () {
	g_pWiringPi->I2CWrite (m_nLidarAdress, 0, 4);
}

int CI2C::GetLidarDistance () {
	return ((g_pWiringPi->I2CRead (m_nLidarAdress, 15) << 8) | g_pWiringPi->I2CRead (m_nLidarAdress, 16));
}