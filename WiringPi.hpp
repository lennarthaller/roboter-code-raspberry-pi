#ifndef WIRINGPI_HPP
#define WIRINGPI_HPP

#include <iostream>
#include "Singleton.hpp"
#include "Logfile.hpp"
#include <stdint.h>
#include <wiringPi.h>
#include <wiringSerial.h>
#include <wiringPiI2C.h>
#include <time.h>

#define g_pWiringPi CWiringPi::Get()

class CWiringPi : public TSingleton<CWiringPi>
{
  public:  
  int InitWiringPi (void);
  int SendSeriellInt (int nData);
  int ReceiveSeriellData (void);
  int SeriellDataAvailable (void);
  float GetCompassData (void);
  long TimeSinceStart (void);
  
  private:
  int m_nOwnSeriellAdress;
  int m_nCompassAdress;
};

#endif
