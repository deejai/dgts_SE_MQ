#pragma once
#include "SE_MQ_Client.h"
#include "ApiModule.h"
#include "MunitionModule.h"
#include "PhysicsModule.h"

int main(int argc, char *argv[])
{
	int choice = 0;
	
	if (argc > 1) {
		choice = argv[1][0] - '0';
	}
	
	std::cout << "[" << choice << "]\n";

	while (choice < 1 || choice > 3)
	{
		// Display menu if no command line argument was received
		std::cout << "Run SE_RabbitMQ_Client as:\n"
				  << "1. Api Module\n"
				  << "2. Munition Module\n"
				  << "3. Physics Module\n"
				  << "(API -> apiModule -> munitionModule -> physicsModule -> Environment)\n";
		std::cin >> choice;
			// TODO: Handle user input, loop if invalid
	}

	// Module
	Module *mod;

    // TODO: Initialize chosen module
	switch (choice)
	{
	case 1:
		mod = new ApiModule();
		break;

	case 2:
		mod = new MunitionModule();
		break;

	case 3:
		mod = new PhysicsModule();
		break;

	default:
		std::cout << "This should never happen.\n";
		return -1;
	}

	mod->run();

    return 0;
}
