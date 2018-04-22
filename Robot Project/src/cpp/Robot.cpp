#include "Robot.h"
#include "maxutils/MaxTask.h"
#include "maxutils/MaxDataStream.h"
#include "maxutils/MaxAutonomous.h"
#include "SampleAutonomous.h"
#include "PowerReportingTask.h"
#include "iostream"

void Robot::RobotInit() 
{
	MaxLog::InitializeMaxLog();

	MaxAutonomousManagerInstance.RegisterAutonomous(new SampleAutonomous);

	// Task names cannot contain spaces at this time
	taskschedule.AddTask((MaxTask*)&ControlTaskInstance, "ControlTask", 100);
	taskschedule.AddTask((MaxTask*)&MaxAutonomousManagerInstance, "AutoManager", 100);
	taskschedule.AddTask(new PowerReportingTask(), "PowerReporting", 20);

	taskschedule.LaunchTasks();
}

void Robot::Disabled() { }
void Robot::Autonomous() { }
void Robot::OperatorControl() { }
void Robot::Test() { }

START_ROBOT_CLASS(Robot)