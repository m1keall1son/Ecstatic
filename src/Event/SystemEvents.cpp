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
    
    EventType RequestSceneChangeEvent::TYPE = getHash("Request_scene_change_event");
    
    RequestSceneChangeEventRef RequestSceneChangeEvent::create()
    {
        return RequestSceneChangeEventRef( new RequestSceneChangeEvent );
    }
    
    RequestSceneChangeEvent::RequestSceneChangeEvent() : ec::EventData( cinder::app::getElapsedSeconds() ){}
    
    const char* RequestSceneChangeEvent::getName() const
    {
        return "Request_scene_change_event";
    }
    
    EventType RequestSceneChangeEvent::getEventType() const
    {
        return RequestSceneChangeEvent::TYPE;
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
    
    
    //SHUT DOWN  ----------------------------------------------------//
    
    EventType SerializeAllEvent::TYPE = getHash("serialize_all_event");
    
    SerializeAllEventRef SerializeAllEvent::create()
    {
        return SerializeAllEventRef( new SerializeAllEvent );
    }
    
    SerializeAllEvent::SerializeAllEvent() : ec::EventData( cinder::app::getElapsedSeconds() ){}
    
    const char* SerializeAllEvent::getName() const
    {
        return "serialize_all_event";
    }
    
    EventType SerializeAllEvent::getEventType() const
    {
        return SerializeAllEvent::TYPE;
    }
    
    //INIT GUI  ----------------------------------------------------//
    
    EventType InitGUIEvent::TYPE = getHash("init_gui_event");
    
    InitGUIEventRef InitGUIEvent::create(const GUIManagerRef& gui_manager )
    {
        return InitGUIEventRef( new InitGUIEvent( gui_manager ) );
    }
    
    InitGUIEvent::InitGUIEvent(const GUIManagerRef& gui_manager ) : ec::EventData( cinder::app::getElapsedSeconds() ), mManager(gui_manager){}
    
    const char* InitGUIEvent::getName() const
    {
        return "init_gui_event";
    }
    
    EventType InitGUIEvent::getEventType() const
    {
        return InitGUIEvent::TYPE;
    }

    //UNINIT GUI  ----------------------------------------------------//
    
    EventType UninitGUIEvent::TYPE = getHash("uninit_gui_event");
    
    UninitGUIEventRef UninitGUIEvent::create(const std::vector<IdType>& ids )
    {
        return UninitGUIEventRef( new UninitGUIEvent( ids ) );
    }
    
    UninitGUIEvent::UninitGUIEvent(const std::vector<IdType>& ids ) : ec::EventData( cinder::app::getElapsedSeconds() ), mIds(ids){}
    
    const char* UninitGUIEvent::getName() const
    {
        return "uninit_gui_event";
    }
    
    EventType UninitGUIEvent::getEventType() const
    {
        return UninitGUIEvent::TYPE;
    }
    
}