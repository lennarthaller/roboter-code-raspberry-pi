#ifndef TIMER_HPP
#define TIMER_HPP

#include <iostream>
#include "Singleton.hpp"
#include "Tracer.hpp"
#include <time.h>

#define g_pTimer CTimer::Get()

class CTimer : public TSingleton<CTimer>
{
  public:  
  long TimeSinceStart (void);
  int InitTimer (void);
  
  private:
  unsigned long long m_nTimerToZero;
};

#endif
