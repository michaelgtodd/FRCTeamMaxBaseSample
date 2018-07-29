#pragma once

#include "robotlib/RobotTask.h"
#include "robotlib/RobotAction.h"

class TaskMetricsTask : public RobotTask
{
public:
	void Always();
	void Run();
	void Disable();
	void Autonomous();
	void Start();
	void Init();
private:
	std::vector<DataItem *> TaskCounters;
	uint32_t LastReport;
}; 
