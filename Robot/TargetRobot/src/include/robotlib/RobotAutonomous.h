#pragma once
#include <string>
#include "RobotTask.h"
#include "RobotAction.h"
#include <thread>
#include <vector>
#ifndef WIN32
#include "pthread.h"
#else
#include <Windows.h>
#endif

class AutonomousTask
{
public:
	void virtual Init() = 0;
	void virtual Autonomous() = 0;
	void virtual End() = 0;
	std::string virtual GetName() = 0;
};

class RegisterAutonomousAction : public RobotAction
{
public:
	RegisterAutonomousAction(AutonomousTask * AutonomousTask);

	bool isFinished();
	void update();
	void done();
	void start();

	std::vector<std::string> getName();
private:
	RegisterAutonomousAction() = default;
	AutonomousTask * AutonomousTask_;
	bool ranOnce = false;
};

class SelectAutonomousAction : public RobotAction
{
public:
	SelectAutonomousAction(std::string AutonomousName);

	bool isFinished();
	void update();
	void done();
	void start();

	std::vector<std::string> getName();
private:
	SelectAutonomousAction() = default;
	std::string AutonomousName_;
	bool ranOnce = false;
};

class AutonomousManager : RobotTask
{
	friend class RegisterAutonomousAction;
	friend class SelectAutonomousAction;

public:
	void Run();
	void Always();
	void Disable();
	void Autonomous();

	void RegisterAutonomous(AutonomousTask * AutonomousTask);
	void SelectAutonomous(std::string AutonomousName);
	std::vector<std::string> GetAutonomousList();
	std::string GetSelectedAuto();
private:
	void ProcessRegisterAutonomous(AutonomousTask * AutonomousTask);
	void ProcessSelectAutonomous(std::string AutonomousName);
	void Lock();
	void Unlock();
	void Init();
	void EndAutonomous();
	std::vector<AutonomousTask *> AutoList;
	std::vector<std::string> AutoNameList;
	AutonomousTask * SelectedAutonomous;
	bool AutoRunning = false;
	bool LastStateAutonomous = false;
	SerialActionRunner ActionRunner;
#ifdef WIN32
	HANDLE mutex;
#else
	pthread_mutex_t mutex;
#endif
public:
	AutonomousManager() : ActionRunner("AutoRunner", 30) {}
};

extern AutonomousManager AutonomousManagerInstance;