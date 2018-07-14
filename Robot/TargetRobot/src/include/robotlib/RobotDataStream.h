#pragma once
#include <string>
#include "RobotTask.h"
#include <vector>

namespace MaxLog
{
	void InitializeMaxLog();
	void LogPass(std::string error_message);
	void LogInfo(std::string error_message);
	void LogError(std::string error_message);

	void AddTargetAddress(std::string address);
}