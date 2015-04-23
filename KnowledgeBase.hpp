#ifndef KNOWLEDGEBASE_HPP
#define KNOWLEDGEBASE_HPP

#include "WiringPi.hpp"

#define g_pKnowledgeBase CKnowledgeBase::Get()

class CKnowledgeBase : public TSingleton<CKnowledgeBase>
{
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
	std::auto_ptr<Position> GetOdometryPosition () {return m_pOdometriePositionPtr;}
	void 	SetOdometryTicks (int nOdometryTicks[]);
	unsigned long* 	GetOdometryTicks () {return m_nOdometryTicks;}
	void 	SetCurrentBatteryVoltage (float fCurrentBattteryVoltage) {m_fCurrentBattteryVoltage = fCurrentBattteryVoltage;}
	float 	GetCurrentBatteryVoltage () {return m_fCurrentBatteryVoltage;}
	
	private:
	struct Position {
		float fX;
		float fY;
		float fTheta; //in radian! (counterclockwise from x-axis)
	}
	Position OdometryPosition;
	
	std::auto_ptr<Position> m_pOdometriePositionPtr;
	unsigned long m_nOdometryTicks[4];
	int 	m_nCurrentMotorPower[4]; //0 = Motor 1..
	int 	m_nScannerData[100];
	float 	m_fCalculatedDrivingDirection;
	float 	m_fTargetDrivingAngle;
	float 	m_fCurrentBattteryVoltage;
};

#endif