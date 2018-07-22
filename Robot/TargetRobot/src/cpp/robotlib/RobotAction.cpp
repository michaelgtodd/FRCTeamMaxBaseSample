#include "robotlib/RobotAction.h"
#include <iostream>

uint32_t RobotAction::getCount()
{
	return 1;
}

void RobotAction::setTimeout(uint32_t milliseconds)
{
	timeoutTime = milliseconds;
}

bool RobotAction::isTimeoutExpired()
{
	bool timedOut = false;
	if (expiredTime != 0)
	{
#ifdef WIN32
		timedOut = expiredTime < timeGetTime();
#else
		timedOut = expiredTime < (uint32_t)(Timer::GetFPGATimeStamp() * 1000.0);
#endif
	}
	if (timedOut)
	{
		std::cout << "Hey I'm a " << this->getName()[0] << " and I timed out after " << RobotAction::timeoutTime << " milliseconds." << std::endl;
	}

	return timedOut;
}

void RobotAction::baseStart()
{
#ifdef WIN32
	expiredTime = timeGetTime() + timeoutTime;
#else
	expiredTime = (Timer::GetFPGATimeStamp() * 1000) + timeoutTime;
#endif
	this->start();	
}

void ParallelAction::AddAction(RobotAction * Action)
{
	ActionList.push_back(Action);
}

void ParallelAction::AddActions(std::vector<RobotAction *> Actions)
{
	ActionList.insert(ActionList.end(), Actions.begin(), Actions.end());
}

uint32_t ParallelAction::getCount()
{
	return ActionList.size();
}

bool ParallelAction::isFinished()
{
	return ActionList.empty();
}

void ParallelAction::update()
{
	if (ActionList.empty())
		return;

	std::vector<RobotAction *>::iterator i = ActionList.begin();
	while (i != ActionList.end())
	{
		(*i)->update();
		if ((*i)->isFinished() || (*i)->isTimeoutExpired())
		{
			(*i)->done();
			delete (*i);
			i = ActionList.erase(i);
		}
		else 
		{
			i++;
		}
	}
}

void ParallelAction::done()
{
	std::vector<RobotAction *>::iterator i = ActionList.begin();
	while (i != ActionList.end())
	{
		(*i)->done();
		delete (*i);
		i = ActionList.erase(i);
	}
}

void ParallelAction::start()
{
	if (ActionList.empty())
		return;

	for (std::vector<RobotAction *>::iterator i = ActionList.begin();
		i != ActionList.end();
		i++)
	{
		(*i)->baseStart();
	}
}

std::vector<std::string> ParallelAction::getName()
{
	std::vector<std::string> namelist;
	namelist.push_back("Parallel");
	for (std::vector<RobotAction *>::iterator i = ActionList.begin();
		i != ActionList.end();
		i++)
	{
		std::vector<std::string> childNames = (*i)->getName();
		namelist.insert(namelist.end(), childNames.begin(), childNames.end());
	}
	return namelist;
}

void SerialAction::AddAction(RobotAction * Action)
{
	ActionList.push_back(Action);
}

void SerialAction::AddActions(std::vector<RobotAction *> Actions)
{
	ActionList.insert(ActionList.end(), Actions.begin(), Actions.end());
}

uint32_t SerialAction::getCount()
{
	return ActionList.size();
}

bool SerialAction::isFinished()
{
	return ActionList.empty() == 0;
}

void SerialAction::update()
{
	if (ActionList.empty())
		return;

	std::vector<RobotAction *>::iterator i = ActionList.begin();
	if ((*i)->isFinished() || (*i)->isTimeoutExpired())
	{
		do 
		{
			(*i)->done();
			delete (*i);
			i = ActionList.erase(i);

			if (ActionList.empty())
				return;

			(*i)->baseStart();

			(*i)->update();
		} while ((*i)->isFinished() || (*i)->isTimeoutExpired());
	}
	else {
		(*i)->update();
	}
}

void SerialAction::done()
{
	std::vector<RobotAction *>::iterator i = ActionList.begin();
	while (i != ActionList.end())
	{
		(*i)->done();
		delete (*i);
		i = ActionList.erase(i);
	}
}

