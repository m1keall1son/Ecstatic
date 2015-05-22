//
//  ActorManager.cpp
//  System_test
//
//  Created by Mike Allison on 5/3/15.
//
//

#include "ActorManager.h"
#include "EventManager.h"
#include "Actor.h"
#include "ConfigManager.h"
#include "ActorFactory.h"
#include "Controller.h"
#include "Scene.h"
#include "SystemEvents.h"

namespace ec {
    
static ActorManagerRef sActorManager = nullptr;
    
ActorManager::ActorManager(){
    CI_LOG_V("Actor manager initializing...");
    Controller::get()->eventManager()->addListener( fastdelegate::MakeDelegate( this, &ActorManager::handleDestroyActor ), DestoryActorEvent::TYPE );
    Controller::get()->eventManager()->addListener( fastdelegate::MakeDelegate( this, &ActorManager::handleCreateActor ), CreateActorEvent::TYPE );
    
}

ActorManager::~ActorManager()
{
    Controller::get()->eventManager()->removeListener( fastdelegate::MakeDelegate( this, &ActorManager::handleDestroyActor ), DestoryActorEvent::TYPE );
    Controller::get()->eventManager()->removeListener( fastdelegate::MakeDelegate( this, &ActorManager::handleCreateActor ), CreateActorEvent::TYPE );
}

ActorManagerRef ActorManager::get()
{
    if(!sActorManager){
        sActorManager = ActorManagerRef( new ActorManager );
    }
    return sActorManager;
}

void ActorManager::handleDestroyActor(EventDataRef event)
{
    CI_LOG_V("Actor manager received destroy actor event");
    auto e = std::dynamic_pointer_cast<DestoryActorEvent>(event);
    CI_LOG_V( "Erasing actor: "+ std::to_string( e->getActorUId() ) + " from actor manager" );
    mActors.erase( e->getActorUId() );
}

void ActorManager::handleCreateActor(EventDataRef event)
{
    CI_LOG_V("Actor manager received create actor event");
    auto e = std::dynamic_pointer_cast<CreateActorEvent>(event);
    CI_LOG_V( "Create actor: "+ e->getReferenceName() );
    auto init  = ConfigManager::get()->retreiveActorConfig( e->getReferenceScene(), e->getReferenceName() );
    auto actor = ActorFactory::get()->createActor( init );
    mActors.insert( std::make_pair(actor->getUId(), actor) );
    auto scene_id = Controller::get()->scene().lock()->getId();
    Controller::get()->eventManager()->triggerEvent( ReturnActorCreatedEvent::create( scene_id, actor) );
}
    
    
bool ActorManager::actorExists( const ActorUId &_uid )
{
    return mActors.count(_uid);
}

ActorId ActorManager::retrieveIdForUnique( const ActorUId &_uid )
{
    auto it = mActors.find(_uid);
    if( it != mActors.end() ){
        return it->second->mId;
    }else{
        return 0;
    }
}

ActorWeakRef ActorManager::retreiveUnique( const ActorUId &_uid )
{
    auto it = mActors.find(_uid);
    if( it != mActors.end() ){
        return  it->second;
    }else{
        return ActorWeakRef();
    }
}

std::vector<ActorWeakRef> ActorManager::retreiveActorsById( const ActorId &_id ){
 
    std::vector<ActorWeakRef> ret;
    auto it = mActors.begin();
    auto end = mActors.end();
    while( it != end ){
        if( it->second->mId == _id ){
            ret.push_back( it->second );
        }
        ++it;
    }
    return ret;
}

int ActorManager::getNumActorsForId( const ActorId &_id )
{
    int count;
    auto it = mActors.begin();
    auto end = mActors.end();
    while( it != end ){
        if( it->second->mId == _id ){
            count++;
        }
        ++it;
    }
    return count;
    
}

}