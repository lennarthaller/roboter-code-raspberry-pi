#ifndef TIM551DRIVER_HPP
#define TIM551DRIVER_HPP

#include <libusb.h>
#include <string.h>
#include <vector>

#include "Tracer.hpp"
#include "KnowledgeBase.hpp"

class CTiM551Driver
{
  public:
    int InitLaserScanner ();
    int UpdateData ();
    unsigned short int* GetCurrentData () {return m_nDistanceValue;}

  private:
   int sendSOPASCommand (const char *request, std::vector<char *> &Fields, bool ReturnData);

    // libusb
    libusb_context *ctx;
    ssize_t numberOfDevices;
    libusb_device_handle *device_handle;

    unsigned short int m_nDistanceValue[271];

};
#endif
