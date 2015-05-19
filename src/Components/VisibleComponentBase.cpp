//
//  VisibleComponentBase.cpp
//  System_test
//
//  Created by Mike Allison on 5/18/15.
//
//

#include "VisibleComponentBase.h"
#include "SystemEvents.h"
#include "Controller.h"
#include "Scene.h"
#include "cinder/Log.h"
#include "Actor.h"

namespace ec{

    ComponentType CullableComponentBase::TYPE = 0x003;
    
    CullableComponentBase::CullableComponentBase()
    {
        Controller::get()->eventManager()->addListener( fastdelegate::MakeDelegate(this, &CullableComponentBase::handleSceneChange), SceneChangeEvent::TYPE);
        registerHandler();
    }
    
    CullableComponentBase::~CullableComponentBase()
    {
        Controller::get()->eventManager()->removeListener( fastdelegate::MakeDelegate(this, &CullableComponentBase::handleSceneChange), SceneChangeEvent::TYPE);
        
        if( auto scene = Controller::get()->scene().lock() )
        {
            scene->manager()->removeListener(fastdelegate::MakeDelegate(this, &CullableComponentBase::handleCulling), CullVisibleComponentsEvent::TYPE );
        }else{
            CI_LOG_E("no current scene");
        }
    }

    void CullableComponentBase::handleSceneChange( EventDataRef event )
    {
        if(mContext->isPersistent())
            registerHandler();
    }
    
    void CullableComponentBase::handleCulling( EventDataRef event )
    {
        //deal with culling here to set visibility
        mIsVisible = cull();
    }

    void CullableComponentBase::registerHandler()
    {
        if( auto scene = Controller::get()->scene().lock() )
        {
            scene->manager()->addListener(fastdelegate::MakeDelegate(this, &CullableComponentBase::handleCulling), CullVisibleComponentsEvent::TYPE );
        }else{
            CI_LOG_E("no current scene");
        }
    }
}