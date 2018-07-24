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

void AutonomousManager::Lock()
{
#ifdef WIN32
	WaitForSingleObject(mutex, INFINITE);
#else
	pthread_mutex_lock(&mutex);
#endif
}

void AutonomousManager::Unlock()
{
#ifdef WIN32
	ReleaseMutex(mutex);
#else
	pthread_mutex_unlock(&mutex);
#endif
}

void AutonomousManager::EndAutonomous()
{
	Lock();
	if (LastStateAutonomous)
	{
		SelectedAutonomous->End();
	}
	LastStateAutonomous = false;
	AutoLocked = false;
	Unlock();
}

void AutonomousManager::Autonomous()
{
	Lock();
	AutoLocked = true;
	if (!LastStateAutonomous)
	{
		RobotLog::LogInfo("Starting Autonomous: " + SelectedAutonomous->GetName());
		std::cout << "Starting auto..." << std::endl;
		SelectedAutonomous->Init();
	}

	SelectedAutonomous->Autonomous();

	LastStateAutonomous = true;
	Unlock();
}

void AutonomousManager::RegisterAutonomous(AutonomousTask * AutonomousTask)
{
	Lock();
	AutoList.push_back(AutonomousTask);
	if (AutoList.size() == 1)
		SelectedAutonomous = AutonomousTask;
	Unlock();
}

void AutonomousManager::SelectAutonomous(std::string AutonomousName)
{
	Lock();
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
	Unlock();
}

std::vector<std::string> AutonomousManager::GetAutonomousList()
{
	Lock();
	std::vector<std::string> result;
	for (std::vector<AutonomousTask *>::iterator i = AutoList.begin();
		i != AutoList.end();
		i++)
	{
		result.push_back((*i)->GetName());
	}
	return result;
	Unlock();
}

void AutonomousManager::Init()
{
#ifdef WIN32
	mutex = CreateMutex(NULL, FALSE, NULL);
#else
	mutex = PTHREAD_MUTEX_INITIALIZER;
#endif
}