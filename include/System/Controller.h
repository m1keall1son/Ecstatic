//
//  Controller.h
//  System_test
//
//  Created by Mike Allison on 5/5/15.
//
//

#pragma once

#include "Common.h"
#include "cinder/Json.h"
#include "SystemEvents.h"

namespace ec {
    
class Controller {
    
public:
    
    ///TODO: some kind of state that says what mode we are in
    
    static void                 initializeRift( bool enable = true );
    static void                 initializeKinect( bool enable = true );
    static bool                 isRiftEnabled();
    static bool                 isKinectEnabled();
    static double               getAverageFps();
    
    static ControllerRef        create( ci::app::App* conxtext, const SceneFactoryRef& scene_factory, const ComponentFactoryRef& component_factory );
    static ControllerRef        get();
    void                        initialize( const ci::JsonTree &configuration );
    inline SceneWeakRef         scene() { return mCurrentScene; }
    inline GUIManagerRef        guiManager() { return mGuiManager; }
    inline SceneFactoryRef      sceneFactory() { return mSceneFactory; }
    inline EventManagerRef      eventManager(){ return mEventManager; }
    inline ComponentFactoryRef  componentFactory() { return mComponentFactory; }
    void                        update();
    void                        draw();
    void                        nextScene();
    inline void                 enableDebug( bool enable = true ){ mDebug = enable; }
    inline bool                 debugEnabled(){ return mDebug; }
    void                        enableGUI( bool enable = true );
    void                        reset( bool set = true );
    
    ~Controller();
    
private:
    
    Controller( ci::app::App* context, const SceneFactoryRef& scene_factory, const ComponentFactoryRef& component_factory );
    
    
    void                        restart();

    void                        handleRequestNextScene(ec::EventDataRef);
    void                        handleRestart( ec::EventDataRef );
    int                         mSceneIndex;
    SceneRef                    mCurrentScene;
    ConfigManagerRef            mConfigManager;
    std::deque<SceneRef>        mScenes;
    EventManagerRef             mEventManager;
    SceneFactoryRef             mSceneFactory;
    ComponentFactoryRef         mComponentFactory;
    GUIManagerRef               mGuiManager;
    ///TODO: debug levels
    bool                        mDebug;
    bool                        mShouldRestart;
    
    ci::app::App*               mContext;
    
};

}