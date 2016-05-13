#include "Publisher.h"
#include <iostream>

Publisher::Publisher()
{
    Initialize("localhost", Event::NUM_TYPES, "testQueue");
}

Publisher::Publisher(std::string host, Event::eventType evtType, std::string queue)
{
	Initialize(host, evtType, queue);
}

Publisher::~Publisher()
{
}

void Publisher::publishEvent(Event *evt)
{
	//std::cout << "createMessage"; std::cin.ignore();
	const std::string messageText = "eventType_" + std::to_string(evt->getEventID());
	AmqpClient::BasicMessage::ptr_t message = AmqpClient::BasicMessage::Create();
	message->Body(messageText);

	//std::cout << "publishMessage"; std::cin.ignore();
	m_channel->BasicPublish(exchangeName, routingKey, message);
}

void Publisher::Initialize(std::string host, Event::eventType evtType, std::string queue)
{
	m_channel = AmqpClient::Channel::Create(host);

	queueName = m_channel->DeclareQueue(queue, false, true, false, false);
	routingKey = "eventType_" + std::to_string(evtType);

	m_channel->BindQueue(queueName, exchangeName, routingKey);
}