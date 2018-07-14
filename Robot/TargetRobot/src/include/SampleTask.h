#pragma once

#include "robotlib/RobotTask.h"
#include "ControlTask.h"

class SampleTask : public MaxTask
{
public:
	void Always();
	void Run();
	void Disable();
	void Autonomous();
	void ControllerUpdate(RobotControl * controls);
private:
	void Init();
};