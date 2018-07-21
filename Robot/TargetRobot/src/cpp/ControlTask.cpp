#include "ControlTask.h"
#include "robotlib/RobotDataStream.h"
#include "RobotControl.h"
#include <iostream>
#include <math.h>

using namespace std;

ControlTask ControlTaskInstance;

void ControlTask::Run()
{

}

void ControlTask::Always()
{
	taskschedule.DispatchControl(Controls); // This must remain in Always()
}

void ControlTask::Disable()
{

}

void ControlTask::ControllerUpdate(RobotControl * controls)
{

}

void ControlTask::Autonomous()
{

}

void ControlTask::ProcessOscData(osc::ReceivedMessage messages)
{

}

void ControlTask::Init()
{

}