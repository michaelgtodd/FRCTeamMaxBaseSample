#include "SampleActions/TimeoutPrintAction.h"
#include "robotlib/RobotDataStream.h"

TimeoutPrintAction::TimeoutPrintAction(std::string printText, uint32_t timeout)
{
	printText_ = printText;
	this->setTimeout(timeout);
}

bool TimeoutPrintAction::isFinished()
{
	return false;
}

void TimeoutPrintAction::update()
{

}

void TimeoutPrintAction::done()
{
	RobotReporter::LogMessage(RobotReporter::Info, printText_);
}

void TimeoutPrintAction::start()
{

}

std::vector<std::string> TimeoutPrintAction::getName()
{
	std::vector<std::string> myName;
	myName.push_back("PrintAction");
	return myName;
}