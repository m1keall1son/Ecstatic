//
//  Events.cpp
//  System_test
//
//  Created by Mike Allison on 4/28/15.
//
//

#include "Events.h"
#include "Common.h"


ec::EventType TestEvent::TYPE = ec::getHash("test_event");

TestEventRef TestEvent::create()
{
    return TestEventRef( new TestEvent() );
}

TestEvent::TestEvent() : ec::EventData( cinder::app::getElapsedSeconds() ){}

const char* TestEvent::getName() const
{
    return "test_event";
}

ec::EventType TestEvent::getEventType() const
{
    return TestEvent::TYPE;
}