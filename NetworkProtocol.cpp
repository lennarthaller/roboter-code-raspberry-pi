#include "NetworkProtocol.hpp"

void CNetworkProtocol::SendKnowledgeBase () {
	for (int i=0;i<4;i++) {
		g_pNetwork->Send (g_pKnowledgeBase->GetOdometryTicksSinceLastUpdate()+i); //Odometry Ticks (4 ints)
	}
	for (int i=0;i<100;i++) {
		g_pNetwork->Send (g_pKnowledgeBase->GetScannerData()+i); //Scanner data Ticks (100 ints)
	}
	for (int i=0;i<4;i++) {
		g_pNetwork->Send (g_pKnowledgeBase->GetCurrentMotorPower()+i); //Motor Power (4 ints)
	}
	g_pNetwork->Send (static_cast <int> (g_pKnowledgeBase->GetCalculatedDrivingDirection()*10)); //Calculated direction * 10 (1 int)
	g_pNetwork->Send (static_cast <int> (g_pKnowledgeBase->GetTargetDrivingDirection()*10)); //Target direction * 10 (1 int)
	g_pNetwork->Send (static_cast <int> (g_pKnowledgeBase->GetCurrentBatteryVoltage()*10)); //operating voltage * 10 (1 int)
	g_pNetwork->Send (m_nMainLoopTicksPerSecond); //Target direction * 10 (1 int)
}