#pragma once
#ifdef WIN32
#include "FRCWindowsRobot.h"
#else
#include "WPILib.h"
#endif
#include "SampleTask.h"
#include "ControlTask.h"

class Robot : public frc::SampleRobot 
{
public:
	void RobotInit();
	void Disabled();
	void Autonomous();
	void OperatorControl();
	void Test();
};