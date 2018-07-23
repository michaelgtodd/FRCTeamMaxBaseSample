#include "SampleActions/CounterAction.h"
#include <iostream>

CounterAction::CounterAction(int counterMax)
{
	_counter = 0;
	_counterMax = counterMax;
}

bool CounterAction::isFinished()
{
	return hitMax;
}

void CounterAction::update()
{
	_counter++;
	if (_counter >= _counterMax)
		hitMax = true;
}

void CounterAction::done()
{

}

void CounterAction::start()
{

}

std::vector<std::string> CounterAction::getName()
{
	std::vector<std::string> myName;
	myName.push_back("CounterAction");
	return myName;
}

int CounterAction::getCounter()
{
	return _counter;
}
