#pragma once
#include "SimpleAmqpClient/SimpleAmqpClient.h"
#include "Event.h"

class Publisher
{
public:
    // Defaults to localhost if no host is provided
    Publisher();
	Publisher(std::string host);
	Publisher(std::string host, std::string eventKey);
    ~Publisher();

    // Publish a single Event
    void publishEvent(Event* evt);

private:
    AmqpClient::Channel::ptr_t m_channel;

    void Initialize(std::string host, std::string eventKey);
	const std::string exchangeName = "amq.direct";

	// Declared in Initialize()
	std::string queueName;
	std::string routingKey;
};