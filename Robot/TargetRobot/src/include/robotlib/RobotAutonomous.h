#pragma once
#include <string>
#include "RobotTask.h"
#include <thread>
#include <vector>
#ifndef WIN32
#include <pthread.h>
#endif

class AutonomousTask
{
public:
	void virtual Init() = 0;
	void virtual ControllerUpdate(RobotControl * controls) = 0;
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
	void ControllerUpdate(RobotControl * controls);
	void Autonomous();

	void RegisterAutonomous(AutonomousTask * AutonomousTask);
	void SelectAutonomous(std::string AutonomousName);
	std::vector<std::string> GetAutonomousList();
private:
	void Init();
	void EndAutonomous();
	std::vector<AutonomousTask *> AutoList;
	AutonomousTask * SelectedAutonomous;
	bool AutoLocked = false;
	bool LastStateAutonomous = false;
#ifndef WIN32
	pthread_mutex_t AutoMutex;
#endif
};

extern AutonomousManager AutonomousManagerInstance;