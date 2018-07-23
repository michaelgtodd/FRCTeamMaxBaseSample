#include "SampleTask.h"
#include <iostream>
#include "robotlib/RobotDataStream.h"
#include "SampleActions/PrintAction.h"
#include "SampleActions/TimeoutPrintAction.h"

void SampleTask::Run()
{

}

void SampleTask::Disable()
{

}

void SampleTask::Always()
{
	ActionRunner.Run();
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
	ActionRunner.queueAction(new PrintAction("I'm getting started"));
	ActionRunner.queueAction(new PrintAction("I'm going to run a few tests."));
	ActionRunner.queueAction(new TimeoutPrintAction("First I'm going to time out for 5 seconds, then print some numbers, then wait another five seconds, then print out done", 5000));
	std::vector<RobotAction *> phaseOneActions;
	phaseOneActions.push_back(new TimeoutPrintAction("one", 2500));
	phaseOneActions.push_back(new TimeoutPrintAction("two", 4000));
	phaseOneActions.push_back(new TimeoutPrintAction("three", 5000));
	ActionRunner.queueAction(new ParallelAction(phaseOneActions));
	ActionRunner.queueAction(new PrintAction("Done."));
}