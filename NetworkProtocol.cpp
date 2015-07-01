#include "NetworkProtocol.hpp"

void CNetworkProtocol::SendKnowledgeBase () {
	for (int i=0;i<4;i++) {
		g_pNetwork->CreatePackage (Check (*(g_pKnowledgeBase->GetOdometryTicksSinceLastUpdate()+i), 1)); //Odometry Ticks (4 ints)
	}
	for (int i=0;i<100;i++) {
		g_pNetwork->CreatePackage (Check (*(g_pKnowledgeBase->GetScannerData()+i), 2)); //Scanner data (100 ints)
	}
	for (int i=0;i<4;i++) {
		g_pNetwork->CreatePackage (Check (*(g_pKnowledgeBase->GetCurrentMotorPower()+i), 3)); //Motor Power (4 ints)
	}
	
	g_pNetwork->CreatePackage (Check ((g_pKnowledgeBase->GetCalculatedDrivingDirection()+90)*100, 4)); //Calculated direction * 100 (1 int)
	g_pNetwork->CreatePackage (Check ((g_pKnowledgeBase->GetTargetDrivingDirection()+90)*100, 5)); //Target direction * 100 (1 int)
	g_pNetwork->CreatePackage (Check ((g_pKnowledgeBase->GetCurrentBatteryVoltage()*100), 6)); //operating voltage * 100 (1 int)
	g_pNetwork->CreatePackage (Check (g_pKnowledgeBase->GetMainLoopTicksPerSecond()/10000, 7)); //loop ticks /10000 (1 int)
	g_pNetwork->CreatePackage (Check (g_pKnowledgeBase->LidarPosition()->nX+15000, 8)); //X + 15000 Pos (1 int)
	g_pNetwork->CreatePackage (Check (g_pKnowledgeBase->LidarPosition()->nY+15000, 9)); //Y + 15000 Pos (1 int)
	g_pNetwork->CreatePackage (Check ((g_pKnowledgeBase->LidarPosition()->fTheta+10)*1000, 10)); //(Theta +10) * 1000 (1 int)
	
	g_pNetwork->Send ();
}

uint16_t CNetworkProtocol::Check (float fNumber, int nError) {
	if ((fNumber < 0)||(fNumber > 65536)) {
		std::cout << "Network parameter error! " << nError << std::endl;
		return 0;
	}else{
		return static_cast <uint16_t> (fNumber);
	}
}

uint16_t CNetworkProtocol::Check (int nNumber, int nError) {
	if ((nNumber < 0)||(nNumber > 65536)) {
		std::cout << "Network parameter error! " << nError << std::endl;
		return 0;
	}else{
		return static_cast <uint16_t> (nNumber);
	}
}