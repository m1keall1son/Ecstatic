//
//  ActorManager.h
//  System_test
//
//  Created by Mike Allison on 5/3/15.
//
//

#pragma once
#include "Common.h"

namespace ec {

class ActorManager {
public:
    
    static ActorManagerRef get();
    
    bool actorExists( const ActorUId &_uid );
    
    ActorId retrieveIdForUnique( const ActorUId &_uid );
    
    ActorWeakRef retreiveUnique( const ActorUId &_uid );
    
    std::vector<ActorWeakRef> retreiveActorsById( const ActorId &_id );
    
    int getNumActorsForId( const ActorId &_id );
    
    void handleDestroyActor( EventDataRef );
    
    void handleCreateActor( EventDataRef );
    
    void restart();
    
    ~ActorManager();
    
private:
    
    ActorManager();
    std::map< ActorUId, ActorRef > mActors;
    bool    mShuttingDown;
    void handleShutDown(EventDataRef);
    
};

}