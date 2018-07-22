#include "robotlib/RobotAction.h"

void ParallelAction::AddAction(RobotAction * Action)
{
	ActionList.push_back(Action);
}

void ParallelAction::AddActions(std::vector<RobotAction *> Actions)
{
	ActionList.insert(ActionList.end(), Actions.begin(), Actions.end());
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
		if ((*i)->isFinished())
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
		(*i)->start();
	}
}

void SerialAction::AddAction(RobotAction * Action)
{
	ActionList.push_back(Action);
}

void SerialAction::AddActions(std::vector<RobotAction *> Actions)
{
	ActionList.insert(ActionList.end(), Actions.begin(), Actions.end());
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
	if ((*i)->isFinished())
	{
		do 
		{
			(*i)->done();
			delete (*i);
			i = ActionList.erase(i);

			if (ActionList.empty())
				return;

			(*i)->start();

			(*i)->update();
		} while ((*i)->isFinished());
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
	(*i)->start();
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
	if (baseAction.isFinished())
	{
		Action->start();
	}
	baseAction.AddAction(Action);
	ActionRunner::Unlock();
}

void SerialActionRunner::queueActions(std::vector<RobotAction *> Actions)
{
	ActionRunner::Lock();
	
	if (baseAction.isFinished())
	{
		Actions[0]->start();
	}
	baseAction.AddActions(Actions);

	ActionRunner::Unlock();
}

void ParallelActionRunner::queueAction(RobotAction * Action)
{
	ActionRunner::Lock();

	Action->start();
	baseAction.AddAction(Action);

	ActionRunner::Unlock();
}

void ParallelActionRunner::queueActions(std::vector<RobotAction *> Actions)
{
	ActionRunner::Lock();

	for (std::vector<RobotAction *>::iterator i = Actions.begin();
		i != Actions.end();
		i++)
	{
		(*i)->start();
	}
	baseAction.AddActions(Actions);

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

