#ifndef NETWORKPROTOCOL_HPP
#define NETWORKPROTOCOL_HPP

#include "Network.hpp"
#include "KnowledgeBase.hpp"
#include <iostream>
#include <stdint.h>

class CNetworkProtocol
{
public:
	void SendKnowledgeBase ();
	
private:
	uint16_t Check (float fNumber, int nError);
	uint16_t Check (int nNumber, int nError);
};

#endif