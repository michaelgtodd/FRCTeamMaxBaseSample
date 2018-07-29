#pragma once
#include <string>
#include <thread>
#include <vector>
#include "RobotControl.h"
#include "DataStore.h"
#include "BaseDataStoreTypes.h"
#include "RobotLibConfig.h"

class TaskMetricsData : public DataItem
{
public:
	void ResetRuns();
	uint32_t GetRuns();
	void IncrementRuns();
	void SetPeriod(uint32_t period);
	uint32_t GetPeriod();
private:
	uint32_t runCounter;
	uint32_t targetPeriod;
	std::string name;
};

class RobotTask 
{
public:
	void virtual Run() = 0;
	void virtual Disable() = 0;
	void virtual Always() = 0;
	void virtual Autonomous() = 0;
	void virtual Start() = 0;

	std::string GetTaskName();
	uint32_t GetTaskPeriod();

	void ExecInit(std::string taskname, uint32_t task_period);
	void Launch(int priority);
	void virtual Init() = 0;

protected:
	uint32_t getTimeMS();

private:
	void ThreadProcess();
	uint32_t task_period_;
	std::string taskname_;
	std::thread running_thread;
	uint32_t lastLoopEndTargetMS = 0;
#ifdef TASK_METRICS
	TaskMetricsData * taskMetricsData;
#endif
};

class TaskSchedule
{
public:
	static void AddTask(RobotTask* task, std::string taskname, uint32_t period);
	static void LaunchTasks();
	static void SetTaskPriorty(int priority, std::string taskname);
	static void SetTaskPriorty(int priority, std::string taskname, std::thread * thread);
private:
	static void AddLibraryTasks();
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