#include "EventHandler.h"

EventHandler::EventHandler()
{
    // No events ignored by default
    for (int i = 0; i < Event::eventType::NUM_TYPES; i++) {
        ignoredEvents[i] = false;
    }


}

EventHandler::~EventHandler()
{
}

void EventHandler::run(std::string host)
{
    if (running) { return; }

    /*int t1, t2;
    boost::thread acceptorThread;
    boost:: emitterThread;

    t1 = pthread_create(&acceptorThread, NULL, acceptor, (void *)&host);
    t2 = pthread_create(&emitterThread, NULL, emitter, (void *)&host);
    if (t1 || t2) {
        printf("Thread creation failed\n");
    }*/
}

int EventHandler::numUnprocessedEventsQueued()
{
    return 0;
}

int EventHandler::numProcessedEventsQueued()
{
    return 0;
}

int EventHandler::numEventsQueued()
{
    if (start_index > end_index) {
        return MAX_QUEUED_EVENTS + end_index - start_index;
    }
    else {
        return end_index - start_index;
    }
}

void* EventHandler::acceptor(void* host)
{
    return nullptr;
}

void* EventHandler::emitter(void* host)
{
    return nullptr;
}
