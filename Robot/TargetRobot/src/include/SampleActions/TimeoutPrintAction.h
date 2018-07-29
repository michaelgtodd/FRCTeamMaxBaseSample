#pragma once
#include "robotlib/RobotAction.h"
#include <string>

class TimeoutPrintAction : public RobotAction
{
public:
	TimeoutPrintAction(std::string printText, uint32_t timeout);
	bool isFinished();
	void update();
	void done();
	void start();
	std::vector<std::string> getName();
private:
	std::string printText_;
	TimeoutPrintAction();
};