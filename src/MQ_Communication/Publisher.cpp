#include "Publisher.h"
#include <iostream>

Publisher::Publisher()
{
    Initialize("localhost", "testEvent");
}

Publisher::Publisher(std::string host)
{
	Initialize(host, "testEvent");
}

Publisher::Publisher(std::string host, std::string eventKey)
{
	Initialize(host, eventKey);
}

Publisher::~Publisher()
{
}

void Publisher::publishEvent(Event *evt)
{
	//std::cout << "createMessage"; std::cin.ignore();
	const std::string messageText = "MSG_004";
	AmqpClient::BasicMessage::ptr_t message = AmqpClient::BasicMessage::Create();
	message->Body(messageText);

	//std::cout << "publishMessage"; std::cin.ignore();
	m_channel->BasicPublish(exchangeName, routingKey, message);
}

void Publisher::Initialize(std::string host, std::string eventKey)
{
	m_channel = AmqpClient::Channel::Create(host);

	queueName = m_channel->DeclareQueue("");
	routingKey = eventKey;

	m_channel->BindQueue(queueName, exchangeName, routingKey);
}