#include "robotlib/PowerReportingTask.h"
#include <iostream>
#include "robotlib/RobotDataStream.h"
#include "ControlTask.h"
#include "robotlib/RobotDataStream.h"

void PowerReportingTask::Run()
{

}

void PowerReportingTask::Disable()
{

}

double AveragePowerValues[16];

void PowerReportingTask::Always()
{
	for (int i = 0; i < 16; i++)
	{
#ifndef WIN32
		AveragePowerValues[i] = (((AveragePowerValues[i] * 20.0) - AveragePowerValues[i]) + PDP->GetCurrent(i)) / 20.0;
#endif
	}

	for (int i = 0; i < 16; i++)
	{
		//MaxLog::TransmitDouble("/power/" + std::to_string(i), AveragePowerValues[i]);
	}

	//MaxLog::TransmitDouble("/Power/Total/", PDP->GetTotalCurrent());
}

void PowerReportingTask::Autonomous()
{

}

void PowerReportingTask::ControllerUpdate(MaxControl * controls)
{

}

void PowerReportingTask::Init()
{
#ifndef WIN32
	PDP = new PowerDistributionPanel();
#endif
	for (int i = 0; i < 16; i++)
	{
		AveragePowerValues[i] = 0;
	}
}