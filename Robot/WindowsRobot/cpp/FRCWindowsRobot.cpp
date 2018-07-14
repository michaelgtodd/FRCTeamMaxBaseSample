#pragma once

#include "FRCWindowsRobot.h"

bool RobotState::IsOperatorControl()
{
	return false;
}

bool RobotState::IsEnabled()
{
	return false;
}

bool RobotState::IsAutonomous()
{
	return false;
}