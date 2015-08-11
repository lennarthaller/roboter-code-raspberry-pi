#ifndef I2C_HPP
#define I2C_HPP

#include <iostream>
#include "Singleton.hpp"
#include "Tracer.hpp"

#include <wiringPiI2C.h>
#include <wiringPi.h>

#define g_pI2C CI2C::Get()

class CI2C : public TSingleton<CI2C>
{
  public:
	int InitI2C (void);
	int InitWiringPi (void);
	float GetCompassData (void);
	void StartLidarMeasurement (void);
	int GetLidarDistance (void);

  private:
	int I2CRead (int nDevice, int nRegister);
	void I2CWrite (int nDevice, int nRegister, int nData);

	int m_nCompassAdress;
	int m_nLidarAdress;
	bool m_bError;
};

#endif
