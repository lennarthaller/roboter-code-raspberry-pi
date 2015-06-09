#ifndef I2C_HPP
#define I2C_HPP

#include <iostream>
#include "Singleton.hpp"
#include "Logfile.hpp"
#include "WiringPi.hpp"

#define g_pI2C CI2C::Get()

class I2C : public TSingleton<I2C>
{
  public:
	int InitI2C (void);
	float GetCompassData (void);
	
  private:
	int m_nCompassAdress;
	bool m_bError;
};

#endif
