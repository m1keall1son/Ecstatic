//
//  EventManagerBase.h
//  RendererTest
//
//  Created by Ryan Bartley on 8/17/14.
//
//

#pragma once

#include "BaseEventData.h"
#include "FastDelegate.h"

namespace ec {
	
using EventListenerDelegate = fastdelegate::FastDelegate1<EventDataRef, void>;

class EventManagerBase {
public:
	
	enum eConstants { kINFINITE = 0xffffffff };
	explicit EventManagerBase( const std::string &name );
	virtual ~EventManagerBase();
	
	//! Registers a delegate function that will get called when the event type is
	//! triggered. Returns true if successful, false if not.
	virtual bool addListener( const EventListenerDelegate &eventDelegate, const EventType &type ) = 0;
	
	//! Removes a delegate / event type pairing from the internal tables.
	//! Returns false if the pairing was not found.
	virtual bool removeListener( const EventListenerDelegate &eventDelegate, const EventType &type ) = 0;
	
	//! Fires off event NOW. This bypasses the queue entirely and immediately
	//! calls all delegate functions registered for the event.
	virtual bool triggerEvent( const EventDataRef &event ) = 0;
	
	//! Fires off event. This uses the queue and will call the delegate
	//! function on the next call to tickUpdate. assuming there's enough time.
	virtual bool queueEvent( const EventDataRef &event ) = 0;
	
	// Finds the next-available instance of the named event type and remove it
	// from the processing queue. This may be done up to the point that it is
	// actively being processed ... e.g.: is safe to happen during event
	// processing itself.
	//
	// If allOfType is true, then all events of that type are cleared from the
	// input queue. //
	// returns true if the event was found and removed, false otherwise
	virtual bool abortEvent( const EventType& type, bool allOfType = false ) = 0;
	
	// Allows for processing of any queued messages, optionally specify a
	// processing time limit so that the event processing does not take too
	// long. Note the danger of using this artificial limiter is that all
	// messages may not in fact get processed.
	//
	// returns true if all messages ready for processing were completed, false
	// otherwise (e.g. timeout).
	virtual bool update( uint64_t maxMillis = kINFINITE ) = 0;
    
protected:
    
    std::string mName;
    
};

}