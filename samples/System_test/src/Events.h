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

using TestEventRef = std::shared_ptr<class TestEvent>;
    
class TestEvent : public ec::EventData {
    public:
    
    static ec::EventType TYPE;
    
    static TestEventRef create();
    
    ~TestEvent(){}
    ec::EventDataRef copy(){ return ec::EventDataRef(); }
    const char* getName() const;
    ec::EventType getEventType() const;
    
    void serialize( ci::Buffer &streamOut ){}
    void deSerialize( const ci::Buffer &streamIn ){}
    
    private:
        TestEvent();
};
    

