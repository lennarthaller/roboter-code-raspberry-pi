#ifndef I2C_HPP
#define I2C_HPP

#include <iostream>
#include "Singleton.hpp"
#include "Logfile.hpp"
#include "WiringPi.hpp"

#define g_pI2C CI2C::Get()

class CI2C : public TSingleton<CI2C>
{
  public:
	int InitI2C (void);
	float GetCompassData (void);
	void StartLidarMeasurement (void);
	int GetLidarDistance (void);
	
  private:
	int m_nCompassAdress;
	int m_nLidarAdress;
	bool m_bError;
};

#endif
