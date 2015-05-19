//
//  EventManagerBase.cpp
//  RendererTest
//
//  Created by Ryan Bartley on 8/17/14.
//
//

#include "EventManagerBase.h"
#include "cinder/Log.h"

namespace ec {
			
EventManagerBase::EventManagerBase( const std::string &name ) : mName(name)
{
}

EventManagerBase::~EventManagerBase()
{
}
	
}