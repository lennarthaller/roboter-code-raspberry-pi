#ifndef SEREIELL_HPP
#define SEREIELL_HPP

#include <iostream>
#include "Singleton.hpp"
#include "Logfile.hpp"
#include "WiringPi.hpp"

#define g_pSeriell CSeriell::Get()

class CSeriell : public TSingleton<CSeriell>
{
  public:
  int GetPMLDistance (void);
  int GetPhotoSensorData (const int nPhotoSensor);
  float GetBatteryVoltage (void);
  int SetMotorPower (const int nMotor, const int nPower);
  int MovePML (const int nDirection);
  
  private:
  int DataAvailableNoTimeOut (void);
};

#endif
