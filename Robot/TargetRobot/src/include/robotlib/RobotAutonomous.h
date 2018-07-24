#pragma once
#include <string>
#include "RobotTask.h"
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

class AutonomousManager : RobotTask
{
public:
	void Run();
	void Always();
	void Disable();
	void Autonomous();

	void RegisterAutonomous(AutonomousTask * AutonomousTask);
	void SelectAutonomous(std::string AutonomousName);
	std::vector<std::string> GetAutonomousList();
private:
	void Init();
	void EndAutonomous();
	void Lock();
	void Unlock();
	std::vector<AutonomousTask *> AutoList;
	AutonomousTask * SelectedAutonomous;
	bool AutoLocked = false;
	bool LastStateAutonomous = false;
#ifdef WIN32
	HANDLE mutex;
#else
	pthread_mutex_t mutex;
#endif
};

extern AutonomousManager AutonomousManagerInstance;