#include "robotlib/ActionMetricsTask.h"
#include <iostream>
#include <sstream>

void ActionMetricsTask::Run()
{

}

void ActionMetricsTask::Disable()
{

}

void ActionMetricsTask::Always()
{
	std::stringstream output;
	output << "Action Data" << std::endl;
	uint32_t CurrentTime = getTimeMS();
	double RateMultiplier = 1000.0 / (double)(CurrentTime - LastReport);
	for (std::vector<DataItem *>::iterator i = ActionMetrics.begin();
		i != ActionMetrics.end();
		i++)
	{
		ActionRunnerDataItem * MetricsData = (ActionRunnerDataItem *)(*i);
		std::vector<std::string> actions = MetricsData->GetRunningActions();
		if (!actions.empty())
		{
			output << "ActionRunner: " << MetricsData->GetRunnerName() << ": " << std::endl;
			for (std::vector<std::string>::iterator i = actions.begin();
				i != actions.end();
				i++)
			{
				output << "\t" << (*i) << std::endl;
			}
		}
	}
	LastReport = getTimeMS();
	std::cout << output.rdbuf();
}

void ActionMetricsTask::Autonomous()
{

}

void ActionMetricsTask::Start()
{
	ActionMetrics = DataStore::LookupDataItemBeginsWith("/actionmetrics/");
	std::cout << "looked up..." << std::endl;
	LastReport = getTimeMS();
}

void ActionMetricsTask::Init()
{
}