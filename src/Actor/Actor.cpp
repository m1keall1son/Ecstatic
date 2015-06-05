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
#include "GUIManager.h"

namespace ec {
        
    Actor::Actor( const ActorNameType &name, const ActorType &type, const ActorTypeQualifier &qualifier,  bool activate, bool persistence ): mName(name), mId( getHash(name) ), mActive(activate), mPersistent(persistence), mType(type), mQualifier(qualifier){
        //long int t = static_cast<long int>(time(nullptr));
        mUniqueId = getHash(name);
    }
    
    Actor::~Actor()
    {
        mComponents.clear();
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
    
    ci::JsonTree Actor::serialize()
    {
        auto actor = ci::JsonTree();
        actor.addChild( ci::JsonTree( "name", mName ) );
        actor.addChild( ci::JsonTree( "id", mId ) );
        actor.addChild( ci::JsonTree( "type", mType ) );
        actor.addChild( ci::JsonTree( "type_qualifier", mQualifier ) );
        ///TODO: fix this hard code
        actor.addChild( ci::JsonTree( "create_on_scene_init", true ) );
        actor.addChild( ci::JsonTree( "persistent", isPersistent() ) );
        actor.addChild( ci::JsonTree( "active", isActive() ) );

        auto components = ci::JsonTree::makeArray( "components" );
        auto it = mComponents.begin();
        auto end = mComponents.end();
        for(; it != end; ++it ){
            auto component = it->second->serialize();
            components.addChild(component);
        }
        actor.addChild(components);
        
        return actor;
        
    }
    
    
    void Actor::saveActorToFile()
    {
        
        auto actor = serialize();
        std::vector<std::string> allowed_extensions( 1, "json" );
        auto save_path = ci::app::getSaveFilePath( ci::app::getAssetDirectories()[0], allowed_extensions );
        if(save_path != "")
            actor.write( save_path, ci::JsonTree::WriteOptions().indented() );
        
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
    
    void Actor::postInit()
    {
        auto it = mComponents.begin();
        auto end = mComponents.end();
        while(it != end ){
            it->second->postInit();
            ++it;
        }
    }
    
//    ci::params::InterfaceGlRef Actor::initGUI()
//    {
//        auto params = ci::params::InterfaceGl::create( getName(), ci::vec2(200,400));
//        params->hide();
//        auto saveFn = std::bind( &Actor::saveActorToFile, this );
//        for( auto& component : mComponents ){
//            component.second->loadGUI(params);
//        }
//        params->addButton("Save Actor", saveFn);
//        
//        return params;
//    }
    
    void Actor::initGUI(ec::GUIManager *gui_manager)
    {
        auto gui = gui_manager->getMainGui();
        gui->addSeparator();
        gui->addText("Actor: "+getName());
        auto saveFn = std::bind( &Actor::saveActorToFile, this );
        for( auto& component : mComponents ){
            component.second->loadGUI( gui );
        }
        gui->addButton("Save Actor", saveFn);
        
    }
    
}