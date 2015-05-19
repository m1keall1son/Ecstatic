//
//  Scenes.cpp
//  System_test
//
//  Created by Mike Allison on 5/18/15.
//
//

#include "cinder/Log.h"
#include "Scenes.h"
#include "SystemEvents.h"
#include "Actor.h"
#include "Components.h"

using namespace ci;
using namespace ci::app;

static SceneCameraType parseCameraType( const ec::ActorTypeQualifier &qualifier )
{
    if( qualifier == "main" )return SceneCameraType::MAIN_CAMERA;
    else if( qualifier == "debug" )return SceneCameraType::DEBUG_CAMERA;
    else return SceneCameraType::MAIN_CAMERA;
}

static LightType parseLightType( const ec::ActorTypeQualifier &qualifier )
{
    if( qualifier == "sun" )return LightType::SUN;
    else if( qualifier == "point" )return LightType::POINT;
    else return LightType::SUN;
}

SceneFactoryRef SceneFactory::create()
{
    return SceneFactoryRef( new SceneFactory );
}

ec::SceneRef SceneFactory::createScene( const ci::JsonTree& init )
{
    std::string name = "";
    
    try{
        
        name = init.getValueForKey("name");
        
    } catch (const ci::JsonTree::ExcChildNotFound &e) {
        CI_LOG_E( e.what() );
    }
    
    if (name == "intro")
    {
        CI_LOG_V("parsed intro scene");
        return IntroScene::create(name);
    }else{
        return nullptr;
    }

}

IntroSceneRef IntroScene::create( const std::string& name )
{
    return IntroSceneRef( new IntroScene(name) );
}

IntroScene::IntroScene( const std::string& name ):ec::Scene(name)
{
    //initialize stuff
    CI_LOG_V("Intro scene constructed");
}


void IntroScene::update()
{
    //do stuff
    CI_LOG_V("Intro scene updating");

    ec::Scene::update();
}

void IntroScene::preDraw()
{
    //do stuff
    CI_LOG_V("Intro scene preDrawing");
    gl::pushMatrices();
    auto actor = mActors.find( mCameras.find(MAIN_CAMERA)->second )->second.lock();
    if( actor ){
        auto camera_component_weak = actor->getComponent<CameraComponent>(CameraComponent::TYPE);
        gl::setMatrices( camera_component_weak.lock()->getCamera() );
    }
}

void IntroScene::draw()
{
    //do stuff
    CI_LOG_V("Intro scene drawing");
    
}

void IntroScene::postDraw()
{
    //do stuff
    CI_LOG_V("Intro scene postDrawing");
    gl::popMatrices();
}

void IntroScene::logActorType(ec::ReturnActorCreatedEventRef event)
{
    //do stuff
    CI_LOG_V("logging actor type");
    auto strong = event->getActorWeakRef().lock();
    if( strong ){
        if( strong->getType() == "camera" ){
            mCameras.insert( std::make_pair( parseCameraType( strong->getTypeQualifier() ), strong->getUId() ) );
        }else if( strong->getType() == "light" ){
            mLights.insert( std::make_pair( parseLightType( strong->getTypeQualifier() ), strong->getUId() ) );
        }
    }
    
}