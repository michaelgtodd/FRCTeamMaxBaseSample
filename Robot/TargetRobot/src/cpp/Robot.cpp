#include "Robot.h"
#include "robotlib/RobotTask.h"
#include "robotlib/RobotDataStream.h"
#include "robotlib/RobotAutonomous.h"
#include "DriveTrainTask.h"

void Robot::RobotInit() 
{
	RobotReporter::LogMessage(RobotReporter::Pass, "Initializing Robot...");

	//AutonomousManagerInstance.RegisterAutonomous(new SampleAutonomous);

	// Task names cannot contain spaces at this time
	TaskSchedule::AddTask(new DriveTrainTask(), "DriveTrain", 100);
	TaskSchedule::AddTask(&AutonomousManagerInstance, "AutoManager", 100);

	TaskSchedule::LaunchTasks();
}

void Robot::Disabled() { }
void Robot::Autonomous() { }
void Robot::OperatorControl() { }
void Robot::Test() { }

#ifndef WIN32
START_ROBOT_CLASS(Robot)
#endif