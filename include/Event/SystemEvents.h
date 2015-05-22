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
    
///COMPONENTS
    
    class UpdateComponentsEvent : public EventData {
    public:
        
        static EventType TYPE;
        
        static UpdateComponentsEventRef create( const TimeStepType &delta );
        
        ~UpdateComponentsEvent(){}
        EventDataRef copy(){ return UpdateComponentsEventRef(); }
        const char* getName() const;
        EventType getEventType() const;
        
        void serialize( ci::Buffer &streamOut ){}
        void deSerialize( const ci::Buffer &streamIn ){}
        
        TimeStepType getTimeStep(){ return mDelta; }
        
    private:
        UpdateComponentsEvent( const TimeStepType &delta );
        TimeStepType mDelta;
    };

    class CullVisibleComponentsEvent : public EventData {
    public:
        
        static EventType TYPE;
        
        static CullVisibleComponentsEventRef create( const TimeStepType &delta );
        
        ~CullVisibleComponentsEvent(){}
        EventDataRef copy(){ return CullVisibleComponentsEventRef(); }
        const char* getName() const;
        EventType getEventType() const;
        
        void serialize( ci::Buffer &streamOut ){}
        void deSerialize( const ci::Buffer &streamIn ){}
        
        TimeStepType getTimeStep(){ return mDelta; }
        
    private:
        CullVisibleComponentsEvent( const TimeStepType &delta );
        TimeStepType mDelta;
    };
    
    class DrawVisibleComponentsEvent : public EventData {
    public:
        
        static EventType TYPE;
        
        static DrawVisibleComponentsEventRef create( const TimeStepType &delta );
        
        ~DrawVisibleComponentsEvent(){}
        EventDataRef copy(){ return DrawVisibleComponentsEventRef(); }
        const char* getName() const;
        EventType getEventType() const;
        
        void serialize( ci::Buffer &streamOut ){}
        void deSerialize( const ci::Buffer &streamIn ){}
        
        TimeStepType getTimeStep(){ return mDelta; }
        
    private:
        DrawVisibleComponentsEvent( const TimeStepType &delta );
        TimeStepType mDelta;
    };
    
}