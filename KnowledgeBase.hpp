#ifndef KNOWLEDGEBASE_HPP
#define KNOWLEDGEBASE_HPP

#include <iostream>
#include "Singleton.hpp"
#include "Logfile.hpp"
#include <stdint.h>

#define g_pKnowledgeBase CKnowledgeBase::Get()

class CKnowledgeBase : public TSingleton<CKnowledgeBase>
{
	private:
	typedef struct {
		int nX;
		int nY;
		float fTheta; //in rad! (clockwise from y-axis)
	} Position;
	
	Position OdometryPositionData;
	Position LidarPositionData;
	unsigned long m_nOdometryTicks[4];
	int		m_nOdometryTicksSinceLastupdate[4];
	int 	m_nScannerData[100];
	float 	m_fCalculatedDrivingDirection;
	float 	m_fTargetDrivingAngle;
	int 	m_nMainLoopTicksPerSecond;
	bool 	m_bIsConnected;
	int 	m_nCurrentMotorPower[4]; //0 = Motor 1..
	float 	m_fCurrentBattteryVoltage;
	
	public:
	CKnowledgeBase ();
	
	void 	SetScannerData (int nSensorData[]);
	int* 	GetScannerData () {return m_nScannerData;}
	void 	SetCurrentMotorPower (int nCurrentMotorPower, int nMotorNumber);
	int* 	GetCurrentMotorPower () {return m_nCurrentMotorPower;}
	void 	SetCalculatedDrivingDirection (float fDirection) {m_fCalculatedDrivingDirection = fDirection;}
	float 	GetCalculatedDrivingDirection () {return m_fCalculatedDrivingDirection;}
	void 	SetTargetDrivingDirection (float fDirection) {m_fTargetDrivingAngle = fDirection;}
	float 	GetTargetDrivingDirection () {return m_fTargetDrivingAngle;}
	Position* OdometryPosition () {return &OdometryPositionData;}
	Position* LidarPosition () {return &LidarPositionData;}
	void 	SetOdometryTicks (int nOdometryTicks[]);
	unsigned long* 	GetOdometryTicks () {return m_nOdometryTicks;}
	void 	SetOdometryTicksSinceLastUpdate (int nOdometryTicks[]);
	int*	GetOdometryTicksSinceLastUpdate () {return m_nOdometryTicksSinceLastupdate;}
	void 	SetMainLoopTicksPerSecond (int nTicksPerSecond) {m_nMainLoopTicksPerSecond = nTicksPerSecond;}
	int 	GetMainLoopTicksPerSecond () {return m_nMainLoopTicksPerSecond;}
	void 	SetCurrentBatteryVoltage (float fCurrentBattteryVoltage) {m_fCurrentBattteryVoltage = fCurrentBattteryVoltage;}
	float 	GetCurrentBatteryVoltage () {return m_fCurrentBattteryVoltage;}
	bool 	GetIsConnected() {return m_bIsConnected;}
	void 	SetIsConnected (bool bNetworkStatus) {m_bIsConnected = bNetworkStatus;}
};

#endif