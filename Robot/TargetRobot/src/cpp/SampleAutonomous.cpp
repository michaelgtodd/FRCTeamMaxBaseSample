#include "SampleAutonomous.h"
#include "robotlib/RobotDataStream.h"
#include "iostream"
#include <math.h>

void SampleAutonomous::Init()
{
	RobotLog::LogInfo("Starting Auto");

	std::cout << "Auto Init" << std::endl;

	StartTime = getTimeMS();
	
	LastMessage = 0;
}

void SampleAutonomous::ControllerUpdate(RobotControl * controls)
{
	// can get controller data here
}

void SampleAutonomous::Autonomous()
{
	double CurrentTime = getTimeMS();
	RunTime = CurrentTime - StartTime;
	if (floor(RunTime) > LastMessage)
	{
		LastMessage = (int) floor(RunTime);
		std::cout << "Running at " << std::to_string(LastMessage) << " seconds" << std::endl;
		RobotLog::LogInfo("Running at " + std::to_string(LastMessage) + " seconds");
	}
}

void SampleAutonomous::End()
{
	double CurrentTime = getTimeMS();
	RunTime = CurrentTime - StartTime;
	LastMessage = (int) floor(RunTime);
	RobotLog::LogInfo("Ending Auto after " + std::to_string(LastMessage) + " seconds");
}

std::string SampleAutonomous::GetName()
{
	return "Sample_Auto";
}
