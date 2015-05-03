#include "NetworkProtocol.hpp"

void CNetworkProtocol::SendKnowledgeBase () {
	for (int i=0;i<4;i++) {
		g_pNetwork->CreatePackage (*(g_pKnowledgeBase->GetOdometryTicksSinceLastUpdate()+i)); //Odometry Ticks (4 ints)
	}
	for (int i=0;i<100;i++) {
		g_pNetwork->CreatePackage (*(g_pKnowledgeBase->GetScannerData()+i)); //Scanner data Ticks (100 ints)
	}
	for (int i=0;i<4;i++) {
		g_pNetwork->CreatePackage (*(g_pKnowledgeBase->GetCurrentMotorPower()+i)); //Motor Power (4 ints)
	}
	
	g_pNetwork->CreatePackage (static_cast <uint16_t> (g_pKnowledgeBase->GetCalculatedDrivingDirection()*100)); //Calculated direction * 100 (1 int)
	g_pNetwork->CreatePackage (static_cast <uint16_t> (g_pKnowledgeBase->GetTargetDrivingDirection()*100)); //Target direction * 100 (1 int)
	g_pNetwork->CreatePackage (static_cast <uint16_t> ((g_pKnowledgeBase->GetCurrentBatteryVoltage()*100))); //operating voltage * 100 (1 int)
	g_pNetwork->CreatePackage (static_cast <uint16_t> (g_pKnowledgeBase->GetMainLoopTicksPerSecond()/10000)); //loop ticks /10000 (1 int)
	
	g_pNetwork->Send ();
}