#include "Tracer.hpp"

int CTracer::TracerInit (int nDebugLevel) {
  if (m_bIsInitialised == false) {
    Logfile = new Clogfile ();
    Logfile->CreateLogfile();
    m_bIsInitialised = true;
    m_nSelectedDebugLevel = nDebugLevel;
    return 0;
  }else{
    return 1;
  }
}

void CTracer::Trace (int DebugLevel, std::string Text) {
  std::string message;
  switch (DebugLevel)
{
      case ERROR: {
        message = "[ERROR]: ";
        message.append (Text);
        std::cout << message << std::endl;
        Logfile->Textout (RED, message);
        break;
      }

      case WARNING: {
        message = "[WARNING]: ";
        message.append (Text);
        if (m_nSelectedDebugLevel >= WARNING) {
            std::cout << message << std::endl;
        }
        Logfile->Textout (ORANGE, message);
        break;
      }

      case NOTE: {
        message = "[NOTE]: ";
        message.append (Text);
        if (m_nSelectedDebugLevel >= NOTE) {
            std::cout << message << std::endl;
        }
        Logfile->Textout (BLUE, message);
        break;
      }

      case DEBUG: {
        message = "[DEBUG]: ";
        message.append (Text);
        if (m_nSelectedDebugLevel >= DEBUG) {
            std::cout << message << std::endl;
        }
        Logfile->Textout (BLACK, message);
        break;
      }
  };
}

void CTracer::TracerEnd () {
    Trace (NOTE, "Ending Tracing.");
  	delete Logfile;
}