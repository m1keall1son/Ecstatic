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
#include "CameraManager.h"

using namespace ci;
using namespace ci::app;

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

IntroScene::IntroScene( const std::string& name ):AppSceneBase(name)
{
    //initialize stuff
    CI_LOG_V("Intro scene constructed");
}


void IntroScene::update()
{
    //do stuff
    CI_LOG_V("Intro scene updating");

    //update the superclass
    AppSceneBase::update();
}

void IntroScene::preDraw()
{
    //do stuff
    CI_LOG_V("Intro scene preDrawing");
    gl::pushMatrices();
    gl::setMatrices( mCameras->getCamera( CameraManager::CameraType::MAIN_CAMERA ) );
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
