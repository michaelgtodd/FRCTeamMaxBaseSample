#pragma once
#include "maxutils/MaxTask.h"
#include "osc/OscReceivedElements.h"
#include "osc/OscPacketListener.h"
#include "ip/UdpSocket.h"
#include "WPILib.h"
#include <string.h>
#include "maxutils\MaxAutonomous.h"

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