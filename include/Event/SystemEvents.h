//
//  SystemEvents.h
//  System_test
//
//  Created by Mike Allison on 5/5/15.
//
//

#pragma once

#include "Common.h"
#include "BaseEventData.h"

namespace ec {

///ACTOR
    
class DestoryActorEvent : public EventData {
public:
    
    static EventType TYPE;
    
    static DestoryActorEventRef create( const ActorUId & actor );
    
    ~DestoryActorEvent(){}
    EventDataRef copy(){ return DestoryActorEventRef(); }
    const char* getName() const;
    EventType getEventType() const;
    
    void serialize( ci::Buffer &streamOut ){}
    void deSerialize( const ci::Buffer &streamIn ){}
    
    inline ActorUId getActorUId(){ return mUId; }
    
private:
    DestoryActorEvent( const ActorUId & actor );
    ActorUId  mUId;
    
};

class CreateActorEvent : public EventData {
public:
    
    static EventType TYPE;
    
    static CreateActorEventRef create( const std::string &scene, const std::string &actor  );
    
    ~CreateActorEvent(){}
    EventDataRef copy(){ return CreateActorEventRef(); }
    const char* getName() const;
    EventType getEventType() const;
    
    void serialize( ci::Buffer &streamOut ){}
    void deSerialize( const ci::Buffer &streamIn ){}
    
    inline std::string& getReferenceName(){ return mReferenceName; }
    inline std::string& getReferenceScene(){ return mReferenceScene; }

private:
    CreateActorEvent( const std::string &scene, const std::string &actor  );
    std::string mReferenceName;
    std::string mReferenceScene;

};


class ReturnActorCreatedEvent : public EventData {
public:
    
    static EventType TYPE;
    
    static ReturnActorCreatedEventRef create( const SceneId &scene_id, const ActorWeakRef &actor );
    
    ~ReturnActorCreatedEvent(){}
    EventDataRef copy(){ return ReturnActorCreatedEventRef(); }
    const char* getName() const;
    EventType getEventType() const;
    
    void serialize( ci::Buffer &streamOut ){}
    void deSerialize( const ci::Buffer &streamIn ){}
    
    inline ActorWeakRef getActorWeakRef(){ return mWeakActor; }
    inline SceneId getSceneId() { return mSceneId; }
    
private:
    ReturnActorCreatedEvent( const SceneId &scene_id, const ActorWeakRef &actor );
    ActorWeakRef mWeakActor;
    SceneId mSceneId;
};

    
///SCENE
    
    class ScenePreDrawEvent : public EventData {
    public:
        
        static EventType TYPE;
        
        static ScenePreDrawEventRef create( const TimeStepType &delta );
        
        ~ScenePreDrawEvent(){}
        EventDataRef copy(){ return ScenePreDrawEventRef(); }
        const char* getName() const;
        EventType getEventType() const;
        
        void serialize( ci::Buffer &streamOut ){}
        void deSerialize( const ci::Buffer &streamIn ){}
        
        TimeStepType getTimeStep(){ return mDelta; }
        
    private:
        ScenePreDrawEvent( const TimeStepType &delta );
        TimeStepType mDelta;
    };
    
    class SceneDrawEvent : public EventData {
    public:
        
        static EventType TYPE;
        
        static SceneDrawEventRef create( const TimeStepType &delta );
        
        ~SceneDrawEvent(){}
        EventDataRef copy(){ return SceneDrawEventRef(); }
        const char* getName() const;
        EventType getEventType() const;
        
        void serialize( ci::Buffer &streamOut ){}
        void deSerialize( const ci::Buffer &streamIn ){}
        
        TimeStepType getTimeStep(){ return mDelta; }
        
    private:
        SceneDrawEvent( const TimeStepType &delta );
        TimeStepType mDelta;
    };
    
    class SceneUpdateEvent : public EventData {
    public:
        
        static EventType TYPE;
        
        static SceneUpdateEventRef create( const TimeStepType &delta );
        
        ~SceneUpdateEvent(){}
        EventDataRef copy(){ return SceneUpdateEventRef(); }
        const char* getName() const;
        EventType getEventType() const;
        
        void serialize( ci::Buffer &streamOut ){}
        void deSerialize( const ci::Buffer &streamIn ){}
        
        TimeStepType getTimeStep(){ return mDelta; }
        
    private:
        SceneUpdateEvent( const TimeStepType &delta );
        TimeStepType mDelta;
    };
    
    class SceneChangeEvent : public EventData {
    public:
        
        static EventType TYPE;
        
        static SceneChangeEventRef create();
        
        ~SceneChangeEvent(){}
        EventDataRef copy(){ return SceneChangeEventRef(); }
        const char* getName() const;
        EventType getEventType() const;
        
        void serialize( ci::Buffer &streamOut ){}
        void deSerialize( const ci::Buffer &streamIn ){}
        
    private:
        SceneChangeEvent();
    };
    
//-----------------------------------------------
    class ShutDownEvent : public EventData {
    public:
        
        static EventType TYPE;
        
        static ShutDownEventRef create();
        
        ~ShutDownEvent(){}
        EventDataRef copy(){ return ShutDownEventRef(); }
        const char* getName() const;
        EventType getEventType() const;
        
        void serialize( ci::Buffer &streamOut ){}
        void deSerialize( const ci::Buffer &streamIn ){}
        
    private:
        ShutDownEvent();
    };
    
    //-----------------------------------------------
    class SerializeAllEvent : public EventData {
    public:
        
        static EventType TYPE;
        
        static SerializeAllEventRef create();
        
        ~SerializeAllEvent(){}
        EventDataRef copy(){ return SerializeAllEventRef(); }
        const char* getName() const;
        EventType getEventType() const;
        
        void serialize( ci::Buffer &streamOut ){}
        void deSerialize( const ci::Buffer &streamIn ){}
        
    private:
        SerializeAllEvent();
    };

    
    //-----------------------------------------------
    class InitGUIEvent : public EventData {
    public:
        
        static EventType TYPE;
        
        static InitGUIEventRef create( const GUIManagerRef& gui_manager );
        
        ~InitGUIEvent(){}
        EventDataRef copy(){ return InitGUIEventRef(); }
        const char* getName() const;
        EventType getEventType() const;
        
        void serialize( ci::Buffer &streamOut ){}
        void deSerialize( const ci::Buffer &streamIn ){}
        
        inline GUIManagerRef getGUIManager(){ return mManager; }
        
    private:
        InitGUIEvent(const GUIManagerRef& gui_manager );
        GUIManagerRef mManager;
    };
    
    //-----------------------------------------------
    class UninitGUIEvent : public EventData {
    public:
        
        static EventType TYPE;
        
        static UninitGUIEventRef create( const std::vector<IdType>& ids_to_remove );
        
        ~UninitGUIEvent(){}
        EventDataRef copy(){ return UninitGUIEventRef(); }
        const char* getName() const;
        EventType getEventType() const;
        
        void serialize( ci::Buffer &streamOut ){}
        void deSerialize( const ci::Buffer &streamIn ){}
        
        inline std::vector<IdType>& getIds(){ return mIds; }
        
    private:
        UninitGUIEvent( const std::vector<IdType>& ids_to_remove );
        std::vector<IdType> mIds;
    };
    
}