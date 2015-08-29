#include "TiM551Driver.hpp"

int CTiM551Driver::InitLaserScanner () {

  //Log_file->WriteTopic ("Initialising the SICk TiM551", 1);

 int nResult = libusb_init (&ctx);
 if (nResult != 0) {
   //Log_file->Textout (RED, "Failed to initialise Libusb!");
   return 1;
 }

  libusb_set_debug(ctx_, 3); //Set the verbosity level to 3 as suggested in the documentation

 const int nVendorID = 0x19A2; // SICK AG
 const int nDeviceID = 0x5001; // TIM3XX
 libusb_device_handle = libusb_open_device_with_vid_pid (ctx, 0x19A2, 0x5001); //If available, open the first SICK TIM3xx device

 if (device_handle == NULL) {
   //Log_file->Textout (RED, "Libusb cannot open the device!");
   return 1;
 }else{
   //Log_file->Textout (BLACK, "Libusb opened the device.");
 }

 if (libusb_kernel_driver_active (device_handle, 0) == 1) {
   if (libusb_detach_kernel_driver(device_handle, 0) == 0) {
     //Log_file->Textout (BLACK, "Libusb - Kernel driver detached.");
   }
 }

 result = libusb_claim_interface(device_handle, 0); //Claim the interface 0
 if (result < 0) {
   //Log_file->Textout (RED, "Libusb cannot claim the interface!");
   return 1;
 }

 //Log_file->Textout (BLACK, "TiM551 was succesfully initialised.");
 return 0;
}


int CTiM551Driver::sendSOPASCommand (const char *request) {
  if (device_handle == NULL) {
  //Log_file->Textout (RED, "Libusb - device not open!");
  return 1;
  }

  const int buffSize = 1000;
  int result = 0;
  unsigned char receiveBuffer[buffSize];
  int actual_length = 0;
  int requestLength = strlen(request);

  result = libusb_bulk_transfer(device_handle, (2 | LIBUSB_ENDPOINT_OUT), (unsigned char*)request, requestLength, &actual_length, 0);
  if (result != 0 || actual_length != requestLength) {
    //Log_file->Textout (RED, "Libusb write error.");
    return 1;
  }

  result = libusb_bulk_transfer(device_handle, (1 | LIBUSB_ENDPOINT_IN), receiveBuffer, buffSize, &actual_length, 1000);
  if (result != 0) {
  //Log_file->Textout (RED, "Libusb read error.");
  return 1;
  }

  return 0;
}

int CTiM551Driver::CloseLaserScanner () {

}
