#include "robotlib/TaskMetricsTask.h"
#include "robotlib/RobotDataStream.h"
#include <sstream>

void TaskMetricsTask::Run()
{

}

void TaskMetricsTask::Disable()
{

}

void TaskMetricsTask::Always()
{
	std::stringstream output;
	output << "Task Data" << std::endl;
	uint32_t CurrentTime = getTimeMS();
	double RateMultiplier = 1000.0 / (double)(CurrentTime - LastReport);
	for (std::vector<DataItem *>::iterator i = TaskCounters.begin();
		i != TaskCounters.end();
		i++)
	{
		TaskMetricsData * counter = (TaskMetricsData *)(*i);
		output << counter->GetName() << ": " << (uint32_t)round(counter->GetRuns() * RateMultiplier);
		output << " Goal: " << counter->GetPeriod() <<  std::endl;
		counter->ResetRuns();
	}
	LastReport = getTimeMS();
	RobotReporter::LogMessage(RobotReporter::Info, output.str());
}

void TaskMetricsTask::Autonomous()
{

}

void TaskMetricsTask::Start()
{
	TaskCounters = DataStore::LookupDataItemBeginsWith("/taskmetrics/");
	LastReport = getTimeMS();
}

void TaskMetricsTask::Init()
{
}