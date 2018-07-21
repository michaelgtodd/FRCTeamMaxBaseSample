#pragma once
#ifndef WIN32
#include "WPILib.h"
#endif
#include "RobotControl.h"
#include "robotlib/RobotTask.h"
#include "robotlib/osc/OscReceivedElements.h"
#include "robotlib/osc/OscPacketListener.h"
#include "robotlib/ip/UdpSocket.h"
#include <string.h>
#include "robotlib/RobotAutonomous.h"

class ControlTask : public RobotTask
{
public:
	void Always();
	void Run();
	void Disable();
	void ControllerUpdate(RobotControl * controls);
	void Autonomous();
	void ProcessOscData(osc::ReceivedMessage messages);
private:
	void Init();
	RobotControl * Controls;
};

extern ControlTask ControlTaskInstance;
extern TaskSchedule taskschedule;