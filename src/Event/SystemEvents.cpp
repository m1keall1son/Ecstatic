//
//  SystemEvents.cpp
//  System_test
//
//  Created by Mike Allison on 5/5/15.
//
//

#include "SystemEvents.h"
#include "Scene.h"

namespace ec {
    
///ACTOR ----------------------------------------------------------------//
    
    //ACTOR DESTROY  ----------------------------------------------------//
    
    EventType DestoryActorEvent::TYPE = getHash("destroy_actor_event");
    
    DestoryActorEventRef DestoryActorEvent::create( const ActorUId &actor )
    {
        return DestoryActorEventRef( new DestoryActorEvent( actor ) );
    }
    
    DestoryActorEvent::DestoryActorEvent( const ActorUId &actor   ) : ec::EventData( cinder::app::getElapsedSeconds() ), mUId( actor ){}
    
    const char* DestoryActorEvent::getName() const
    {
        return "destory_actor_event";
    }
    
    EventType DestoryActorEvent::getEventType() const
    {
        return DestoryActorEvent::TYPE;
    }
    
    //ACTOR CREATE  ----------------------------------------------------//
    
    EventType CreateActorEvent::TYPE = getHash("create_actor_event");
    
    CreateActorEventRef CreateActorEvent::create( const std::string &scene, const std::string &actor  )
    {
        return CreateActorEventRef( new CreateActorEvent( scene, actor ) );
    }
    
    CreateActorEvent::CreateActorEvent( const std::string &scene, const std::string &actor   ) : ec::EventData( cinder::app::getElapsedSeconds() ), mReferenceName( actor ), mReferenceScene(scene){}
    
    const char* CreateActorEvent::getName() const
    {
        return "create_actor_event";
    }
    
    EventType CreateActorEvent::getEventType() const
    {
        return CreateActorEvent::TYPE;
    }
    
    //RETURN ACTOR  ----------------------------------------------------//
    
    EventType ReturnActorCreatedEvent::TYPE = getHash("return_actor_created_event");
    
    ReturnActorCreatedEventRef ReturnActorCreatedEvent::create( const SceneId &scene_id, const ActorWeakRef &actor )
    {
        return ReturnActorCreatedEventRef( new ReturnActorCreatedEvent( scene_id, actor ) );
    }
    
    ReturnActorCreatedEvent::ReturnActorCreatedEvent( const SceneId &scene_id, const ActorWeakRef &actor ) : ec::EventData( cinder::app::getElapsedSeconds() ), mWeakActor( actor ), mSceneId(scene_id){}
    
    const char* ReturnActorCreatedEvent::getName() const
    {
        return "return_actor_created_event";
    }
    
    EventType ReturnActorCreatedEvent::getEventType() const
    {
        return ReturnActorCreatedEvent::TYPE;
    }
    
///SCENE ----------------------------------------------------------------//
    
    //SCENE UPDATE  ----------------------------------------------------//
    
    EventType SceneUpdateEvent::TYPE = getHash("scene_update_event");
    
    SceneUpdateEventRef SceneUpdateEvent::create( const TimeStepType &delta )
    {
        return SceneUpdateEventRef( new SceneUpdateEvent( delta ) );
    }
    
    SceneUpdateEvent::SceneUpdateEvent( const TimeStepType &delta   ) : ec::EventData( cinder::app::getElapsedSeconds() ), mDelta( delta ){}
    
    const char* SceneUpdateEvent::getName() const
    {
        return "scene_update_event";
    }
    
    EventType SceneUpdateEvent::getEventType() const
    {
        return SceneUpdateEvent::TYPE;
    }
    
    //SCENE DRAW  ----------------------------------------------------//
    
    EventType SceneDrawEvent::TYPE = getHash("scene_draw_event");
    
    SceneDrawEventRef SceneDrawEvent::create( const TimeStepType &delta )
    {
        return SceneDrawEventRef( new SceneDrawEvent( delta ) );
    }
    
    SceneDrawEvent::SceneDrawEvent( const TimeStepType &delta   ) : ec::EventData( cinder::app::getElapsedSeconds() ), mDelta( delta ){}
    
    const char* SceneDrawEvent::getName() const
    {
        return "scene_draw_event";
    }
    
    EventType SceneDrawEvent::getEventType() const
    {
        return SceneDrawEvent::TYPE;
    }
    
    //SCENE PREDRAW  ----------------------------------------------------//

    EventType ScenePreDrawEvent::TYPE = getHash("scene_predraw_event");
    
    ScenePreDrawEventRef ScenePreDrawEvent::create( const TimeStepType &delta )
    {
        return ScenePreDrawEventRef( new ScenePreDrawEvent( delta ) );
    }
    
    ScenePreDrawEvent::ScenePreDrawEvent( const TimeStepType &delta   ) : ec::EventData( cinder::app::getElapsedSeconds() ), mDelta( delta ){}
    
    const char* ScenePreDrawEvent::getName() const
    {
        return "scene_predraw_event";
    }
    
    EventType ScenePreDrawEvent::getEventType() const
    {
        return ScenePreDrawEvent::TYPE;
    }
    
    //SCENE CHANGE  ----------------------------------------------------//
    
    EventType SceneChangeEvent::TYPE = getHash("scene_change_event");
    
    SceneChangeEventRef SceneChangeEvent::create()
    {
        return SceneChangeEventRef( new SceneChangeEvent );
    }
    
    SceneChangeEvent::SceneChangeEvent() : ec::EventData( cinder::app::getElapsedSeconds() ){}
    
    const char* SceneChangeEvent::getName() const
    {
        return "scene_change_event";
    }
    
    EventType SceneChangeEvent::getEventType() const
    {
        return SceneChangeEvent::TYPE;
    }
    
    //SHUT DOWN  ----------------------------------------------------//
    
    EventType ShutDownEvent::TYPE = getHash("shut_down_event");
    
    ShutDownEventRef ShutDownEvent::create()
    {
        return ShutDownEventRef( new ShutDownEvent );
    }
    
    ShutDownEvent::ShutDownEvent() : ec::EventData( cinder::app::getElapsedSeconds() ){}
    
    const char* ShutDownEvent::getName() const
    {
        return "shutdown_event";
    }
    
    EventType ShutDownEvent::getEventType() const
    {
        return ShutDownEvent::TYPE;
    }
    
}