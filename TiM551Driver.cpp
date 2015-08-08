#include "TiM551Driver.hpp"

int CTiM551Driver::InitLaserScanner () {

  Log_File->WriteTopic ("Initialising the SICk TiM551", 1);

 int nResult = libusb_init (&ctx);
 if (nResult != 0) {
   Log_File->Textout (RED, "Failed to initialise Libusb!");
 }

  libusb_set_debug(ctx_, 3); //Set the verbosity level to 3 as suggested in the documentation

 int vendorID = 0x19A2; // SICK AG
 int deviceID = 0x5001; // TIM3XX
 libusb_device_handle = libusb_open_device_with_vid_pid (ctx, 0x19A2, 0x5001); //If available, open the first SICK TIM3xx device

 if (device_handle == NULL) {
   Log_File->Textout (RED, "Libusb cannot open the device!");
 }else{
   Log_File->Textout (BLACK, "Libusb opened the device.");
 }

 if (libusb_kernel_driver_active (device_handle, 0) == 1) {
   if (libusb_detach_kernel_driver(device_handle, 0) == 0) {
     Log_File->Textout (BLACK, "Libusb - Kernel driver detached.");
   }
 }

 result = libusb_claim_interface(device_handle, 0); //Claim the interface 0
 if (result < 0) {
   Log_File->Textout (RED, "Libusb cannot claim the interface!");
 }

 Log_File->Textout (BLACK, "TiM551 was succesfully initialised.");
 return 0;
}

int CTiM551Driver::CloseLaserScanner () {

}
