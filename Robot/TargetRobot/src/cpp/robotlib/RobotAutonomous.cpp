#include "robotlib\RobotAutonomous.h"
#include "robotlib\RobotDataStream.h"
#include "iostream"

AutonomousManager AutonomousManagerInstance;

void AutonomousManager::Run()
{
	EndAutonomous();
}

void AutonomousManager::Always()
{

}

void AutonomousManager::Disable()
{
	EndAutonomous();
}

void AutonomousManager::ControllerUpdate(RobotControl * controls)
{
	SelectedAutonomous->ControllerUpdate(controls);
}

void AutonomousManager::EndAutonomous()
{
#ifndef WIN32
	pthread_mutex_lock(&AutoMutex);
	if (LastStateAutonomous)
	{
		SelectedAutonomous->End();
	}
	LastStateAutonomous = false;
	AutoLocked = false;
	pthread_mutex_unlock(&AutoMutex);
#endif
}

void AutonomousManager::Autonomous()
{
#ifndef WIN32
	pthread_mutex_lock(&AutoMutex);
	AutoLocked = true;
	if (!LastStateAutonomous)
	{
		RobotLog::LogInfo("Starting Autonomous: " + SelectedAutonomous->GetName());
		std::cout << "Starting auto..." << std::endl;
		SelectedAutonomous->Init();
	}

	SelectedAutonomous->Autonomous();

	LastStateAutonomous = true;
	pthread_mutex_unlock(&AutoMutex);
#endif
}

void AutonomousManager::RegisterAutonomous(AutonomousTask * AutonomousTask)
{
	AutoList.push_back(AutonomousTask);
	if (AutoList.size() == 1)
		SelectedAutonomous = AutonomousTask;
}

void AutonomousManager::SelectAutonomous(std::string AutonomousName)
{
#ifndef WIN32
	pthread_mutex_lock(&AutoMutex);
	if (!AutoLocked)
	{
		for (std::vector<AutonomousTask *>::iterator i = AutoList.begin();
			i != AutoList.end();
			i++)
		{
			if (AutonomousName == (*i)->GetName())
			{
				SelectedAutonomous = (*i);
			}
		}
	}
	pthread_mutex_unlock(&AutoMutex);
#endif
}

std::vector<std::string> AutonomousManager::GetAutonomousList()
{
	std::vector<std::string> result;
	for (std::vector<AutonomousTask *>::iterator i = AutoList.begin();
		i != AutoList.end();
		i++)
	{
		result.push_back((*i)->GetName());
	}
	return result;
}

void AutonomousManager::Init()
{
#ifndef WIN32
	pthread_mutex_init(&AutoMutex, 0);
#endif
}