#pragma once
#include "SimpleAmqpClient.h"
#include "Event.h"

class Publisher
{
public:
    // Defaults to localhost if no host is provided
    Publisher();
    ~Publisher();

    // Publish a single event
    void publishEvent(Event* evt);

    void pubTest();

private:
    AmqpClient::Channel::ptr_t m_channel;

    void Initialize();
	const std::string host = "localhost";
	const std::string queueName = "";
	const std::string exchangeName = "amq.direct";
    const std::string routingKey = "";
};