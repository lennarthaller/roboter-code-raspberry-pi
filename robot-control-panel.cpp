#include <iostream>
#include <stdint.h>
#include <wiringPi.h>
#include <wiringSerial.h>
#include <wiringPiI2C.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

#define BUF_SIZ 4096

using namespace std;

void DataTransmit();
void RobotDrive();

int nFd = 0; 
 
int main (void) {

//char[] chData = 'Hallo Welt!\n';
int nData = 0;
int nCounter = 0;
char chEingabe;
int nSeriellData = 0;
int nRs232Data[2];
bool bUSARTDataToggle = false;
int nI2CDevice = 0;
float fAngel = 0;
int nI2CData[2];

if (wiringPiSetup () == -1) { //wiringPi initalisierung
    cout << "wiringPi konnte nicht initalisiert werden!";
	return 1;
  }
  
  nFd = serialOpen ("/dev/ttyAMA0", 4800); //initalisierung der rs232 Schnittstelle
  nI2CDevice = wiringPiI2CSetup (0x60); //initalisieren des cmps10
  
	do {
	cout << "\Robot Control Panel" << endl;
	cout << "--------------------" << endl;
	cout << "(S)s232 Senden" << endl;
	cout << "(L)s232 Lesen" << endl;
	cout << "(G)rosse Zahle lesen" << endl;
	cout << "(D)atenuebertragung starten" << endl;
	cout << "(A)uslesen des cmps10" << endl;
	cout << "(R)oboter starten" << endl;
	cout << "(I)nfo" << endl;
	cout << "(B)eenden\n\n";
	cin >> chEingabe;
	
	switch (chEingabe) {
	
	case ('s'):
	case ('S'): {
	cout << "Welche Zahl soll gesendet werden (0-255)?" << endl;
	cin >> nSeriellData;
	serialPutchar (nFd, nSeriellData);
	cout << endl << "Daten gesendet." << endl;
	} break;
	
	case ('l'):
	case ('L'): {
	cout << "Wieviele Bytes wollen sie lesen?" << endl;
	cin >> nData;
	cout << "\n----" << endl;
	while (nData >= nCounter) {
	if (serialDataAvail (nFd) > 0) {
	nSeriellData = serialGetchar (nFd);
	cout << endl << nSeriellData << endl;
	nCounter ++;
	}
	}
	} break;
	
	case ('g'):
	case ('G'): {
	cout << "Wieviele Bytes wollen sie lesen?" << endl;
	cin >> nData;
	cout << "\n----" << endl;
	while (nData >= nCounter) {
	if (serialDataAvail (nFd) > 0) {
	if (bUSARTDataToggle == false) {
	nRs232Data[0] = serialGetchar (nFd);
	bUSARTDataToggle = true;
	}else{
	nRs232Data[1] = serialGetchar (nFd);
	nSeriellData = ((nRs232Data[1] << 8 ) | nRs232Data[0]);
	cout << endl << nSeriellData << endl;
	nCounter ++;
	bUSARTDataToggle = false;
	}
	}
	}
	} break;
	
	case ('d'):
	case ('D'): {
	cout << "Datenübertragung wird gestartet." << endl;
	DataTransmit ();
	}break;
	
	case ('A'):
	case ('a'): {
	nI2CData[0] = wiringPiI2CReadReg8 (nI2CDevice, 3);
	nI2CData[1] = wiringPiI2CReadReg8 (nI2CDevice, 2);
	
	fAngel = static_cast<float>  ((nI2CData[1] << 8) | nI2CData[0]) / 10;
	cout << "Wert des Kompasses: " << fAngel << endl;
	}break;
	
	case ('R'):
	case ('r'): {
	cout << "Roboter wird gestarted.." << endl;
	RobotDrive();
	}break;
	
	case ('i'):
	case ('I'): {
	cout << "Robot Control Panel" << endl;
	cout << "Version 0.2.1" << endl;
	cout << "by Lennart Haller" << endl;
	} break;
   }
  } while (chEingabe != 'b' && chEingabe != 'B');
return 0;
 }
 
 void DataTransmit () {
 
 int nSocketFromServer = 0;
	int nSocketFromClient = 0;
	socklen_t SizeOfClientSocket = 0;
	char chBuffer[BUF_SIZ];
    int nBytes;
	//char chEingabe;
	//int nZahl = 0;
	
	int nSeriellData = 0;
	int nSensorData = 0;

	struct sockaddr_in AdressFromServer;
	AdressFromServer.sin_addr.s_addr = INADDR_ANY;
	AdressFromServer.sin_port = htons(7000);            
	AdressFromServer.sin_family = AF_INET;

	struct sockaddr_in AdressfromClient;
	SizeOfClientSocket = sizeof(AdressfromClient);
	
	if (wiringPiSetup () == -1) { //wiringPi initalisierung
    cout << "wiringPi konnte nicht initalisiert werden!";
  }

	nSocketFromServer = socket(PF_INET, SOCK_STREAM, 0);
	if (nSocketFromServer == -1) {
		cout << "Socket konnte nicht erstellt werden!" << endl;
	}else{
	cout << "Socket erzeugt." << endl;
}
	if (bind(nSocketFromServer, (struct sockaddr*) &AdressFromServer, sizeof(AdressFromServer)) == -1) {
    cout << "Socket konnte nicht gebunden werden!" << endl;
	}else{
	cout << "Socket gebunden." << endl;
}
	if (listen(nSocketFromServer, 3) == -1) {
    cout << "Keine eingehenden Verbindungen!!" << endl;
	}else{
	cout << "Auf Verbindung Warten..." << endl;
}
	nSocketFromClient = accept(nSocketFromServer, (struct sockaddr*) &AdressfromClient, &SizeOfClientSocket);
	if (nSocketFromClient == -1) {
		cout << "Fehler bei der Verbindung!" << endl;
	}else{
	cout << "Verbindung hergestellt." << endl;
}
	for (;;) {

	if (serialDataAvail (nFd) > 0) {
	nSensorData = serialGetchar (nFd);
	
	
	/*nSensorData = 70 * (nSeriellData - 40) / 210;
	nSensorData -= 80;
	nSensorData *= -1;
	*/
	nSensorData += 1024;
	nSensorData = htons (nSensorData);

	memcpy (&chBuffer, &nSensorData, sizeof(nSensorData));

	nBytes = send(nSocketFromClient, chBuffer, strlen(chBuffer), 0);
		if (nBytes == -1) {
        cout << "Daten konnten nicht gesendet werden!" << endl;
		}
	}
	}
 
 }
 
 void RobotDrive() {

int nI2Ccmps10 = 0;
int nI2CData[2];

nI2Ccmps10 = wiringPiI2CSetup (0x60); //initalisieren des cmps10

serialPutchar (nFd, 255);
serialPutchar (nFd, 255);

for (;;) {
 nI2CData[0] = wiringPiI2CReadReg8 (nI2Ccmps10, 3);
 nI2CData[1] = wiringPiI2CReadReg8 (nI2Ccmps10, 2);
	serialPutchar (nFd, nI2CData[0]);
	serialPutchar (nFd, nI2CData[1]);
	
	delay(500);
 }
 }