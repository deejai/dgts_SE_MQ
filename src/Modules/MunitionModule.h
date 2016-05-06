#pragma once
#include "Module.h"

class munitionModule : public Module
{
public:
    munitionModule();
    ~munitionModule();

    // RabbitMQ input controls
    void connectAmqpInput();
    void disconnectAmqpInput();

    // RabbitMQ output controls
    void connectAmqpOutput();
    void disconnectAmqpOutput();

private:
    void start();
    void stop();
};

