#include "ParallelCounterSampleTask.h"
#include <iostream>
#include "robotlib/RobotDataStream.h"
#include "SampleActions/CounterAction.h"
#include "SampleActions/PrintAction.h"
#include "SampleActions/TimeoutPrintAction.h"

void ParallelCounterSampleTask::Run()
{

}

void ParallelCounterSampleTask::Disable()
{

}

void ParallelCounterSampleTask::Always()
{
	ActionRunner.Run();
}

void ParallelCounterSampleTask::Autonomous()
{

}

void ParallelCounterSampleTask::ControllerUpdate(RobotControl * controls)
{
	RobotControl * controls_ = (RobotControl *)(controls);
}

void ParallelCounterSampleTask::Init()
{
	ActionRunner.queueAction(new PrintAction("Starting parallel counter action test..."));
	CounterAction * sampleCounterAction = new CounterAction(1500000);
	ActionRunner.queueAction(sampleCounterAction);
	ActionRunner.queueAction(new TimeoutPrintAction(std::to_string(sampleCounterAction->getCounter()), 1000));
	ActionRunner.queueAction(new TimeoutPrintAction(std::to_string(sampleCounterAction->getCounter()), 2000));
	ActionRunner.queueAction(new TimeoutPrintAction(std::to_string(sampleCounterAction->getCounter()), 3000));
	ActionRunner.queueAction(new TimeoutPrintAction(std::to_string(sampleCounterAction->getCounter()), 4000));
}