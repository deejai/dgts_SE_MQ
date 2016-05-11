#pragma once
#include "SimpleAmqpClient/SimpleAmqpClient.h"
#include "Event.h"

class Subscriber
{
public:
    // Defaults to localhost if no host is provided
    Subscriber();
    Subscriber(std::string host);
    ~Subscriber();

    // Consume a single Event
	Event *getNextEvent();

private:
    AmqpClient::Channel::ptr_t m_channel;

	void Initialize(std::string host);
	const std::string exchangeName = "amq.direct";
	const std::string routingKey = "";

	// Generated in Initialize()
	std::string queueName;
};