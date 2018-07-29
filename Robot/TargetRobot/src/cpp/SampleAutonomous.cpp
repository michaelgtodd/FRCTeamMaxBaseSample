#include "SampleAutonomous.h"
#include "robotlib/RobotDataStream.h"
#include <math.h>
#include <sstream>

void SampleAutonomous::Init()
{
	RobotReporter::LogMessage(RobotReporter::Pass, "Auto Init");

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

		std::stringstream output;
		output << "Running at " << std::to_string(LastMessage) << " seconds" << std::endl;
		RobotReporter::LogMessage(RobotReporter::Info, output.str());
	}
}

void SampleAutonomous::End()
{
	double CurrentTime = getTimeMS();
	RunTime = CurrentTime - StartTime;
	LastMessage = (int) floor(RunTime);
}

std::string SampleAutonomous::GetName()
{
	return "Sample_Auto";
}
