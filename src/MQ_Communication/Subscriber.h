#pragma once
#include "SimpleAmqpClient.h"

class Subscriber
{
public:
    // Defaults to localhost if no host is provided
    Subscriber();
    Subscriber(std::string host);

    ~Subscriber();

    void getNextEvent();
    void startConsumingEvents();
    void stopConsumingEvents();

private:
    AmqpClient::Channel::ptr_t m_channel;
};