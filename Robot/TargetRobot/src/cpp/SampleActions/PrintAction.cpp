#include "SampleActions/PrintAction.h"
#include "robotlib/RobotDataStream.h"

PrintAction::PrintAction(std::string printText)
{
	printText_ = printText;
}

bool PrintAction::isFinished()
{
	return ranOnce;
}

void PrintAction::update()
{
	RobotReporter::LogMessage(RobotReporter::Info, printText_);
	ranOnce = true;
}

void PrintAction::done()
{

}

void PrintAction::start()
{

}

std::vector<std::string> PrintAction::getName()
{
	std::vector<std::string> myName;
	myName.push_back("PrintAction");
	return myName;	
}