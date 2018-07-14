#pragma once
#include "WPILib.h"
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