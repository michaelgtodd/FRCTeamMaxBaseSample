#include "Robot.h"
#include "robotlib/RobotTask.h"
#include "robotlib/RobotDataStream.h"
#include "robotlib/RobotAutonomous.h"
#include "SampleAutonomous.h"
#include "robotlib/PowerReportingTask.h"
#include "SampleTask.h"
#include "iostream"

void Robot::RobotInit() 
{
	std::cout << "Initializing Robot..." << std::endl;

	RobotLog::InitializeRobotLog();

	AutonomousManagerInstance.RegisterAutonomous(new SampleAutonomous);

	// Task names cannot contain spaces at this time
	taskschedule.AddTask((RobotTask*)&ControlTaskInstance, "ControlTask", 100);
	taskschedule.AddTask((RobotTask*)&AutonomousManagerInstance, "AutoManager", 100);
	taskschedule.AddTask(new PowerReportingTask(), "PowerReporting", 20);
	taskschedule.AddTask(new SampleTask(), "Sampletask", 100);

	taskschedule.LaunchTasks();
}

void Robot::Disabled() { }
void Robot::Autonomous() { }
void Robot::OperatorControl() { }
void Robot::Test() { }

#ifndef WIN32
START_ROBOT_CLASS(Robot)
#endif