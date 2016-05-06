#pragma once
#include "SE_MQ_Client.h"
#include "SimpleAmqpClient.h"
#include "publisher.h"

int main()
{
    Publisher* pub = new Publisher();
	//delete pub;
	std::cout << "END_MAIN"; std::cin.ignore();
	
    // TODO: Display menu if no command line argument was received
        // "Run SE_RabbitMQ_Client as:"
        // "1. apiModule"
        // "2. munitionModule"
        // "3. physicsModule"
        // "(API -> apiModule -> munitionModule -> physicsModule -> Environment)"
        // Handle user input, loop if invalid

    // TODO: Initialize chosen node
        // Instantiate node
        // Connect node's subscriber to input
        // Connect node's publisher to output
        // Start subscriber
        // Start publisher

    return 0;
}
