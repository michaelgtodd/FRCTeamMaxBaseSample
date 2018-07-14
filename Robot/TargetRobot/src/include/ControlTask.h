#pragma once
#ifndef WIN32
#include "WPILib.h"
#endif
#include "robotlib/RobotTask.h"
#include "robotlib/osc/OscReceivedElements.h"
#include "robotlib/osc/OscPacketListener.h"
#include "robotlib/ip/UdpSocket.h"
#include <string.h>
#include "robotlib/RobotAutonomous.h"

using namespace std;

class RobotControl : public MaxControl
{
public:
	RobotControl();
};

class AutonomousControl : public MaxControl
{
public:
};

class ControlTask : public MaxTask
{
public:
	void Always();
	void Run();
	void Disable();
	void ControllerUpdate(MaxControl * controls);
	void Autonomous();
	void ProcessOscData(osc::ReceivedMessage messages);
	void UpdateAutonomousData(AutonomousControl AutoControlInput);
private:
	void Init();
	RobotControl * Controls;
	AutonomousControl * Auto;
};

extern ControlTask ControlTaskInstance;
extern MaxTaskSchedule taskschedule;