#pragma once
#include <string>
#include <sstream>
#include "RobotTask.h"
#include "RobotAction.h"
#include <string>
#include "RobotLibConfig.h"

#include "robotlib/osc/OscOutboundPacketStream.h"
#include "robotlib/osc/OscPacketListener.h"
#include "robotlib/osc/OscReceivedElements.h"
#include "robotlib/ip/UdpSocket.h"

class OSCData
{
	friend class OSCTransmitAction;
private:
	void virtual Encode() = 0;
};

class OSCString : public OSCData
{
public:
	OSCString(std::string label, std::string value);
private:
	OSCString();
	void Encode();
	std::string value;
	std::string label;
};

class OSCInt : public OSCData
{
public:
	OSCInt(std::string label, int32_t value);
private:
	OSCInt();
	void Encode();
	int32_t value;
	std::string label;
};

class OSCDouble : public OSCData
{
public:
	OSCDouble(std::string label, double value);
private:
	OSCDouble();
	void Encode();
	double value;
	std::string label;
};

class OSCTransmitAction : public RobotAction
{
	OSCTransmitAction(OSCData * DataPacket);
	bool isFinished();
	void update();
	void done();
	void start();

	std::vector<std::string> getName();
private:
	OSCTransmitAction();
	OSCData * OSCDataPacket;
	bool ranOnce = false;
};

class OSCReporter : public RobotTask
{
	friend class OSCData;
	friend class OSCDouble;
	friend class OSCString;
	friend class OSCInt;

	void Always();
	void Run();
	void Disable();
	void Autonomous();
	void Start();
	void Init();
private:
	static osc::OutboundPacketStream OSCStream;
	static SerialActionRunner ActionRunner;
	static UdpTransmitSocket OSCTransmitSocket;
};

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
