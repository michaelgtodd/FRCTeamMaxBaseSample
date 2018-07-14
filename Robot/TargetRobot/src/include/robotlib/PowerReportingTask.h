#pragma once
#include "robotlib/RobotTask.h"
#ifndef WIN32
#include "ctre/Phoenix.h"
#include "WPILib.h"
#endif

class PowerReportingTask : public MaxTask
{
public:
	void Always();
	void Run();
	void Disable();
	void Autonomous();
	void ControllerUpdate(MaxControl * controls);
private:
	void Init();
#ifndef WIN32
	frc::PowerDistributionPanel * PDP;
#endif
};