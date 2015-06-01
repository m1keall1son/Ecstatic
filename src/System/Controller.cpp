//
//  Controller.cpp
//  System_test
//
//  Created by Mike Allison on 5/5/15.
//
//

#include "Controller.h"
#include "cinder/app/App.h"
#include "cinder/Log.h"
#include "ConfigManager.h"
#include "Scene.h"
#include "SystemEvents.h"
#include "SceneFactory.h"
#include "ActorManager.h"
#include "GUIManager.h"
#include "SystemEvents.h"
#include "OculusRiftComponent.h"

using namespace ci;
using namespace ci::app;

namespace ec {
    
    static bool sRiftEnabled = false;
    static double sFPS = 0.;
    
    void Controller::initializeRift( bool enable )
    {
        sRiftEnabled = enable;
        if( enable )
            OculusRiftComponent::initializeRift();
    }
    
    bool Controller::isRiftEnabled()
    {
        return sRiftEnabled;
    }
    
    double Controller::getAverageFps()
    {
        return sFPS;
    }
    
    static ControllerRef sController = nullptr;
    
    ControllerRef Controller::create( ci::app::App* context, const SceneFactoryRef& scene_factory,const ComponentFactoryRef& component_factory )
    {
        sController = ControllerRef( new Controller( context, scene_factory, component_factory) );
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
    
    Controller::Controller( ci::app::App* context, const SceneFactoryRef& scene_factory, const ComponentFactoryRef& component_factory ) : mSceneIndex(0), mCurrentScene(nullptr), mConfigManager(nullptr), mSceneFactory(scene_factory), mComponentFactory(component_factory), mDebug(false),mContext(context)
    {
        CI_LOG_V("controller constructing...");
        mEventManager = EventManager::create("global event manager");
        mGuiManager = GUIManager::create();
        mGuiManager->enableGUI(false);
        mEventManager->addListener(fastdelegate::MakeDelegate(mGuiManager.get(), &GUIManager::handleUninit), UninitGUIEvent::TYPE);
        mEventManager->addListener(fastdelegate::MakeDelegate(mGuiManager.get(), &GUIManager::handleSceneChange), ec::SceneChangeEvent::TYPE);
        mEventManager->addListener(fastdelegate::MakeDelegate(this, &Controller::handleRequestNextScene), RequestSceneChangeEvent::TYPE);
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
        mCurrentScene = mScenes.front();
        mScenes.pop_front();
        CI_LOG_V("controller initialized");
        CI_LOG_V("controller initializing scene: "+ mCurrentScene->getName() +"...");
        mCurrentScene->initialize();
        CI_LOG_V("controller scene: "+ mCurrentScene->getName() +" initialized!");
        CI_LOG_V("Initialize scene GUIs");
        mGuiManager->postInit();
    }
    
    void Controller::handleRequestNextScene(ec::EventDataRef)
    {
        nextScene();
    }
    
    void Controller::nextScene()
    {
        CI_LOG_V("request next scene");
        auto persisten_actors = mCurrentScene->shutdown();
        auto next = mScenes.front();
        mCurrentScene = next;
        next->initialize( persisten_actors );
        mScenes.pop_front();
        mEventManager->triggerEvent(SceneChangeEvent::create());
    }
    
    void Controller::update()
    {
        CI_LOG_V("update queued");
        mEventManager->queueEvent( SceneUpdateEvent::create( getFrameTimeStep() ) );
        sFPS = mContext->getAverageFps();
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
        if(!isRiftEnabled())mGuiManager->draw();
        
        if( debugEnabled() ){//showFps
            ci::gl::ScopedMatrices pushMatrix;
            ci::gl::setMatricesWindow( mContext->getWindowSize());
            ci::gl::ScopedViewport view( vec2(0), mContext->getWindowSize() );
            ci::gl::drawString(std::to_string( mContext->getAverageFps()),ci::vec2(10));
        }
    }
    
    void Controller::enableGUI( bool enable )
    {
        mGuiManager->enableGUI( enable );
    }
}