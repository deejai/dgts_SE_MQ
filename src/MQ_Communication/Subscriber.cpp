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
    AmqpClient::Envelope::ptr_t envelope = m_channel->BasicConsumeMessage(consumer_tag);
	std::cout << envelope->Message()->Body();
	m_channel->BasicAck(envelope->GetDeliveryInfo());
	return nullptr;
}

void Subscriber::Initialize(std::string host, Event::eventType evtType, std::string queue)
{
	m_channel = AmqpClient::Channel::Create(host);

	exchangeName = "eventType_" + std::to_string(evtType);
	m_channel->DeclareExchange(exchangeName, "fanout");

	queueName = m_channel->DeclareQueue(queue, false, true, false, false);
	m_channel->BindQueue(queueName, exchangeName, "");

	consumer_tag = m_channel->BasicConsume(queueName, "", true, false, true, 1);
}
