#pragma once
#ifdef WIN32
#include "FRCWindowsRobot.h"
#else
#include "WPILib.h"
#endif

class Robot : public frc::SampleRobot 
{
public:
	void RobotInit();
	void Disabled();
	void Autonomous();
	void OperatorControl();
	void Test();
};