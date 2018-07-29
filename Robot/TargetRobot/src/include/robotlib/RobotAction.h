#pragma once
#include <vector>
#include <string>
#include "DataStore.h"
#include "RobotLibConfig.h"
#ifndef WIN32
#include "pthread.h"
#else
#include <Windows.h>
#endif

class ActionRunnerDataItem : public DataItem
{
public:
	void SetRunnerName(std::string name);
	std::string GetRunnerName();
	void SetRunningActions(std::vector<std::string> actions);
	std::vector<std::string> GetRunningActions();
private:
	std::vector<std::string> RunningActions;
	std::string RunnerName;
};

class RobotAction
{
public:
	virtual ~RobotAction() = default;

	uint32_t virtual getCount();
	bool virtual isFinished() = 0;
	void virtual update() = 0;
	void virtual done() = 0;
	void virtual start() = 0;
	void baseStart();

	std::vector<std::string> virtual getName() = 0;

	void setTimeout(uint32_t milliseconds);
	bool isTimeoutExpired();

private:
	uint32_t timeoutTime = 0;
	uint32_t expiredTime = 0;
};

class ParallelAction : public RobotAction
{
public:
	ParallelAction() = default;
	ParallelAction(std::vector<RobotAction *> Actions);
	void AddAction(RobotAction * Action);
	void AddActions(std::vector<RobotAction *> Actions);

	uint32_t getCount();
	bool isFinished();
	void update();
	void done();
	void start();

	std::vector<std::string> getName();
	
private:
	std::vector<RobotAction *> ActionList;
};

class SerialAction : public RobotAction
{
public:
	SerialAction() = default;
	SerialAction(std::vector<RobotAction *> Actions);
	void AddAction(RobotAction * Action);
	void AddActions(std::vector<RobotAction *> Actions);

	uint32_t getCount();
	bool isFinished();
	void update();
	void done();
	void start();

	std::vector<std::string> getName();
	
private:
	std::vector<RobotAction *> ActionList;
};

class ActionRunner
{
public:
	ActionRunner();
	virtual ~ActionRunner();
	void virtual Run() = 0;
	void virtual queueAction(RobotAction * Action) = 0;
	void virtual queueActions(std::vector<RobotAction *> Actions) = 0;
protected:
	void Lock();
	void Unlock();
	uint32_t actionLimit_ = 0;
	std::string name_ = "NoName";
private:
#ifdef WIN32
	HANDLE mutex;
#else
	pthread_mutex_t mutex;
#endif
};

class SerialActionRunner : public ActionRunner
{
public:
	SerialActionRunner(std::string name, uint32_t actionLimit);
	void queueAction(RobotAction * Action);
	void queueActions(std::vector<RobotAction *> Actions);
	void Run();
	~SerialActionRunner();
private:
	SerialActionRunner();
	SerialAction baseAction;
#ifdef ACTION_METRICS
	ActionRunnerDataItem * MetricsData;
#endif
};

class ParallelActionRunner : public ActionRunner
{
public:
	ParallelActionRunner(std::string name, uint32_t actionLimit);
	void queueAction(RobotAction * Action);
	void queueActions(std::vector<RobotAction *> Actions);
	void Run();
	~ParallelActionRunner();
private:
	ParallelActionRunner();
	ParallelAction baseAction;
#ifdef ACTION_METRICS
	ActionRunnerDataItem * MetricsData;
#endif
};