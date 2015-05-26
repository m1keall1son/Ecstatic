//
//  Controller.cpp
//  System_test
//
//  Created by Mike Allison on 5/5/15.
//
//

#include "Controller.h"
#include "Cinder/Log.h"
#include "ConfigManager.h"
#include "Scene.h"
#include "SystemEvents.h"
#include "SceneFactory.h"
#include "ActorManager.h"
#include "GUIManager.h"
#include "SystemEvents.h"

namespace ec {
    
    static ControllerRef sController = nullptr;
    
    ControllerRef Controller::create( const SceneFactoryRef& scene_factory,const ComponentFactoryRef& component_factory )
    {
        sController = ControllerRef( new Controller( scene_factory, component_factory) );
        return sController;
    }
    
    Controller::~Controller()
    {
        CI_LOG_V("controller destructor");
        mScenes.clear();
        mEventManager->clear();
    }
    
    ControllerRef Controller::get()
    {
        CI_ASSERT(sController);
        return sController;
    }
    
    Controller::Controller( const SceneFactoryRef& scene_factory, const ComponentFactoryRef& component_factory ) : mSceneIndex(0), mCurrentScene(nullptr), mConfigManager(nullptr), mSceneFactory(scene_factory), mComponentFactory(component_factory), mDebug(false)
    {
        CI_LOG_V("controller constructing...");
        mEventManager = EventManager::create("global event manager");
        mGuiManager = GUIManager::create();
        mGuiManager->enableGUI(false);
        mEventManager->addListener(fastdelegate::MakeDelegate(mGuiManager.get(), &GUIManager::handleUninit), UninitGUIEvent::TYPE);
    }
    
    void Controller::initialize(const ci::JsonTree &configuration)
    {
        CI_LOG_V("controller initializing...");
        ActorManager::get();
        mConfigManager = ConfigManager::create( configuration );
        try {
            
            auto scenes = configuration["scenes"];
            for( auto & scene : scenes){
                mScenes.push_back( mSceneFactory->createScene(scene) );
            }
            
        } catch (const ci::JsonTree::ExcChildNotFound &e) {
            CI_LOG_E( e.what() );
        }
        mCurrentScene = (*mScenes.begin());
        CI_LOG_V("controller initialized");
        CI_LOG_V("controller initializing scene: "+ mCurrentScene->getName() +"...");
        mCurrentScene->initialize();
        CI_LOG_V("controller scene: "+ mCurrentScene->getName() +" initialized");
        CI_LOG_V("Initialize scen GUIs");
        mGuiManager->postInit();
    }
    
    void Controller::nextScene()
    {
        CI_LOG_V("request next scene");
        auto persisten_actors = mCurrentScene->shutdown();
        auto next = mScenes[mSceneIndex++];
        next->initialize( persisten_actors );
        mCurrentScene = next;
    }
    
    void Controller::update()
    {
        CI_LOG_V("update queued");
        mEventManager->queueEvent( SceneUpdateEvent::create( getFrameTimeStep() ) );
    }
    
    void Controller::draw()
    {
        CI_LOG_V("predraw queued");
        mEventManager->queueEvent( ScenePreDrawEvent::create( getFrameTimeStep() ) );
        CI_LOG_V("draw queued");
        mEventManager->queueEvent( SceneDrawEvent::create( getFrameTimeStep() ) );
        CI_LOG_V("global even manager update");
        mEventManager->update();
        CI_LOG_V("draw GUIs");
        mGuiManager->draw();
    }
    
    void Controller::enableGUI( bool enable )
    {
        mGuiManager->enableGUI( enable );
    }
}