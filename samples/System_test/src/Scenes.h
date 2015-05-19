//
//  Scenes.h
//  System_test
//
//  Created by Mike Allison on 5/18/15.
//
//

#pragma once
#include "Common.h"
#include "SceneFactory.h"
#include "Scene.h"

enum SceneCameraType { MAIN_CAMERA, DEBUG_CAMERA };
enum LightType { SUN, POINT };

using SceneFactoryRef = std::shared_ptr<class SceneFactory>;

class SceneFactory : public ec::SceneFactory {
    
public:
    
    static SceneFactoryRef create();
    ec::SceneRef createScene( const ci::JsonTree& init ) override;
    
};

using IntroSceneRef = std::shared_ptr<class IntroScene>;

class IntroScene : public ec::Scene {
    
public:
    
    static IntroSceneRef create( const std::string& name );
    
    void update() override;
    void preDraw() override;
    void draw() override;
    void postDraw() override;
    void logActorType( ec::ReturnActorCreatedEventRef event )override;
    
private:
    
    IntroScene( const std::string& name );
    
    std::map< SceneCameraType, ec::ActorUId > mCameras;
    std::map< LightType, ec::ActorUId > mLights;

};