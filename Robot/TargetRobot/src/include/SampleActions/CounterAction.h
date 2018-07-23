#pragma once
#include "robotlib/RobotAction.h"
#include <string>

class CounterAction : public RobotAction
{
public:
	CounterAction(int counterMax);
	bool isFinished();
	void update();
	void done();
	void start();
	std::vector<std::string> getName();
	int getCounter();
private:
	int _counter;
	int _counterMax;
	CounterAction();
	bool hitMax = false;
};
