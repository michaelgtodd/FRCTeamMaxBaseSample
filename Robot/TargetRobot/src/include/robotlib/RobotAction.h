#pragma once
#include <vector>
#ifndef WIN32
#include "pthread.h"
#else
#include <Windows.h>
#endif

class RobotAction
{
public:
	virtual ~RobotAction() = default;

	bool virtual isFinished() = 0;
	void virtual update() = 0;
	void virtual done() = 0;
	void virtual start() = 0;

	std::string getName();

	void setTimeout(uint32_t milliseconds);

private:
	bool isTimeoutExpired();

	uint32_t expired_time;
};

class ParallelAction : public RobotAction
{
public:
	void AddAction(RobotAction * Action);
	void AddActions(std::vector<RobotAction *> Actions);

	bool isFinished();
	void update();
	void done();
	void start();

private:
	std::vector<RobotAction *> ActionList;
};

class SerialAction : public RobotAction
{
public:
	void AddAction(RobotAction * Action);
	void AddActions(std::vector<RobotAction *> Actions);

	bool isFinished();
	void update();
	void done();
	void start();
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
	void queueAction(RobotAction * Action);
	void queueActions(std::vector<RobotAction *> Actions);
	void Run();
	~SerialActionRunner();
private:
	SerialAction baseAction;
};

class ParallelActionRunner : ActionRunner
{
public:
	void queueAction(RobotAction * Action);
	void queueActions(std::vector<RobotAction *> Actions);
	void Run();
	~ParallelActionRunner();
private:
	ParallelAction baseAction;
};