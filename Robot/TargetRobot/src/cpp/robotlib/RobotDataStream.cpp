#include "maxutils/MaxDataStream.h"
#include "maxutils/MaxDefs.h"
#include "Robot.h"
#include <iostream>
#include <cerrno>
#include "pthread.h"

#include "osc/OscOutboundPacketStream.h"
#include "osc/OscPacketListener.h"
#include "osc/OscReceivedElements.h"
#include "ip/UdpSocket.h"

#define OUTPUT_BUFFER_SIZE 1024

namespace MaxLog
{

	static bool Initialized = false;

	class MaxPacketListener : public osc::OscPacketListener {
	protected:

		virtual void ProcessMessage(const osc::ReceivedMessage& m,
			const IpEndpointName& remoteEndpoint)
		{
			(void)remoteEndpoint;

			try {
				ControlTaskInstance.ProcessOscData(m);
			}
			catch (osc::Exception& e) {
				LogError("Failed to parse OSC message");
			}
		}
	};

	std::vector<UdpTransmitSocket *> transmitSockets;
	UdpTransmitSocket * lemurSocket;

	void RunListener()
	{
		MaxPacketListener listener;
		UdpListeningReceiveSocket s(
			IpEndpointName(IpEndpointName::ANY_ADDRESS, BROADCASTPORT),
			&listener);

		s.RunUntilSigInt();
	}

	void AddTargetAddress(std::string address)
	{
		if (!Initialized) 
		{
			try {
				transmitSockets.push_back(new UdpTransmitSocket(IpEndpointName(address.c_str(), BROADCASTPORT)));
			}
			catch (...)
			{
				std::cout << "Error adding endpoint: " << address << std::endl;
			}
		}
		else
		{
			std::cout << "Error adding endpoint: " << address << ", log already initialized" << std::endl;
		}
	}

	void InitializeMaxLog()
	{
		std::thread * oscReceiveThread =  new std::thread(&RunListener);

		int priority = 97;

		sched_param sch;
		sch.sched_priority = priority;

		if (pthread_setschedparam(oscReceiveThread->native_handle(), SCHED_FIFO, &sch) != 0)
		{
			std::cout << "Failed to set task: " << "OSCReceive priority: " << priority << " Error: " << " " << strerror(errno) << std::endl;
			MaxLog::LogError("Failed to set task: OSCReceive priority: " + std::to_string(priority) + " Error: " + strerror(errno));
		}
		else {
			std::cout << "Set priority for task: " << "OSCReceive priority: " << priority << std::endl;
			MaxLog::LogInfo("Set priority for task: OSCReceive priority: " + std::to_string(priority));
		}
	}

	void transmit(osc::OutboundPacketStream p)
	{
		for (std::vector<UdpTransmitSocket *>::iterator i = transmitSockets.begin();
			i < transmitSockets.end();
			i++)
		{
			(*i)->Send(p.Data(), p.Size());
		}
	}
	
	void LogPass(std::string error_message)
	{
		char buffer[OUTPUT_BUFFER_SIZE];

		osc::OutboundPacketStream p(buffer, OUTPUT_BUFFER_SIZE);

		p << osc::BeginMessage("/pass") << error_message.c_str() << osc::EndMessage;

		transmit(p);
	}

	void LogInfo(std::string error_message)
	{
		char buffer[OUTPUT_BUFFER_SIZE];

		osc::OutboundPacketStream p(buffer, OUTPUT_BUFFER_SIZE);

		p << osc::BeginMessage("/info") << error_message.c_str() << osc::EndMessage;

		transmit(p);
	}

	void LogError(std::string error_message)
	{
		char buffer[OUTPUT_BUFFER_SIZE];

		osc::OutboundPacketStream p(buffer, OUTPUT_BUFFER_SIZE);

		p << osc::BeginMessage("/error") << error_message.c_str() << osc::EndMessage;

		transmit(p);
	}
}