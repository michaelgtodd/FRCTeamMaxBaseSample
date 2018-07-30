#pragma once
#include "robotlib/RobotTask.h"
#include "robotlib/RobotAction.h"

class RobotLoggerTask : public RobotTask
{
public:
	void Always();
	void Run();
	void Disable();
	void Autonomous();
	void Start();
	void Init();
};