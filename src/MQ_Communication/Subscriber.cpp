#include "Subscriber.h"

Subscriber::Subscriber()
{
	Initialize("localhost", Event::NUM_TYPES, "testQueue");
}

Subscriber::Subscriber(std::string host, Event::eventType evtType, std::string queue)
{
	Initialize(host, evtType, queue);
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

void Subscriber::Initialize(std::string host, Event::eventType evtType, std::string queue)
{
	m_channel = AmqpClient::Channel::Create(host);

	queueName = m_channel->DeclareQueue(queue, false, true, false, false);
	routingKey = "eventType_";

	m_channel->BindQueue(queueName, exchangeName, routingKey);
}
