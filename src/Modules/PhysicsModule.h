#pragma once
#include "Module.h"

class physicsModule : public Module
{
public:
    physicsModule();
    ~physicsModule();

    // RabbitMQ input controls
    void connectAmqpInput();
    void disconnectAmqpInput();

    // Environment output controls
    void connectEnvironmentOutput();
    void disconnectEnvironmentOutput();

private:
	void start();
	void stop();
};