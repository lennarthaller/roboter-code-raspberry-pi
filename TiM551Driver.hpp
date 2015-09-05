#ifndef TIM551DRIVER_HPP
#define TIM551DRIVER_HPP

#include <iostream>
//#include <libusb-1.0/libusb.h>
#include <libusb.h>
#include <string.h>
#include <vector>
//#include <stdio.h>

/*#include <stdlib.h>
*/

#include "Tracer.hpp"

class CTiM551Driver
{
  public:
    int InitLaserScanner ();
    int CloseLaserScanner ();
    int GetData ();

  private:
   int sendSOPASCommand (const char *request, std::vector<unsigned char> &reply);

    // libusb
    libusb_context *ctx;
    ssize_t numberOfDevices;
    libusb_device_handle *device_handle;

};
#endif
