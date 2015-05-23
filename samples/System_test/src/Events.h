//
//  Events.h
//  System_test
//
//  Created by Mike Allison on 4/28/15.
//
//

#pragma once

#include "BaseEventData.h"
#include "AppCommon.h"
    
class DrawDebugEvent : public ec::EventData {
    public:
    
    static ec::EventType TYPE;
    
    static DrawDebugEventRef create();
    
    ~DrawDebugEvent(){}
    ec::EventDataRef copy(){ return ec::EventDataRef(); }
    const char* getName() const;
    ec::EventType getEventType() const;
    
    void serialize( ci::Buffer &streamOut ){}
    void deSerialize( const ci::Buffer &streamIn ){}
    
    private:
        DrawDebugEvent();
};


class DrawShadowEvent : public ec::EventData {
public:
    
    static ec::EventType TYPE;
    
    static DrawShadowEventRef create();
    
    ~DrawShadowEvent(){}
    ec::EventDataRef copy(){ return ec::EventDataRef(); }
    const char* getName() const;
    ec::EventType getEventType() const;
    
    void serialize( ci::Buffer &streamOut ){}
    void deSerialize( const ci::Buffer &streamIn ){}
    
private:
    DrawShadowEvent();
};

