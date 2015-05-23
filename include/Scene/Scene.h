//
//  Scene.h
//  System_test
//
//  Created by Mike Allison on 5/3/15.
//
//

#pragma once
#include "Common.h"
#include "EventManager.h"
#include "cinder/Json.h"

namespace ec {
    
class Scene {
    
public:
        
    inline EventManagerRef manager(){ return mSceneManager; }
    
    inline const std::string& getName(){ return mName; }
    
    inline const SceneId            getId()const{ return mId; }
    inline SceneId                  getId(){ return mId; }
    
    virtual ~Scene();
    
protected:
    
    
    Scene( const std::string& name );
    
    virtual void                    initialize( const std::vector<ActorUId>& persistent_actors = std::vector<ActorUId>(0) );
    virtual std::vector<ActorUId>   shutdown();
    

    virtual void                    initialize( const ci::JsonTree &init ) = 0;

    virtual void                    update(); //has to update the event manager
    virtual void                    preDraw() = 0;
    virtual void                    draw() = 0;
    virtual void                    postDraw() = 0;
    
    ActorWeakRef                    getActor( const ActorUId& _id );
    virtual void                    handleReturnActorCreate( EventDataRef );
    virtual void                    handleSceneUpdate( EventDataRef );
    virtual void                    handleScenePreDraw( EventDataRef ); //culling
    virtual void                    handleSceneDraw( EventDataRef );
    
    std::string                                 mName;
    std::map<ActorUId, ActorWeakRef>            mActors;
    EventManagerRef                             mSceneManager;
    SceneId                                     mId;
    
    friend class                     Controller;
};
    
    
}

