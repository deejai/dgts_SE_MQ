#pragma once
#include "SimpleAmqpClient/SimpleAmqpClient.h"
#include "Event.h"

class Subscriber
{
public:
    // Defaults to localhost if no host is provided
    Subscriber();
    Subscriber(std::string host, Event::eventType evtType, std::string queue);
    ~Subscriber();

    // Consume a single Event
	Event *getNextEvent();

private:
    AmqpClient::Channel::ptr_t m_channel;

	void Initialize(std::string host, Event::eventType evtType, std::string queue);
	const std::string exchangeName = "amq.direct";

	// Generated in Initialize()
	std::string queueName;
	std::string routingKey;
};