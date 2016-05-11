#include "CollisionEvent.h"

CollisionEvent::CollisionEvent()
{
	eventID = Event::eventType::COLLISION;
	description = "collision";
}


CollisionEvent::~CollisionEvent()
{
}