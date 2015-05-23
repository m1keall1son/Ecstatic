//
//  Events.cpp
//  System_test
//
//  Created by Mike Allison on 4/28/15.
//
//

#include "Events.h"
#include "Common.h"


//DRAW DEBUG -------------------------------------------------------------/

ec::EventType DrawDebugEvent::TYPE = ec::getHash("draw_debug_event");

DrawDebugEventRef DrawDebugEvent::create()
{
    return DrawDebugEventRef( new DrawDebugEvent() );
}

DrawDebugEvent::DrawDebugEvent() : ec::EventData( cinder::app::getElapsedSeconds() ){}

const char* DrawDebugEvent::getName() const
{
    return "draw_debug_event";
}

ec::EventType DrawDebugEvent::getEventType() const
{
    return DrawDebugEvent::TYPE;
}

//DRAW SHADOW -------------------------------------------------------------/

ec::EventType DrawShadowEvent::TYPE = ec::getHash("draw_shadow_event");

DrawShadowEventRef DrawShadowEvent::create()
{
    return DrawShadowEventRef( new DrawShadowEvent() );
}

DrawShadowEvent::DrawShadowEvent() : ec::EventData( cinder::app::getElapsedSeconds() ){}

const char* DrawShadowEvent::getName() const
{
    return "draw_shadow_event";
}

ec::EventType DrawShadowEvent::getEventType() const
{
    return DrawShadowEvent::TYPE;
}
