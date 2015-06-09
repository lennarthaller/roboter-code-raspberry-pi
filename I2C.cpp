#include "I2C.hpp"

int CI2C::InitI2C () {
	Log_File->WriteTopic ("Init I2C bus", 1);
	m_bError = false;
	
	m_nCompassAdress = wiringPiI2CSetup (0x60); //initalisieren des cmps10
	if (m_nCompassAdress == -1) {
		Log_File->Textout (RED, "Failed to initialize the compass!");
		m_bError = true;
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
