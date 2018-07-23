#pragma once

#include "robotlib/RobotTask.h"
#include "robotlib/RobotAction.h"

class SampleTask : public RobotTask
{
public:
	void Always();
	void Run();
	void Disable();
	void Autonomous();
	void ControllerUpdate(RobotControl * controls);
private:
	void Init();
	SerialActionRunner ActionRunner;
public:
	SampleTask() : ActionRunner("Sample Runner", 15) {}
};