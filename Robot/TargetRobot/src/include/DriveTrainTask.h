#pragma once
#include "robotlib/RobotTask.h"

class DriveTrainTask : public RobotTask
{
public:
	void Always();
	void Run();
	void Disable();
	void Autonomous();
	void Start();
	void Init();
};