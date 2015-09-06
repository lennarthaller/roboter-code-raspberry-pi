#include "TiM551Driver.hpp"

int CTiM551Driver::InitLaserScanner () {

 int nResult = libusb_init (&ctx);
 if (nResult != 0) {
   g_pTracer->Trace (ERROR, "Failed to initialise Libusb.");
   return -1;
 }

  libusb_set_debug(ctx, 3); //Set the verbosity level to 3 as suggested in the documentation

 const int nVendorID = 0x19A2; // SICK AG
 const int nDeviceID = 0x5001; // TIM3XX
 device_handle = libusb_open_device_with_vid_pid (ctx, nVendorID, nDeviceID); //If available, open the first SICK TIM3xx device

 if (device_handle == NULL) {
   g_pTracer->Trace (ERROR, "Libusb cannot open the device.");
   return -1;
 }else{
   g_pTracer->Trace (NOTE, "Libusb connected to the TiM551.");
 }

 if (libusb_kernel_driver_active (device_handle, 0) == 1) {
   if (libusb_detach_kernel_driver(device_handle, 0) == 0) {
      g_pTracer->Trace (NOTE, "Libusb - kernel driver detached.");
   }
 }

 int result = libusb_claim_interface(device_handle, 0); //Claim the interface 0
 if (result < 0) {
   g_pTracer->Trace (ERROR, "Libusb could not claim the interface.");
   return -1;
 }

 g_pTracer->Trace (NOTE, "TiM551 was successfully initialised.");
 return 1;
}


int CTiM551Driver::sendSOPASCommand (const char *request, std::vector<char *> &Fields, bool ReturnData) {
  if (device_handle == NULL) {
    g_pTracer->Trace (ERROR, "Libusb - device not open.");
    return -1;
  }

  const int buffSize = 30000;
  int result = 0;
  unsigned char receiveBuffer[buffSize];
  int actual_length = 0;
  int requestLength = strlen(request);

  result = libusb_bulk_transfer(device_handle, (2 | LIBUSB_ENDPOINT_OUT), (unsigned char*)request, requestLength, &actual_length, 0);
  if (result != 0 || actual_length != requestLength) {
    g_pTracer->Trace (ERROR, "Libusb write error.");
    return -1;
  }

  result = libusb_bulk_transfer(device_handle, (1 | LIBUSB_ENDPOINT_IN), receiveBuffer, buffSize, &actual_length, 1000);
  if (result != 0) {
    g_pTracer->Trace (ERROR, "Libusb read error.");
    return -1;
  }

  if (ReturnData == true) {
    receiveBuffer[actual_length] = 0;

    //tokenize the data and store it in the vector
    char* buffer_pos = (char*)receiveBuffer;
    char *dstart, *dend;
    dstart = strchr (buffer_pos, 0x02);
    dend = strchr (dstart + 1, 0x03);
    size_t dlength = dend - dstart;
    *dend = '\0';
    dstart++;

    char* chCurrentField = strtok (dstart, " ");
    Fields.push_back (chCurrentField);
    while (chCurrentField != NULL) {
      chCurrentField = strtok(NULL, " ");
      Fields.push_back(chCurrentField);
    }
  }
  return 1;
}

int CTiM551Driver::UpdateData () {
  //Send the "requst one data set" SOPAS command
  const char requestScanData[] = {"\x02sRN LMDscandata\x03\0"};
  std::vector<char *> DataFromSensor;
  int result = sendSOPASCommand(requestScanData, DataFromSensor, true);
  if (result != 1)  {
    g_pTracer->Trace (ERROR, "Libusb - failed to receive scan.");
  }

  unsigned short int nNumberOfData = 0;
  sscanf(DataFromSensor.at(25), "%hx", &nNumberOfData);

  for (int i=0; i<nNumberOfData; i++) {
    sscanf(DataFromSensor.at(26+i), "%hx", &m_nDistanceValue[i]);
  }

  return 1;
}
