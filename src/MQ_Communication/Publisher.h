#pragma once
#include "SimpleAmqpClient/SimpleAmqpClient.h"
#include "Event.h"

class Publisher
{
public:
    // Defaults to localhost if no host is provided
    Publisher();
	Publisher(std::string host, Event::eventType evtType, std::string queue);
    ~Publisher();

    // Publish a single Event
    void publishEvent(Event* evt);

protected:
	void Initialize(std::string host, Event::eventType evtType, std::string queue);

private:
    AmqpClient::Channel::ptr_t m_channel;

	const std::string exchangeName = "amq.fanout";

	// Declared in Initialize()
	std::string queueName;
	std::string routingKey;
};