#ifndef BASICFUNKTIONS_HPP
#define BASICFUNKTIONS_HPP

#include "WiringPi.hpp"
#include "Singleton.hpp"
#include "KnowledgeBase.hpp"
#include "Seriell.hpp"
#include "BasicCalculations.hpp"

#define g_pCBasicFunktions CBasicFunktions::Get()

class CBasicFunktions : public TSingleton<CBasicFunktions>
{
  public:
  CBasicFunktions ();
  
  void UpdateSensorData ();  
  
  private:
  std::clock_t m_nTimeStampSinceLastCall;
  
};

#endif
