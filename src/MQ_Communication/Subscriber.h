#pragma once
#include "SimpleAmqpClient/SimpleAmqpClient.h"
#include "Event.h"

class Subscriber
{
public:
    // Defaults to localhost if no host is provided
    Subscriber();
    Subscriber(std::string host);

    ~Subscriber();

    Event *getNextEvent();
    void startConsumingEvents();
    void stopConsumingEvents();

private:
    AmqpClient::Channel::ptr_t m_channel;
};