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

#include <iostream>

#define g_pCBasicFunktions CBasicFunktions::Get()

class CBasicFunktions : public TSingleton<CBasicFunktions>
{
  public:
  CBasicFunktions ();
  
  void UpdateSensorData (); 
  void CountLoopTicks ();
  
  private:
  double m_nTimeStampSinceLastCallSensorUpdate;
  double m_nTimeStampSinceLastCallLoopTicks;
  double m_nTimeStampSinceLastCallSensorUpdateOdometry;
  int 	 m_nLoopTicks;
  
  CNetworkProtocol NetworkProtocol;
  
};

#endif
