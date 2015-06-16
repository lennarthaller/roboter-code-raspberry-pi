#ifndef SEREIELL_HPP
#define SEREIELL_HPP

#include <iostream>
#include "Singleton.hpp"
#include "Logfile.hpp"
#include "Timer.hpp"
#include "KnowledgeBase.hpp"

#include <wiringSerial.h>

#define g_pSeriell CSeriell::Get()

class CSeriell : public TSingleton<CSeriell>
{
  public:
  int InitSeriell (void);
  int GetPhotoSensorData (const int nPhotoSensor);
  float GetBatteryVoltage (void);
  int SetMotorPower (const int nMotor, const int nPower);
  int MovePML (const int nDirection);
  
  private:
  int DataAvailableNoTimeOut (void);
  int SendSeriellInt (int nData);
  int ReceiveSeriellData (void);
  
  int m_nOwnSeriellAdress;
};

#endif
