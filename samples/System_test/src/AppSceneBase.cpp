//
//  AppSceneBase.cpp
//  System_test
//
//  Created by Mike Allison on 5/22/15.
//
//

#include "AppSceneBase.h"

AppSceneBase::AppSceneBase( const std::string& name ):ec::Scene(name)
{
    mLights = LightManagerRef( new LightManager );
    mCameras = CameraManagerRef( new CameraManager );
}

void AppSceneBase::update()
{
    mLights->update();
    ec::Scene::update();
}