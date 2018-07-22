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
		(*i)->done();
		delete (*i);
		i = ActionList.erase(i);

		if (ActionList.empty())
			return;

		(*i)->start();
	}

	(*i)->update();
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