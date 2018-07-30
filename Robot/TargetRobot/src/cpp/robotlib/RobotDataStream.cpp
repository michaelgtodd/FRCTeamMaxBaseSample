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
	}
	std::cout << message << std::endl;
}








//#include "robotlib/RobotDataStream.h"
//#include "robotlib/RobotDefs.h"
//#include "Robot.h"
//#include <cerrno>
//
//#ifndef WIN32
//#include "pthread.h"
//#endif
//
//#include "robotlib/osc/OscOutboundPacketStream.h"
//#include "robotlib/osc/OscPacketListener.h"
//#include "robotlib/osc/OscReceivedElements.h"
//#include "robotlib/ip/UdpSocket.h"
//
//#define OUTPUT_BUFFER_SIZE 1024
//
//namespace RobotLog
//{
//
//	static bool Initialized = false;
//
//	class PacketListener : public osc::OscPacketListener {
//	protected:
//
//		virtual void ProcessMessage(const osc::ReceivedMessage& m,
//			const IpEndpointName& remoteEndpoint)
//		{
//			(void)remoteEndpoint;
//
//			try {
//				//TODO - what do I do
//			}
//			catch (...) {
//				LogError("Failed to parse OSC message");
//			}
//		}
//	};
//
//	std::vector<UdpTransmitSocket *> transmitSockets;
//	UdpTransmitSocket * lemurSocket;
//
//	void RunListener()
//	{
//		PacketListener listener;
//		UdpListeningReceiveSocket s(
//			IpEndpointName(IpEndpointName::ANY_ADDRESS, BROADCASTPORT),
//			&listener);
//
//		s.RunUntilSigInt();
//	}
//
//	void AddTargetAddress(std::string address)
//	{
//		if (!Initialized) 
//		{
//			try {
//				transmitSockets.push_back(new UdpTransmitSocket(IpEndpointName(address.c_str(), BROADCASTPORT)));
//			}
//			catch (...)
//			{
//				std::cout << "Error adding endpoint: " << address << std::endl;
//			}
//		}
//		else
//		{
//			std::cout << "Error adding endpoint: " << address << ", log already initialized" << std::endl;
//		}
//	}
//
//	void InitializeRobotLog()
//	{
//#ifndef WIN32
//		std::thread * oscReceiveThread =  new std::thread(&RunListener);
//
//		int priority = 97;
//
//		sched_param sch;
//		sch.sched_priority = priority;
//
//		if (pthread_setschedparam(oscReceiveThread->native_handle(), SCHED_FIFO, &sch) != 0)
//		{
//			std::cout << "Failed to set task: " << "OSCReceive priority: " << priority << " Error: " << " " << strerror(errno) << std::endl;
//			RobotLog::LogError("Failed to set task: OSCReceive priority: " + std::to_string(priority) + " Error: " + strerror(errno));
//		}
//		else {
//			std::cout << "Set priority for task: " << "OSCReceive priority: " << priority << std::endl;
//			RobotLog::LogInfo("Set priority for task: OSCReceive priority: " + std::to_string(priority));
//		}
//#endif
//	}
//
//	void transmit(osc::OutboundPacketStream p)
//	{
//		for (std::vector<UdpTransmitSocket *>::iterator i = transmitSockets.begin();
//			i < transmitSockets.end();
//			i++)
//		{
//			(*i)->Send(p.Data(), p.Size());
//		}
//	}
//	
//	void LogPass(std::string error_message)
//	{
//		char buffer[OUTPUT_BUFFER_SIZE];
//
//		osc::OutboundPacketStream p(buffer, OUTPUT_BUFFER_SIZE);
//
//		p << osc::BeginMessage("/pass") << error_message.c_str() << osc::EndMessage;
//
//		std::cout << error_message << std::endl;
//
//		transmit(p);
//	}
//
//	void LogInfo(std::string error_message)
//	{
//		char buffer[OUTPUT_BUFFER_SIZE];
//
//		osc::OutboundPacketStream p(buffer, OUTPUT_BUFFER_SIZE);
//
//		p << osc::BeginMessage("/info") << error_message.c_str() << osc::EndMessage;
//
//		std::cout << error_message << std::endl;
//
//		transmit(p);
//	}
//
//	void LogError(std::string error_message)
//	{
//		char buffer[OUTPUT_BUFFER_SIZE];
//
//		osc::OutboundPacketStream p(buffer, OUTPUT_BUFFER_SIZE);
//
//		p << osc::BeginMessage("/error") << error_message.c_str() << osc::EndMessage;
//
//		std::cout << error_message << std::endl;
//
//		transmit(p);
//	}
//}