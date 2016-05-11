#include "Publisher.h"
#include <iostream>

Publisher::Publisher()
{
    Initialize("localhost", "testQueue", Event::NUM_TYPES);
}

Publisher::Publisher(std::string host, std::string queue, Event::eventType evtType)
{
	Initialize(host, queue, evtType);
}

Publisher::~Publisher()
{
}

void Publisher::publishEvent(Event *evt)
{
	//std::cout << "createMessage"; std::cin.ignore();
	const std::string messageText = "I am a(n) " + evt->getDescription() +" event!\n";
	AmqpClient::BasicMessage::ptr_t message = AmqpClient::BasicMessage::Create();
	message->Body(messageText);

	//std::cout << "publishMessage"; std::cin.ignore();
	m_channel->BasicPublish(exchangeName, routingKey, message);
}

void Publisher::Initialize(std::string host, std::string queue, Event::eventType evtType)
{
	m_channel = AmqpClient::Channel::Create(host);

	queueName = m_channel->DeclareQueue(queue/*, false, true, false, false*/);
	routingKey = "eventType_";

	m_channel->BindQueue(queueName, exchangeName, routingKey);
}