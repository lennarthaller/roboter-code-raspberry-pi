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
  int I2CRead (int nDevice, int nRegister);
  void I2CWrite (int nDevice, int nRegister, int nData);
  int SendSeriellInt (int nData);
  int ReceiveSeriellData (void);
  int SeriellDataAvailable (void);
  long TimeSinceStart (void);
  int InitTimer (void);
  
  private:
  int m_nOwnSeriellAdress;
  unsigned long long m_nTimerToZero;
};

#endif
