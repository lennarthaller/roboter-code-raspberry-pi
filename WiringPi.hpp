#ifndef WIRINGPI_HPP
#define WIRINGPI_HPP

#include <iostream>
#include "Singleton.hpp"
#include "Logfile.hpp"
#include <stdint.h>
#include <wiringPi.h>
#include <wiringSerial.h>
#include <wiringPiI2C.h>
#include <ctime>

//#define CLOCKS_PER_SEC  1000

#define g_pWiringPi CWiringPi::Get()

class CWiringPi : public TSingleton<CWiringPi>
{
  public:
  int InitWiringPi (void);
  int SendSeriellInt (int nData);
  int ReceiveSeriellData (void);
  int SeriellDataAvailable (void);
  float GetCompassData (void);
  clock_t TimeSinceStart (void);
  
  private:
  int m_nOwnSeriellAdress;
  int m_nCompassAdress;
};

#endif
