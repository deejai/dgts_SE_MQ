#include "Subscriber.h"

Subscriber::Subscriber()
{
	Initialize("localhost", "testQueue", Event::NUM_TYPES);
}

Subscriber::Subscriber(std::string host, std::string queue, Event::eventType evtType)
{
	Initialize(host, queue, evtType);
}

Subscriber::~Subscriber()
{
}

Event *Subscriber::getNextEvent()
{
    //std::string consumer_tag = m_channel->BasicConsume("test", "");
    //AmqpClient::Envelope::ptr_t envelope = m_channel->BasicConsumeMessage(consumer_tag);

	return nullptr;
}

void Subscriber::Initialize(std::string host, std::string queue, Event::eventType evtType)
{
	m_channel = AmqpClient::Channel::Create(host);

	queueName = m_channel->DeclareQueue(queue/*, false, true, false, false*/);
	routingKey = "eventType_";

	m_channel->BindQueue(queueName, exchangeName, routingKey);
}
