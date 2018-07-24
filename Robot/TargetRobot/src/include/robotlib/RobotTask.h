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
	void virtual Init() = 0;

private:
	uint32_t getTimeMS();
	void ThreadProcess();
	uint32_t task_period_;
	std::string taskname_;
	std::thread running_thread;
	double lastLoopEndMS = 0;
};

class TaskSchedule
{
public:
	static void AddTask(RobotTask* task, std::string taskname, uint32_t period);
	static void LaunchTasks();
	static void SetTaskPriorty(int priority, std::string taskname);
private:
	static std::vector<RobotTask*> TaskList;
	TaskSchedule() = default;
};

class TaskContainer : public RobotTask
{
public:
	void AddTask(RobotTask * Task, std::string taskname);

	void Run();
	void Disable();
	void Always();
	void Autonomous();
	void Init();

private:
	std::vector<RobotTask*> TaskList;
};