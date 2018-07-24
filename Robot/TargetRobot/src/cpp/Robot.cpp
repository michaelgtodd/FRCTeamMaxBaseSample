#include "Robot.h"
#include "robotlib/RobotTask.h"
#include "robotlib/RobotDataStream.h"
#include "robotlib/RobotAutonomous.h"
#include "SampleAutonomous.h"
#include "ParallelCounterSampleTask.h"
#include "SampleTask.h"
#include "iostream"

void Robot::RobotInit() 
{
	std::cout << "Initializing Robot..." << std::endl;

	RobotLog::InitializeRobotLog();

	AutonomousManagerInstance.RegisterAutonomous(new SampleAutonomous);

	// Task names cannot contain spaces at this time
	TaskSchedule::AddTask((RobotTask*)&AutonomousManagerInstance, "AutoManager", 100);
	// taskschedule.AddTask(new SampleTask(), "Sampletask", 100);
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