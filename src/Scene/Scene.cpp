//
//  Scene.cpp
//  System_test
//
//  Created by Mike Allison on 5/3/15.
//
//

#include "Scene.h"
#include "ConfigManager.h"
#include "cinder/Log.h"
#include "EventManager.h"
#include "Actor.h"
#include "SystemEvents.h"
#include "Controller.h"
#include "ActorManager.h"

namespace ec {
    
    Scene::~Scene()
    {
        if(!mShuttingDown){

        }
    }

    Scene::Scene( const std::string& name ):mName(name), mId( getHash(name) ), mShuttingDown(false)
    {
    }
    
    void Scene::handleShutDown(EventDataRef)
    {
        mShuttingDown = true;
        //mSceneManager->clear();
    }

    void Scene::initialize( const std::vector<ActorUId>& persistent_actors )
    {
        mSceneManager = EventManager::create("Scene "+mName+" Manager");
        Controller::get()->eventManager()->addListener(fastdelegate::MakeDelegate(this, &Scene::handleInitGUI), InitGUIEvent::TYPE);
        Controller::get()->eventManager()->addListener( fastdelegate::MakeDelegate(this, &Scene::handleSceneUpdate), SceneUpdateEvent::TYPE );
        Controller::get()->eventManager()->addListener( fastdelegate::MakeDelegate(this, &Scene::handleReturnActorCreate), ReturnActorCreatedEvent::TYPE );
        Controller::get()->eventManager()->addListener( fastdelegate::MakeDelegate(this, &Scene::handleScenePreDraw), ScenePreDrawEvent::TYPE );
        Controller::get()->eventManager()->addListener( fastdelegate::MakeDelegate(this, &Scene::handleSceneDraw), SceneDrawEvent::TYPE );
        Controller::get()->eventManager()->addListener( fastdelegate::MakeDelegate(this, &Scene::handleShutDown), ShutDownEvent::TYPE );
        
        if( !persistent_actors.empty() ){
            for(auto &id : persistent_actors)
            {
                auto actor_weak = ActorManager::get()->retreiveUnique(id);
                mActors.insert( std::make_pair(id, actor_weak) );
            }
        }
        
        auto init = ConfigManager::get()->retreiveActorsForScene( mName );
        
        ///call to inherited initialize for sub classes to pulll custom shit out of the config
        initialize( ConfigManager::get()->retreiveScene(mName) );
        
        try {
            
            //TODO: the problem with persistent actors is how to manage state across scenes, how to identify actors of the same type across scenes that are persistent, one solution is destroy all and reload referencing a serialized state file that is written out and read back in or something
            //for now, just sending across actors marked 'persistent' and not including them in the config for the next scene, the state has to be handled at runtime then
            
            auto & actors = init.getChildren();
            
            auto it = actors.begin();
            auto end = actors.end();
            for(;it!=end;++it){
                auto actor_name = it->getValueForKey("name");
                CI_LOG_V("found actor: "+actor_name);

                auto onInit = it->getValueForKey<bool>( "create_on_scene_init" );
                
                if( onInit ){
                    CI_LOG_V("creating actor: "+actor_name);
                    Controller::get()->eventManager()->triggerEvent( CreateActorEvent::create( mName, actor_name) );
                }
                
            }
            
        } catch (const ci::JsonTree::ExcChildNotFound &e) {
            CI_LOG_E("actors not found in init");
        }
        
      
        ///POST INITIALIZE ALL ACTORS
        auto actor = mActors.begin();
        auto end = mActors.end();
        
        while( actor != end )
        {
            if(auto a = (*actor).second.lock()){
                a->postInit();
                ++actor;
            }else{
                CI_LOG_E("Actor is missing");
                ec::Controller::get()->eventManager()->triggerEvent(DestoryActorEvent::create((*actor).first));
                actor = mActors.erase(actor);
            }
        }
        
        postInit();
        
        ///run setup events;
        manager()->update();
        
    }
    
    std::vector<ActorUId> Scene::shutdown()
    {
        
        Controller::get()->eventManager()->removeListener( fastdelegate::MakeDelegate(this, &Scene::handleSceneUpdate), SceneUpdateEvent::TYPE );
        Controller::get()->eventManager()->removeListener( fastdelegate::MakeDelegate(this, &Scene::handleReturnActorCreate), ReturnActorCreatedEvent::TYPE );
        Controller::get()->eventManager()->removeListener( fastdelegate::MakeDelegate(this, &Scene::handleScenePreDraw), ScenePreDrawEvent::TYPE );
        Controller::get()->eventManager()->removeListener( fastdelegate::MakeDelegate(this, &Scene::handleSceneDraw), SceneDrawEvent::TYPE );
        Controller::get()->eventManager()->removeListener( fastdelegate::MakeDelegate(this, &Scene::handleShutDown), ShutDownEvent::TYPE );
        Controller::get()->eventManager()->removeListener(fastdelegate::MakeDelegate(this, &Scene::handleInitGUI), InitGUIEvent::TYPE);
        
        CI_LOG_V("shutting down scene...");
        std::vector<ActorUId> persistent_actors;
        std::vector<ActorUId> uninit_gui;
        for( auto & a : mActors)
        {
            uninit_gui.push_back(a.first);
            
            if( auto actor = a.second.lock() )
            {
                if(actor->isPersistent())
                    persistent_actors.push_back(a.first);
                else
                    ec::Controller::get()->eventManager()->triggerEvent(DestoryActorEvent::create(a.first));

            }
        }
        
        Controller::get()->eventManager()->triggerEvent(UninitGUIEvent::create(uninit_gui));
        
        CI_LOG_V("returning "+std::to_string(persistent_actors.size())+" persistent actors");
        mActors.clear();
        mSceneManager->clear();
        return persistent_actors;
    }
    
    void Scene::handleReturnActorCreate( EventDataRef event )
    {
        auto e = std::dynamic_pointer_cast<ReturnActorCreatedEvent>(event);
        auto actorWeak = e->getActorWeakRef();
        if ( auto actorStrong = actorWeak.lock() ) {
            CI_LOG_V("receieved actor create info: "+ actorStrong->getName());
            mActors.insert( std::make_pair(actorStrong->getUId(), actorWeak) );
        }else{
            CI_LOG_V("receieved actor create info: FAILED TO CREATE ACTOR");
        }
    }
    
    //TODO: figure out thie control logic for the main loop
    
    void Scene::handleSceneUpdate( EventDataRef event)
    {
        update();
        auto e = std::dynamic_pointer_cast<SceneUpdateEvent>(event);
    }
    
    void Scene::handleSceneDraw(EventDataRef event)
    {
        auto e = std::dynamic_pointer_cast<SceneDrawEvent>(event);
        draw();
        postDraw();
    }
    
    void Scene::handleScenePreDraw(EventDataRef event)
    {
        auto e = std::dynamic_pointer_cast<ScenePreDrawEvent>(event);
        preDraw();
    }
    
    void Scene::handleInitGUI(EventDataRef event)
    {
        auto e = std::dynamic_pointer_cast<InitGUIEvent>(event);
        initGUI(e->getGUIManager());
    }
    
    void Scene::update()
    {
        CI_LOG_V("base scene updating...");
        mSceneManager->update();
        CI_LOG_V("base scene updated");
    }
    
    ActorWeakRef Scene::getActor( const ActorUId& _id )
    {
        auto found = mActors.find(_id);
        ActorWeakRef ret;
        if( found != mActors.end() ){
            ret = found->second;
        }
        return ret;
    }
    
}
