#ifndef TIM551DRIVER_HPP
#define TIM551DRIVER_HPP

#include <iostream>
#include <libusb.h>
/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
*/

class CTiM551Driver
{
  public:
    int InitLaserScanner ();
    int CloseLaserScanner ();

  private:

    // libusb
    libusb_context *ctx_;
    ssize_t numberOfDevices_;
    libusb_device **devices_;
    libusb_device_handle *device_handle_;

};
#endif
