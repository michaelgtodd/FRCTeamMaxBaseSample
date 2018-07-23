#pragma once
#include <string>
#include <thread>
#include <vector>
#include "RobotControl.h"

class RobotTask 
{
public:
	void virtual Run() = 0;
	void virtual Disable() = 0;
	void virtual Always() = 0;
	void virtual Autonomous() = 0;

	std::string GetTaskName();
	uint32_t GetTaskPeriod();

	void ExecInit(std::string taskname, uint32_t task_period);
	void Launch(int priority);
private:
	void virtual Init() = 0;
	void ThreadProcess();
	uint32_t task_period_;
	std::string taskname_;
	std::thread running_thread;
	double last_loop_end = 0;
};

class TaskSchedule
{
public:
	void AddTask(RobotTask* task, std::string taskname, uint32_t period);
	void LaunchTasks();
private:
	std::vector<RobotTask*> TaskList;
};

extern TaskSchedule taskschedule;
