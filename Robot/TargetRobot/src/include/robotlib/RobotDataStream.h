#pragma once
#include <string>
#include <sstream>
#include "RobotTask.h"
#include "RobotAction.h"
#include <string>


class RobotReporter : public RobotTask
{
	friend class RobotReporterPrintAction;
public:
	enum ReportType { Pass, Info, Error };
	void Always();
	void Run();
	void Disable();
	void Autonomous();
	void Start();
	void Init();
	static void LogMessage(ReportType type, std::string message);
private:
	static void ProcessMessage(ReportType type, std::string message);
	static SerialActionRunner ActionRunner;
};

class RobotReporterPrintAction : public RobotAction
{
public:
	RobotReporterPrintAction(RobotReporter::ReportType type, std::string message);

	bool isFinished();
	void update();
	void done();
	void start();

	std::vector<std::string> getName();
private:
	RobotReporterPrintAction();
	RobotReporter::ReportType type;
	std::string message;
	bool ranOnce = false;
};
