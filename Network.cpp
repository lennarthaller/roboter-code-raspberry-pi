#include "Network.hpp"

CNetwork::CNetwork () {
	nSocketFromServer = 0;
	nSocketFromClient = 0;
	SizeOfClientSocket = sizeof(AdressfromClient);
	
	AdressFromServer.sin_addr.s_addr = INADDR_ANY;
	AdressFromServer.sin_port = htons(7000);            
	AdressFromServer.sin_family = AF_INET;
}
	
int CNetwork::InitNetwork () {
	Log_File->WriteTopic ("Netzwerk initialisierung", 1);
	nSocketFromServer = socket(PF_INET, SOCK_STREAM, 0);
		if (nSocketFromServer == -1) {
			Log_File->Textout (RED, "Netzwerk Setup Fehlgeschlagen!");
			return -1;
	}
	
	if (bind(nSocketFromServer, (struct sockaddr*) &AdressFromServer, sizeof(AdressFromServer)) == -1) {
		Log_File->Textout (RED, "Serversocket konnte nicht gebunden werden.");
		return -1;
	}
	
	Log_File->Textout (BLACK, "Netzwerkresourcen initialisiert.");
	return 1;
}

int CNetwork::ConnectToClient () {
	if (listen(nSocketFromServer, 3) == -1) {
		Log_File->Textout (RED, "Keine eingehende Verbindung.");
		return -1;
	}
	
	nSocketFromClient = accept(nSocketFromServer, (struct sockaddr*) &AdressfromClient, &SizeOfClientSocket);
	if (nSocketFromClient == -1) {
		Log_File->Textout (RED, "Fehler bei der verbindung mit dem Client!");
		return -1;
	}else{
		Log_File->Textout (BLACK, "Netzwerkverbinung hergestellt.");
		return 1;
	}
}

int CNetwork::Send (int nData) {
	nData += 1024;
	nData = htons (nData);

	memcpy (&chBuffer, &nData, sizeof(nData));

		if (send(nSocketFromClient, chBuffer, strlen(chBuffer), 0) == -1) {
			Log_File->Textout (RED, "Fehler bei dem Senden von Netzwerkdaten!");
			return -1;
		}else{
			return 1;
		}
}

int CNetwork::Receive () {
	return 1;
}