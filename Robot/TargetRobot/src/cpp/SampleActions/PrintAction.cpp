#include "SampleActions/PrintAction.h"
#include <iostream>

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
	std::cout << printText_ << std::endl;
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