#include "SampleTask.h"
#include <iostream>
#include "robotlib/RobotDataStream.h"
#include "ControlTask.h"

void SampleTask::Run()
{

}

void SampleTask::Disable()
{

}

void SampleTask::Always()
{
	std::cout << "I'm a sample task and I'm running" << std::endl;
}

void SampleTask::Autonomous()
{

}

void SampleTask::ControllerUpdate(RobotControl * controls)
{
	RobotControl * controls_ = (RobotControl *)(controls);
}

void SampleTask::Init()
{

}