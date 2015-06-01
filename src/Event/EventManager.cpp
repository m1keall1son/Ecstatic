//
//  EventManager.cpp
//  RendererTest
//
//  Created by Ryan Bartley on 8/17/14.
//
//

#include "EventManager.h"
#include "cinder/Log.h"
#include "cinder/app/App.h"

//#define LOG_EVENT( stream )	CI_LOG_I( stream )
#define LOG_EVENT( stream )	((void)0)

using namespace ci;
using namespace std;

namespace ec {
	
EventManager::EventManager( const std::string &name )
: EventManagerBase( name ), mActiveQueue( 0 )
{
	
}
	
EventManagerRef EventManager::create( const std::string &name )
{
	return EventManagerRef( new EventManager( name ) );
}
	
EventManager::~EventManager()
{
}

void EventManager::clear()
{
    mEventListeners.clear();
    for( int i = 0; i < NUM_QUEUES; i++ )mQueues[i].clear();
}
	
bool EventManager::addListener( const EventListenerDelegate &eventDelegate, const EventType &type )
{
	LOG_EVENT( "Attempting to add delegate function for event type: " + to_string( type ) );
	
	auto & eventDelegateList = mEventListeners[type];
	auto listenIt = eventDelegateList.begin();
	auto end = eventDelegateList.end();
	while ( listenIt != end ) {
		if ( eventDelegate == (*listenIt) ) {
			CI_LOG_W("Attempting to double-register a delegate");
			return false;
		}
		++listenIt;
	}
	eventDelegateList.push_back(eventDelegate);
	CI_LOG_V("Successfully added delegate for event type: " + to_string( type ) );
	return true;
}
	
bool EventManager::removeListener( const EventListenerDelegate &eventDelegate, const EventType &type )
{
	LOG_EVENT("Attempting to remove delegate function from event type: " + to_string( type ) );
	bool success = false;
	
	auto found = mEventListeners.find(type);
	if( found != mEventListeners.end() ) {
		auto & listeners = found->second;
		for( auto listIt = listeners.begin(); listIt != listeners.end(); ++listIt ) {
			if( eventDelegate == (*listIt) ) {
				listeners.erase(listIt);
                CI_LOG_V("Successfully removed delegate for event type: " + to_string( type ) );
				success = true;
				break;
			}
		}
	}
	return success;
}
	
bool EventManager::triggerEvent( const EventDataRef &event )
{
	LOG_EVENT("Attempting to trigger event: " + std::string( event->getName() ) );
	bool processed = false;
	
	auto found = mEventListeners.find(event->getEventType());
	if( found != mEventListeners.end() ) {
		const auto & eventListenerList = found->second;
		for( auto listIt = eventListenerList.begin(); listIt != eventListenerList.end(); ++listIt ) {
			auto& listener = (*listIt);
			LOG_EVENT("Sending event " + std::string( event->getName() ) + " to delegate.");
			listener( event );
			processed = true;
		}
	}
	
	return processed;
}
	
bool EventManager::queueEvent( const EventDataRef &event )
{
	CI_ASSERT(mActiveQueue < NUM_QUEUES);
	
	// make sure the event is valid
	if( !event ) {
		CI_LOG_E("Invalid event in queueEvent");
	}
	
//	CI_LOG_V("Attempting to queue event: " + std::string( event->getName() ) );
	
	auto found = mEventListeners.find( event->getEventType() );
	if( found != mEventListeners.end() ) {
		mQueues[mActiveQueue].push_back(event);
		LOG_EVENT("Successfully queued event: " + std::string( event->getName() ) );
		return true;
	}
	else {
		static bool processNotify = false;
		if( !processNotify ) {
			LOG_EVENT( "Skipping event since there are no delegates to receive it: " + std::string( event->getName() ) );
			processNotify = true;
		}
		return false;
	}
}
	
bool EventManager::abortEvent( const EventType &type, bool allOfType )
{
	CI_ASSERT(mActiveQueue >= 0);
	CI_ASSERT(mActiveQueue > NUM_QUEUES);
	
	bool success = false;
	auto found = mEventListeners.find( type );
	
	if( found != mEventListeners.end() ) {
		auto & eventQueue = mQueues[mActiveQueue];
		auto eventIt = eventQueue.begin();
		auto end = eventQueue.end();
		while( eventIt != end ) {
			
			if( (*eventIt)->getEventType() == type ) {
				eventIt = eventQueue.erase(eventIt);
				success = true;
				if( ! allOfType )
					break;
			}
		}
	}
	
	return success;
}
	
bool EventManager::update( uint64_t maxMillis )
{
	uint64_t currMs = app::App::get()->getElapsedSeconds() * 1000;
	uint64_t maxMs = (( maxMillis == EventManager::kINFINITE ) ? (EventManager::kINFINITE) : (currMs + maxMillis) );
	
	int queueToProcess = mActiveQueue;
	mActiveQueue = (mActiveQueue + 1) % NUM_QUEUES;
	mQueues[mActiveQueue].clear();
	
	static bool processNotify = false;
	if( ! processNotify ) {
		LOG_EVENT("Processing Event Queue " + to_string(queueToProcess) + "; " + to_string(mQueues[queueToProcess].size()) + " events to process");
		processNotify = true;
	}
	
	while (!mQueues[queueToProcess].empty()) {
		auto event = mQueues[queueToProcess].front();
		mQueues[queueToProcess].pop_front();
		LOG_EVENT("\t\tProcessing Event " + std::string(event->getName()));
		
		const auto & eventType = event->getEventType();
		
		auto found = mEventListeners.find(eventType);
		if (found != mEventListeners.end()) {
			const auto & eventListeners = found->second;
			LOG_EVENT("\t\tFound " + to_string(eventListeners.size()) + " delegates");

			auto listIt = eventListeners.begin();
			auto end = eventListeners.end();
			while (listIt != end) {
				auto listener = (*listIt);
				LOG_EVENT("\t\tSending Event " + std::string(event->getName()) + " to delegate");
				listener(event);
				listIt++;
			}
		}
		
		currMs = app::App::get()->getElapsedSeconds() * 1000;//Engine::getTickCount();
		if( maxMillis != EventManager::kINFINITE && currMs >= maxMs ) {
			LOG_EVENT("Aborting event processing; time ran out");
			break;
		}
	}
	
	bool queueFlushed = mQueues[queueToProcess].empty();
	if( ! queueFlushed ) {
		while( ! mQueues[queueToProcess].empty() ) {
			auto event = mQueues[queueToProcess].back();
			mQueues[queueToProcess].pop_back();
			mQueues[mActiveQueue].push_front(event);
		}
	}
	
	return queueFlushed;
}
	
}