void SerialAction::start()
{
	if (ActionList.empty())
		return;

	std::vector<RobotAction *>::iterator i = ActionList.begin();
	(*i)->baseStart();
}

std::vector<std::string> SerialAction::getName()
{
	std::vector<std::string> namelist;
	namelist.push_back("Serial");
	for (std::vector<RobotAction *>::iterator i = ActionList.begin();
		i != ActionList.end();
		i++)
	{
		std::vector<std::string> childNames = (*i)->getName();
		namelist.insert(namelist.end(), childNames.begin(), childNames.end());
	}
	return namelist;
}

ActionRunner::ActionRunner()
{
#ifdef WIN32
	mutex = CreateMutex(NULL, FALSE, NULL);
#else
	mutex = PTHREAD_MUTEX_INITIALIZER;
#endif
}

void ActionRunner::Lock()
{
#ifdef WIN32
	WaitForSingleObject(mutex, INFINITE);
#else
	pthread_mutex_lock(&mutex);
#endif
}

void ActionRunner::Unlock()
{
#ifdef WIN32
	ReleaseMutex(mutex);
#else
	pthread_mutex_unlock(&mutex);
#endif
}

ActionRunner::~ActionRunner()
{
#ifdef WIN32
	CloseHandle(mutex);
#endif
}

SerialActionRunner::SerialActionRunner(std::string name, uint32_t actionLimit)
{
	ActionRunner::name_ = name;
	ActionRunner::actionLimit_ = actionLimit;
}

SerialActionRunner::~SerialActionRunner()
{
	ActionRunner::Lock();
	baseAction.done();
	ActionRunner::~ActionRunner();
}

void SerialActionRunner::Run()
{
	ActionRunner::Lock();
	baseAction.update();
	ActionRunner::Unlock();
}

void SerialActionRunner::queueAction(RobotAction * Action)
{
	ActionRunner::Lock();
	if (baseAction.getCount() < ActionRunner::actionLimit_)
	{
		if (baseAction.isFinished())
		{
			Action->baseStart();
		}
		baseAction.AddAction(Action);

	}
	else
	{
		std::cout << "Ruhroh - " << ActionRunner::name_  << "'s queue is overflown." << std::endl;
	}
	ActionRunner::Unlock();
}

void SerialActionRunner::queueActions(std::vector<RobotAction *> Actions)
{
	ActionRunner::Lock();
	if (baseAction.getCount() + Actions.size() <= ActionRunner::actionLimit_)
	{
		if (baseAction.isFinished())
		{
			Actions[0]->baseStart();
		}
		baseAction.AddActions(Actions);
	}
	else
	{
		std::cout << "Ruhroh - " << ActionRunner::name_ << "'s queue is overflown." << std::endl;
	}

	ActionRunner::Unlock();
}

void ParallelActionRunner::queueAction(RobotAction * Action)
{
	ActionRunner::Lock();
	if (baseAction.getCount() < ActionRunner::actionLimit_)
	{
		Action->baseStart();
		baseAction.AddAction(Action);
	}
	else
	{
		std::cout << "Ruhroh - " << ActionRunner::name_ << "'s queue is overflown." << std::endl;
	}
	ActionRunner::Unlock();
}

void ParallelActionRunner::queueActions(std::vector<RobotAction *> Actions)
{
	ActionRunner::Lock();
	if (baseAction.getCount() + Actions.size() < ActionRunner::actionLimit_)
	{
		for (std::vector<RobotAction *>::iterator i = Actions.begin();
			i != Actions.end();
			i++)
		{
			(*i)->baseStart();
		}
		baseAction.AddActions(Actions);
	}
	else
	{
		std::cout << "Ruhroh - " << ActionRunner::name_ << "'s queue is overflown." << std::endl;
	}

	ActionRunner::Unlock();
}

void ParallelActionRunner::Run()
{
	ActionRunner::Lock();

	baseAction.update();

	ActionRunner::Unlock();
}

ParallelActionRunner::~ParallelActionRunner()
{
	ActionRunner::Lock();

	baseAction.done();
	ActionRunner::~ActionRunner();
}

