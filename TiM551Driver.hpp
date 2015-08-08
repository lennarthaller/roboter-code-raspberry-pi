#ifndef TIM551DRIVER_HPP
#define TIM551DRIVER_HPP

#include <iostream>
#include <libusb.h>
/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
*/

#include "Logfile.hpp"

class CTiM551Driver
{
  public:
    int InitLaserScanner ();
    int CloseLaserScanner ();

  private:

    // libusb
    libusb_context *ctx;
    ssize_t numberOfDevices;
    libusb_device **devices;
    libusb_device_handle *device_handle;

};
#endif
