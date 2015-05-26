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
    
    static ControllerRef        create( const SceneFactoryRef& scene_factory, const ComponentFactoryRef& component_factory );
    static ControllerRef        get();
    void                        initialize( const ci::JsonTree &configuration );
    inline SceneWeakRef         scene() { return mCurrentScene; }
    inline SceneFactoryRef      sceneFactory() { return mSceneFactory; }
    inline EventManagerRef      eventManager(){ return mEventManager; }
    inline ComponentFactoryRef  componentFactory() { return mComponentFactory; }
    void                        update();
    void                        draw();
    void                        nextScene();
    inline void                 enableDebug( bool enable = true ){ mDebug = enable; }
    inline bool                 debugEnabled(){ return mDebug; }
    void                        enableGUI( bool enable = true );
    
    ~Controller();
    
private:
    
    Controller( const SceneFactoryRef& scene_factory, const ComponentFactoryRef& component_factory );
    
    int                         mSceneIndex;
    SceneRef                    mCurrentScene;
    ConfigManagerRef            mConfigManager;
    std::vector<SceneRef>       mScenes;
    EventManagerRef             mEventManager;
    SceneFactoryRef             mSceneFactory;
    ComponentFactoryRef         mComponentFactory;
    GUIManagerRef               mGuiManager;
    ///TODO: debug levels
    bool                        mDebug;
};

}