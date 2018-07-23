#pragma once
#ifdef WIN32
#include "FRCWindowsRobot.h"
#else
#include "WPILib.h"
#endif
#include "SampleTask.h"

#define CONSOLE_LOG_INFO

class Robot : public frc::SampleRobot 
{
public:
	void RobotInit();
	void Disabled();
	void Autonomous();
	void OperatorControl();
	void Test();
};