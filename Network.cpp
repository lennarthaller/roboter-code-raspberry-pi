#include "Network.hpp"

CNetwork::CNetwork () {
	m_nSocketFromServer = 0;
	m_nSocketFromClient = 0;
	SizeOfClientSocket = sizeof(AdressfromClient);
	
	AdressFromServer.sin_addr.s_addr = INADDR_ANY;
	AdressFromServer.sin_port = htons(7000);            
	AdressFromServer.sin_family = AF_INET;
}
	
int CNetwork::InitNetwork () {
	Log_File->WriteTopic ("Netzwerk initialisierung", 1);
	m_nSocketFromServer = socket(PF_INET, SOCK_STREAM, 0);
	fcntl(m_nSocketFromServer, F_SETFL, O_NONBLOCK);
		if (m_nSocketFromServer == -1) {
			Log_File->Textout (RED, "Netzwerk Setup Fehlgeschlagen!");
			return -1;
	}
	
	if (bind(m_nSocketFromServer, (struct sockaddr*) &AdressFromServer, sizeof(AdressFromServer)) == -1) {
		Log_File->Textout (RED, "Serversocket konnte nicht gebunden werden.");
		return -1;
	}
	
	Log_File->Textout (BLACK, "Netzwerkresourcen initialisiert.");
	return 1;
}

int CNetwork::ConnectToClient () {
	if (listen(m_nSocketFromServer, 3) != 0) {
		Log_File->Textout (RED, "Keine eingehende Verbindung!");
		return -1;
	}
	
	m_nSocketFromClient = accept(m_nSocketFromServer, (struct sockaddr*) &AdressfromClient, &SizeOfClientSocket);
	if (m_nSocketFromClient == -1) {
		return -1;
	}else{
		Log_File->Textout (BLACK, "Netzwerkverbinung hergestellt.");
		return 1;
	}
}

int CNetwork::Send (int nData) {
	nData += 1024;
	nData = htons (nData);

	memcpy (&m_chBuffer, &nData, sizeof(nData));

		if (send(m_nSocketFromClient, m_chBuffer, strlen(m_chBuffer), 0) == -1) {
			Log_File->Textout (RED, "Fehler bei dem Senden von Netzwerkdaten!");
			return -1;
		}else{
			return 1;
		}
}

int CNetwork::Receive () {
	return 1;
}