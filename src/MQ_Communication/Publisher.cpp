#include "Publisher.h"
#include <iostream>

Publisher::Publisher()
{
    Initialize();
}

Publisher::~Publisher()
{
}

void Publisher::publishEvent(Event *evt)
{
}

void Publisher::pubTest()
{
}

void Publisher::Initialize()
{
	//std::cout << "host        " << " @ [" << &host		   << "]\n";
	//std::cout << "queueName   "	<< " @ [" << &queueName	   << "]\n";
	//std::cout << "exchangeName" << " @ [" << &exchangeName << "]\n";
	//std::cout << "routingKey  "	<< " @ [" << &routingKey   << "]\n\n";

	m_channel = AmqpClient::Channel::Create(host);

    //std::cout << "declareQueue"; std::cin.ignore();
	const std::string qName = m_channel->DeclareQueue(queueName);
	//std::cout << qName << " created.\n";

	//std::cout << "bindQueue"; std::cin.ignore();
	m_channel->BindQueue(qName, exchangeName, routingKey);

	//std::cout << "createMessage"; std::cin.ignore();
	const std::string messageText = "MSG_004";
	AmqpClient::BasicMessage::ptr_t message = AmqpClient::BasicMessage::Create();
	message->Body(messageText);
	
	//std::cout << "publishMessage"; std::cin.ignore();
	m_channel->BasicPublish(exchangeName, routingKey, message);
	
	//std::cout << "end"; std::cin.ignore();
}