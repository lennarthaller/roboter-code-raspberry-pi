#ifndef TRACER_HPP
#define TRACER_HPP

#include <iostream>
#include <sstream>
#include "Singleton.hpp"
#include "Logfile.hpp"

#define g_pTracer CTracer::Get()
#define TEXT std::ostringstream Text
enum DEBUGLEVEL
{
    ERROR,
    WARNING,
    NOTE,
    DEBUG
};

class CTracer : public TSingleton<CTracer>
{
  public:
  int TracerInit (int nDebugLevel);
  void TracerEnd ();
  void Trace (int DebugLevel, std::string Text);

  private:
  Clogfile *Logfile;
  bool m_bIsInitialised;
  int m_nSelectedDebugLevel;

};

#endif
