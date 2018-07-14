#include "robotlib\RobotAutonomous.h"
#include "robotlib\RobotDataStream.h"
#include "iostream"

MaxAutonomousManager MaxAutonomousManagerInstance;

void MaxAutonomousManager::Run()
{
	EndAutonomous();
}

void MaxAutonomousManager::Always()
{

}

void MaxAutonomousManager::Disable()
{
	EndAutonomous();
}

void MaxAutonomousManager::ControllerUpdate(MaxControl * controls)
{
	SelectedAutonomous->ControllerUpdate(controls);
}

void MaxAutonomousManager::EndAutonomous()
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

void MaxAutonomousManager::Autonomous()
{
#ifndef WIN32
	pthread_mutex_lock(&AutoMutex);
	AutoLocked = true;
	if (!LastStateAutonomous)
	{
		MaxLog::LogInfo("Starting Autonomous: " + SelectedAutonomous->GetName());
		std::cout << "Starting auto..." << std::endl;
		SelectedAutonomous->Init();
	}

	SelectedAutonomous->Autonomous();

	LastStateAutonomous = true;
	pthread_mutex_unlock(&AutoMutex);
#endif
}

void MaxAutonomousManager::RegisterAutonomous(MaxAutonomousTask * AutonomousTask)
{
	AutoList.push_back(AutonomousTask);
	if (AutoList.size() == 1)
		SelectedAutonomous = AutonomousTask;
}

void MaxAutonomousManager::SelectAutonomous(std::string AutonomousName)
{
#ifndef WIN32
	pthread_mutex_lock(&AutoMutex);
	if (!AutoLocked)
	{
		for (std::vector<MaxAutonomousTask *>::iterator i = AutoList.begin();
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

std::vector<std::string> MaxAutonomousManager::GetAutonomousList()
{
	std::vector<std::string> result;
	for (std::vector<MaxAutonomousTask *>::iterator i = AutoList.begin();
		i != AutoList.end();
		i++)
	{
		result.push_back((*i)->GetName());
	}
	return result;
}

void MaxAutonomousManager::Init()
{
#ifndef WIN32
	pthread_mutex_init(&AutoMutex, 0);
#endif
}