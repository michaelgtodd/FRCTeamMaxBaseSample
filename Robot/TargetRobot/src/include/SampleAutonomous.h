#pragma once
#include "robotlib/RobotAutonomous.h"

class SampleAutonomous : public AutonomousTask
{
public:
	void Init();
	void ControllerUpdate(RobotControl * controls);
	void Autonomous();
	void End();
	std::string GetName();
private:
	double StartTime = 0;
	double RunTime = 0;
	int LastMessage = 0;
};