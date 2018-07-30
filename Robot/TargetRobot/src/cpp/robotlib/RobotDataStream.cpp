#include "robotlib/RobotDataStream.h"
#include <iostream>

SerialActionRunner RobotReporter::ActionRunner("ConsoleRunner", 200);
SerialActionRunner OSCReporter::ActionRunner("OscRunner", 200);

char OSCBuffer[OSC_OUTPUT_BUFFER_SIZE];

osc::OutboundPacketStream OSCReporter::OSCStream(OSCBuffer, OSC_OUTPUT_BUFFER_SIZE);
UdpTransmitSocket OSCReporter::OSCTransmitSocket(IpEndpointName(OSC_IP, BROADCASTPORT));

OSCString::OSCString(std::string label, std::string value)
{
	OSCString::value = value;
	OSCString::label = label;
}

void OSCString::Encode()
{
	OSCReporter::OSCStream << osc::BeginMessage(label.c_str()) << value.c_str() << osc::EndMessage;
}

OSCInt::OSCInt(std::string label, int32_t value)
{
	OSCInt::value = value;
	OSCInt::label = label;
}

void OSCInt::Encode()
{
	OSCReporter::OSCStream << osc::BeginMessage(label.c_str()) << (int) value << osc::EndMessage;
}

OSCDouble::OSCDouble(std::string label, double value)
{
	OSCDouble::value = value;
	OSCDouble::label = label;
}

void OSCDouble::Encode()
{
	OSCReporter::OSCStream << osc::BeginMessage(label.c_str()) << (double)value << osc::EndMessage;
}

OSCTransmitAction::OSCTransmitAction(OSCData * DataPacket)
{
	OSCDataPacket = DataPacket;
}

bool OSCTransmitAction::isFinished()
{
	return ranOnce;
}

void OSCTransmitAction::update()
{
	OSCDataPacket->Encode();
	ranOnce = true;
}

void OSCTransmitAction::done()
{
	delete OSCDataPacket;
}

void OSCTransmitAction::start()
{

}

std::vector<std::string> OSCTransmitAction::getName()
{
	std::vector<std::string> temp;
	temp.push_back("OSCTransmit");
	return temp;
}

void OSCReporter::Always()
{
	OSCStream.Clear();
	ActionRunner.Run();
	OSCTransmitSocket.Send(OSCStream.Data(), OSCStream.Size());
}

void OSCReporter::Run()
{

}

void OSCReporter::Disable()
{

}

void OSCReporter::Autonomous()
{

}

void OSCReporter::Start()
{

}

void OSCReporter::Init()
{

}

void OSCReporter::AddOSCObject(OSCData * DataPacket)
{
	ActionRunner.queueAction(new OSCTransmitAction(DataPacket));
}

RobotReporterPrintAction::RobotReporterPrintAction(RobotReporter::ReportType type, std::string message)
{
	RobotReporterPrintAction::type = type;
	RobotReporterPrintAction::message = message;
}

bool RobotReporterPrintAction::isFinished()
{
	return ranOnce;
}

void RobotReporterPrintAction::update()
{
	RobotReporter::ProcessMessage(type, message);
	ranOnce = true;
}

void RobotReporterPrintAction::done()
{

}

void RobotReporterPrintAction::start()
{

}

std::vector<std::string> RobotReporterPrintAction::getName()
{
	std::vector<std::string> temp;
	temp.push_back("ConsoleWriterAction");
	return temp;
}

void RobotReporter::Always()
{
	ActionRunner.Run();
}

void RobotReporter::Run()
{

}

void RobotReporter::Disable()
{

}

void RobotReporter::Autonomous()
{

}

void RobotReporter::Start()
{

}

void RobotReporter::Init()
{

}

void RobotReporter::LogMessage(ReportType type, std::string message)
{
	ActionRunner.queueAction(new RobotReporterPrintAction(type, message));
}

void RobotReporter::ProcessMessage(ReportType type, std::string message)
{
	switch (type)
	{
	case Pass:
		std::cout << "PASS: ";
		break;
	case Info:
		std::cout << "INFO: ";
		break;
	case Error:
		std::cout << "ERROR: ";
		break;
	case Log:
		std::cout << "LOG: ";
		break;
	}
	std::cout << message << std::endl;
}
