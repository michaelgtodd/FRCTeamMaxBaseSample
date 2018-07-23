#pragma once

#include "robotlib/RobotTask.h"
#include "ControlTask.h"
#include "robotlib/RobotAction.h"

class ParallelCounterSampleTask : public RobotTask
{
public:
	void Always();
	void Run();
	void Disable();
	void Autonomous();
	void ControllerUpdate(RobotControl * controls);
private:
	void Init();
	ParallelActionRunner ActionRunner;
public:
	ParallelCounterSampleTask() : ActionRunner("Tom's Sample Runner", 15) {}
};