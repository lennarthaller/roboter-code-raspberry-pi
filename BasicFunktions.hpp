#ifndef BASICFUNKTIONS_HPP
#define BASICFUNKTIONS_HPP

#include "Timer.hpp"
#include "Network.hpp"
#include "Singleton.hpp"
#include "KnowledgeBase.hpp"
#include "Seriell.hpp"
#include "BasicCalculations.hpp"
#include "NetworkProtocol.hpp"
#include "MotorController.hpp"
#include "TiM551Driver.hpp"
#include "Tracer.hpp"

#include <iostream>

#define g_pCBasicFunktions CBasicFunktions::Get()

class CBasicFunktions : public TSingleton<CBasicFunktions>
{
  public:
  CBasicFunktions ();

  void UpdatePhotoSensors ();
  void CountLoopTicks ();
  void UpdateLaserScanner ();
  void ManageNetwork ();
  void UpdateBatteryVoltage ();

  private:
  double m_nTimeStampSinceLastCallPhotoSensorsUpdate;
  double m_nTimeStampSinceLastCallLoopTicks;
  double m_nTimeStampSinceLastCallSensorUpdateOdometry;
  double m_nTimeStampSinceLastCallSensorUpdateLaserScanner;
  double m_nTimeStampSinceLastCallNetwork;
  double m_nTimeStampSinceLastBatteryvoltage;
  int 	 m_nLoopTicks;

  CTiM551Driver     *LaserScanner;
  CNetworkProtocol  NetworkProtocol;
};

#endif
