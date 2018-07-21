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
	void virtual ControllerUpdate(RobotControl * controls) = 0;
	void virtual Autonomous() = 0;

	std::string GetTaskName();
	uint32_t GetTaskPeriod();
	uint32_t GetAverageTaskPeriod();
	uint32_t GetAverageTaskDuration();

	void ExecInit(std::string taskname, uint32_t task_period);
	void Launch(int priority);
private:
	void virtual Init() = 0;
	void ThreadProcess();
	uint32_t task_period_;
	std::string taskname_;
	std::thread running_thread;
	double last_loop_end = 0;
	double average_task_differential = 0;
	double average_task_period = 0;
	double average_task_duration = 0;
	double max_task_duration = 0;
	double max_task_period = 0;
};

class TaskSchedule
{
public:
	void AddTask(RobotTask* task, std::string taskname, uint32_t period);
	void LaunchTasks();
	void DispatchControl(RobotControl * ControlUpdate);
private:
	std::vector<RobotTask*> TaskList;
};

class TaskStatisticsTask : public RobotTask
{
public:
	TaskStatisticsTask(std::vector<RobotTask*> TaskList);
	void Always();
	void Run();
	void Disable();
	void Autonomous();
	void ControllerUpdate(RobotControl * controls);
private:
	void Init();
	std::vector<RobotTask*> TaskList_;
};