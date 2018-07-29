#pragma once
#pragma once

#include "robotlib/RobotTask.h"
#include "robotlib/RobotAction.h"

class ActionMetricsTask : public RobotTask
{
public:
	void Always();
	void Run();
	void Disable();
	void Autonomous();
	void Start();
	void Init();
private:
	std::vector<DataItem *> ActionMetrics;
	uint32_t LastReport;
};
