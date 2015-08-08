#ifndef MOTORCONTROLLER_HPP
#define MOTORCONTROLLER_HPP

#include "PID.hpp"
#include "KnowledgeBase.hpp"
#include "Seriell.hpp"

#include <iostream>

#define g_pMotorController CMotorController::Get()

class CMotorController : public TSingleton<CMotorController>
{
	public:
		CMotorController();
		void UpdateMotors ();

	private:
		CPidController *PidMotor[4];
		int m_nControlValue[4];
};

#endif
