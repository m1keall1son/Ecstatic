//
//  Actor.h
//  System_test
//
//  Created by Mike Allison on 4/29/15.
//
//

#pragma once

#include "cinder/Json.h"
#include "cinder/Log.h"
#include "ComponentBase.h"
#include "Common.h"
#include "Manager.hpp"
#include "BaseEventData.h"
#include "cinder/params/Params.h"

namespace ec {

class Actor {
    
public:
    
    template<class Component>
    inline std::weak_ptr<Component> getComponent();
    
    bool            hasComponent( const ComponentType &type );
    ActorId         getId() const;
    ActorUId        getUId() const;
    ActorNameType   getName() const;
    ActorType       getType() const;
    ActorTypeQualifier  getTypeQualifier() const;
    void            destroy();
    
    void            postInit();
    
    void            initGUI( ec::GUIManager* gui_manager );
//    ci::params::InterfaceGlRef initGUI();
    void            saveActorToFile();
    
    ci::JsonTree    serialize();
    
    inline void activate( bool active ){ mActive = active; }
    inline bool isActive(){ return mActive; }
    
    inline void persistence( bool persistent ){ mPersistent = persistent; }
    inline bool isPersistent(){ return mPersistent; }
    
    ~Actor();
    
private:
    
    Actor( const ActorNameType &name, const ActorType &type, const ActorTypeQualifier &qualifier, bool activate, bool persistent );
    
    std::map< ComponentType, ComponentBaseRef > mComponents;
    ActorNameType                              mName;
    ActorId                                    mId;
    ActorUId                                   mUniqueId;
    bool                                       mActive;
    bool                                       mPersistent;
    ActorType                                  mType;
    ActorTypeQualifier                         mQualifier;
    
    void handleShutDown( EventDataRef );
    
    friend class ActorFactory;
    friend class ActorManager;
    
};
    
template<class Component>
inline std::weak_ptr<Component> Actor::getComponent()
{
    auto found = mComponents.find( Component::TYPE );
    if( found != mComponents.end() ) {
        return std::weak_ptr<Component>( std::dynamic_pointer_cast<Component>(found->second) );
    }
    CI_LOG_E("Component type: "+std::to_string(Component::TYPE)+" not found");
    return std::weak_ptr<Component>();
}
    

}