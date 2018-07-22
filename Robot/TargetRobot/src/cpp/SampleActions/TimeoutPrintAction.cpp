#include "SampleActions/TimeoutPrintAction.h"
#include <iostream>

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
	if (!ranOnce)
	{
		std::cout << printText_ << std::endl;
	}	
	ranOnce = true;
}

void TimeoutPrintAction::done()
{

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