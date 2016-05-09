project (SE_MQ)

set(HEADERS
    Core/Event.h
    Core/EventHandler.h
    Core/Module.h
    Core/SE_MQ_Client.h
    Events/CollisionEvent.h
    Events/MunitionEvent.h
    Events/PhysicsEvent.h
    Modules/ApiModule.h
    Modules/MunitionModule.h
    Modules/PhysicsModule.h
    MQ_Communication/Publisher.h
    MQ_Communication/Subscriber.h
)	
	
set(SOURCES
    Core/Event.cpp
    Core/EventHandler.cpp
    Core/Module.cpp
    Core/SE_MQ_Client.cpp
    Events/CollisionEvent.cpp
    Events/MunitionEvent.cpp
    Events/PhysicsEvent.cpp
    Modules/ApiModule.cpp
    Modules/MunitionModule.cpp
    Modules/PhysicsModule.cpp    
    MQ_Communication/Publisher.cpp
    MQ_Communication/Subscriber.cpp    
)

set (DEPENDENCIES
	${BOOST_LIBRARIES}
	${RABITMQC_LIBRARIES}
	${SIMPLEAMQPCLIENT_LIBRARIES}
)

include_directories (
	${BOOST_INCLUDE_DIR}
	${RABITMQC_INCLUDE_DIR}
	${SIMPLEAMQPCLIENT_INCLUDE_DIR}
    Core
    Events
    Modules
    MQ_Communication
)
	
add_executable (
    ${PROJECT_NAME} 
    ${HEADERS}
    ${SOURCES})

target_link_libraries(${PROJECT_NAME} ${DEPENDENCIES})
