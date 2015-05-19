//
//  Actor.cpp
//  System_test
//
//  Created by Mike Allison on 4/29/15.
//
//

#include "Actor.h"
#include "cinder/Log.h"
#include "EventManager.h"
#include "Controller.h"
#include "ActorFactory.h"
#include "ConfigManager.h"
#include "SystemEvents.h"

namespace ec {
        
    Actor::Actor( const ActorNameType &name, const ActorType &type, const ActorTypeQualifier &qualifier,  bool activate, bool persistence ): mName(name), mId( getHash(name) ), mActive(activate), mPersistent(persistence), mType(type), mQualifier(qualifier){
        long int t = static_cast<long int>(time(nullptr));
        mUniqueId = getHash(name+std::to_string(t));
    }
    
    ActorId Actor::getId() const
    {
        return mId;
    }

    ActorId Actor::getUId() const
    {
        return mUniqueId;
    }
    
    ActorNameType Actor::getName() const
    {
        return mName;
    }
    
    ActorType Actor::getType() const
    {
        return mType;
    }
    ActorTypeQualifier Actor::getTypeQualifier() const
    {
        return mQualifier;
    }
    void Actor::destroy()
    {
        mComponents.clear();
        mActive = false;
        //tell manager to remove this actor
        Controller::get()->eventManager()->queueEvent( DestoryActorEvent::create(mUniqueId) );
    }
    
    bool Actor::hasComponent( const ComponentType &type )
    {
        auto it = mComponents.begin();
        auto end = mComponents.end();
        for(; it != end; ++it ){
            if( it->second->getType() == type ){
                return true;
            }
        }
        return false;
    }
    
    
}