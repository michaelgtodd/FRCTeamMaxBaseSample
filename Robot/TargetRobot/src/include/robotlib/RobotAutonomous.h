#pragma once
#include <string>
#include "RobotTask.h"
#include "RobotControls.h"
#include <thread>
#include <vector>
#include "robotlib/RobotControls.h"
#ifndef WIN32
#include <pthread.h>
#endif

class MaxAutonomousTask
{
public:
	void virtual Init() = 0;
	void virtual ControllerUpdate(MaxControl * controls) = 0;
	void virtual Autonomous() = 0;
	void virtual End() = 0;
	std::string virtual GetName() = 0;
};

class MaxAutonomousManager : MaxTask
{
public:
	void Run();
	void Always();
	void Disable();
	void ControllerUpdate(MaxControl * controls);
	void Autonomous();

	void RegisterAutonomous(MaxAutonomousTask * AutonomousTask);
	void SelectAutonomous(std::string AutonomousName);
	std::vector<std::string> GetAutonomousList();
private:
	void Init();
	void EndAutonomous();
	std::vector<MaxAutonomousTask *> AutoList;
	MaxAutonomousTask * SelectedAutonomous;
	bool AutoLocked = false;
	bool LastStateAutonomous = false;
#ifndef WIN32
	pthread_mutex_t AutoMutex;
#endif
};

extern MaxAutonomousManager MaxAutonomousManagerInstance;