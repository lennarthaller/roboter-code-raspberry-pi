#ifndef NETWORK_HPP
#define NETWORK_HPP

#include <iostream>
#include <fcntl.h>
#include "Singleton.hpp"
#include "Logfile.hpp"

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

#define g_pNetwork CNetwork::Get()
#define BUF_SIZE 4096

class CNetwork : public TSingleton<CNetwork>
{
  public:
	CNetwork (void);
	int InitNetwork (void);
	int ConnectToClient (void);
	int Send (int nData);
	int Receive (void);
  private:
	int m_nSocketFromServer;
	int m_nSocketFromClient;
	socklen_t SizeOfClientSocket;
	char m_chBuffer[BUF_SIZE];
	
	struct sockaddr_in AdressFromServer;
	struct sockaddr_in AdressfromClient;
};

#endif
