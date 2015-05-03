#include "Network.hpp"

CNetwork::CNetwork () {
	m_nSocketFromServer = 0;
	m_nSocketFromClient = 0;
	m_nBytes = 0;
	SizeOfClientSocket = sizeof(AdressfromClient);
	
	AdressFromServer.sin_addr.s_addr = INADDR_ANY;
	AdressFromServer.sin_port = htons(7000);            
	AdressFromServer.sin_family = AF_INET;
}
	
int CNetwork::InitNetwork () {
	Log_File->WriteTopic ("Netzwerk initialisierung", 1);
	m_nSocketFromServer = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
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
		std::cout << "Verbindung hergestellt." << std::endl; /////DEBUG
		return 1;
	}
}

int CNetwork::Send (void) {
		if (send(m_nSocketFromClient, m_chBuffer, m_nBytes, 0) == -1) {
			Log_File->Textout (RED, "Fehler bei dem Senden von Netzwerkdaten!");
			return -1;
		}else{
			for (int i=0; i<m_nBytes; i++) {
				m_chBuffer[i] = 0;
			}
			m_nBytes = 0;
			return 1;
		}
}

void CNetwork::CreatePackage (uint16_t nData) {
	m_chBuffer[m_nBytes] = nData;
	m_nBytes ++;
	m_chBuffer[m_nBytes] = (nData >> 8);
	m_nBytes ++;
}
int CNetwork::Receive () {
	return 1;
}