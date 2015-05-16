#ifndef KNOWLEDGEBASE_HPP
#define KNOWLEDGEBASE_HPP

#include "WiringPi.hpp"

#define g_pKnowledgeBase CKnowledgeBase::Get()

class CKnowledgeBase : public TSingleton<CKnowledgeBase>
{
	private:
	typedef struct {
		float fX;
		float fY;
		float fTheta; //in radian! (counterclockwise from x-axis)
	} Position;
	
	Position OdometryPosition;
	unsigned long m_nOdometryTicks[4];
	int		m_nOdometryTicksSinceLastupdate[4];
	int 	m_nScannerData[100];
	float 	m_fCalculatedDrivingDirection;
	float 	m_fTargetDrivingAngle;
	int 	m_nMainLoopTicksPerSecond;
	int 	m_nNetworkStatus;
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
	Position* OdometryPosition () {return &OdometryPosition;}
	void 	SetOdometryTicks (int nOdometryTicks[]);
	unsigned long* 	GetOdometryTicks () {return m_nOdometryTicks;}
	void 	SetOdometryTicksSinceLastUpdate (int nOdometryTicks[]);
	int*	GetOdometryTicksSinceLastUpdate () {return m_nOdometryTicksSinceLastupdate;}
	void 	SetMainLoopTicksPerSecond (int nTicksPerSecond) {m_nMainLoopTicksPerSecond = nTicksPerSecond;}
	int 	GetMainLoopTicksPerSecond () {return m_nMainLoopTicksPerSecond;}
	void 	SetCurrentBatteryVoltage (float fCurrentBattteryVoltage) {m_fCurrentBattteryVoltage = fCurrentBattteryVoltage;}
	float 	GetCurrentBatteryVoltage () {return m_fCurrentBattteryVoltage;}
	int 	GetNetworkStatus () {return m_nNetworkStatus;}
	void 	SetNetworkStatus (int nNetworkStatus) {m_nNetworkStatus = nNetworkStatus;}
};

#endif