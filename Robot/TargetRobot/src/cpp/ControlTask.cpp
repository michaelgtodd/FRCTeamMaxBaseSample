#include "ControlTask.h"
#include "maxutils/MaxDataStream.h"
#include "maxutils/MaxControls.h"
#include <iostream>
#include <math.h>

using namespace std;

ControlTask ControlTaskInstance;

RobotControl::RobotControl()
{

}

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

void ControlTask::ControllerUpdate(MaxControl * controls)
{

}

void ControlTask::Autonomous()
{

}

void ControlTask::UpdateAutonomousData(AutonomousControl AutoControlInput)
{

}

void ControlTask::ProcessOscData(osc::ReceivedMessage messages)
{

}

void ControlTask::Init()
{

}