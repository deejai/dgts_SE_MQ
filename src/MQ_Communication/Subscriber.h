#pragma once
#include "SimpleAmqpClient/SimpleAmqpClient.h"

class Subscriber
{
public:
    // Defaults to localhost if no host is provided
    Subscriber();
    Subscriber(std::string host, Event::eventType evtType, std::string queue);
    ~Subscriber();

    // Consume a single Event
	std::string getNextEventString();

private:
    AmqpClient::Channel::ptr_t m_channel;

	void Initialize(std::string host, Event::eventType evtType, std::string queue);

	// Generated in Initialize()
	std::string queueName;
	std::string exchangeName;
	std::string consumer_tag;
};