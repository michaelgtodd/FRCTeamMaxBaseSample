#pragma once
#include "robotlib/RobotAction.h"
#include <string>

class PrintAction : public RobotAction
{
public:
	PrintAction(std::string printText);
	bool isFinished();
	void update();
	void done();
	void start();
	std::vector<std::string> getName();
private:
	std::string printText_;
	PrintAction();
	bool ranOnce = false;
};