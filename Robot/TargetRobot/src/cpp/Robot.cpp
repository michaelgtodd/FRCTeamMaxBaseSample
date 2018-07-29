#include "Robot.h"
#include "robotlib/RobotTask.h"
#include "robotlib/RobotDataStream.h"
#include "robotlib/RobotAutonomous.h"
#include "SampleAutonomous.h"
#include "ParallelCounterSampleTask.h"
#include "SampleTask.h"

void Robot::RobotInit() 
{
	RobotReporter::LogMessage(RobotReporter::Pass, "Initializing Robot...");

	//RobotLog::InitializeRobotLog();

	AutonomousManagerInstance.RegisterAutonomous(new SampleAutonomous);

	// Task names cannot contain spaces at this time
	TaskSchedule::AddTask((RobotTask*)&AutonomousManagerInstance, "AutoManager", 500);
	//TaskContainer * SuperLoop = new TaskContainer();
	//SuperLoop->AddTask(new SampleTask(), "SampleTask");
	//SuperLoop->AddTask(new SampleTask(), "SampleTask2");
	//SuperLoop->AddTask(new SampleTask(), "SampleTask3");
	//TaskSchedule::AddTask(SuperLoop, "SuperLoop1", 10);
	TaskSchedule::AddTask(new ParallelCounterSampleTask(), "ParallelCounterSampletask", 10);

	TaskSchedule::LaunchTasks();
}

void Robot::Disabled() { }
void Robot::Autonomous() { }
void Robot::OperatorControl() { }
void Robot::Test() { }

#ifndef WIN32
START_ROBOT_CLASS(Robot)
#endif