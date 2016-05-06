#pragma once
#include "Module.h"

class ApiModule : public Module
{
public:
    ApiModule();
    ~ApiModule();

    // Munition stream API input controls
    void connectMunitionStream();
    void disconnectMunitionStream();

    // RabbitMQ output controls
    void connectAmqpOutput();
    void disconnectAmqpOutput();

private:
    void start();
    void stop();
};