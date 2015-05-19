//
//  EventDataBase.h
//  RendererTest
//
//  Created by Ryan Bartley on 8/16/14.
//
//

#pragma once

#include <strstream>
#include <memory>

#include "cinder/Buffer.h"
#include "Common.h"

namespace ec {
	
class EventData {
public:
	explicit EventData( float timestamp = 0.0f ) : mTimeStamp( timestamp ), mIsHandled( false ) {}
	virtual ~EventData() {}

    virtual EventDataRef copy() = 0;
	virtual const char* getName() const = 0;
	virtual EventType getEventType() const = 0;
	float getTimeStamp() { return mTimeStamp; }
	
	bool isHandled() { return mIsHandled; }
	void setIsHandled( bool handled = true ) { mIsHandled = handled; }
	
	// TODO: This is probably stupid, need to figure out what I actually want.
	virtual void serialize( ci::Buffer &streamOut ) = 0;
	virtual void deSerialize( const ci::Buffer &streamIn ) = 0;

	
private:
	const float mTimeStamp;
	bool		mIsHandled;
};

	
}