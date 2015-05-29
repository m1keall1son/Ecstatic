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
    
    ///TODO: whats up with my two initialize functions?  find a better way to carry over persistent actors, in an event probably
    
    virtual void                    initialize( const std::vector<ActorUId>& persistent_actors = std::vector<ActorUId>(0) );
    virtual std::vector<ActorUId>   shutdown();

    virtual void                    initialize( const ci::JsonTree &init ) = 0;
    virtual void                    postInit() = 0;
    
    virtual void                    update(); //has to update the event manager
    virtual void                    preDraw() = 0;
    virtual void                    draw() = 0;
    virtual void                    postDraw() = 0;
    virtual void                    initGUI( const GUIManagerRef& gui_manager ) = 0;
    
    ActorWeakRef                    getActor( const ActorUId& _id );
    virtual void                    handleReturnActorCreate( EventDataRef );
    virtual void                    handleSceneUpdate( EventDataRef );
    virtual void                    handleScenePreDraw( EventDataRef ); //culling
    virtual void                    handleSceneDraw( EventDataRef );
    virtual void                    handleInitGUI( EventDataRef );

    
    std::string                                 mName;
    std::map<ActorUId, ActorWeakRef>            mActors;
    EventManagerRef                             mSceneManager;
    SceneId                                     mId;
    
private:
    
    void handleShutDown( EventDataRef );
    bool mShuttingDown;
    
    friend class                     Controller;
};
    
    
}

