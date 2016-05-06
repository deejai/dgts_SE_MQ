#include "Subscriber.h"

Subscriber::Subscriber()
{
    m_channel = AmqpClient::Channel::Create("localhost");
    std::string queue = m_channel->DeclareQueue("test", false, false, false, true);
}

Subscriber::Subscriber(std::string host)
{
    m_channel = AmqpClient::Channel::Create(host);
    std::string queue = m_channel->DeclareQueue("test", false, false, false, true);
}

Subscriber::~Subscriber()
{
}

void Subscriber::getNextEvent()
{
    std::string consumer_tag = m_channel->BasicConsume("test", "");
    AmqpClient::Envelope::ptr_t envelope = m_channel->BasicConsumeMessage(consumer_tag);
}