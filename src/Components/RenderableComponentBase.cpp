//
//  RenderableComponentBase.cpp
//  System_test
//
//  Created by Mike Allison on 5/18/15.
//
//

#include "RenderableComponentBase.h"

//
//  VisibleComponentBase.cpp
//  System_test
//
//  Created by Mike Allison on 5/18/15.
//
//

#include "RenderableComponentBase.h"
#include "FrustumCullComponent.h"
#include "SystemEvents.h"
#include "Controller.h"
#include "Scene.h"
#include "cinder/Log.h"
#include "Actor.h"

namespace ec{
    
    ComponentType RenderableComponentBase::TYPE = 0x004;
    
    RenderableComponentBase::RenderableComponentBase()
    {
        Controller::get()->eventManager()->addListener( fastdelegate::MakeDelegate(this, &RenderableComponentBase::handleSceneChange), SceneChangeEvent::TYPE);
        registerHandler();
    }
    
    RenderableComponentBase::~RenderableComponentBase()
    {
        Controller::get()->eventManager()->removeListener( fastdelegate::MakeDelegate(this, &RenderableComponentBase::handleSceneChange), SceneChangeEvent::TYPE);
        
        if( auto scene = Controller::get()->scene().lock() )
        {
            scene->manager()->removeListener(fastdelegate::MakeDelegate(this, &RenderableComponentBase::handleDraw), DrawVisibleComponentsEvent::TYPE );
        }else{
            CI_LOG_E("no current scene");
        }
    }
    
    void RenderableComponentBase::handleSceneChange( EventDataRef event )
    {
        if(mContext->isPersistent())
            registerHandler();
    }
    
    void RenderableComponentBase::handleDraw( EventDataRef event )
    {
        auto cull = mContext->getComponent<FrustumCullComponent>().lock();
        if( cull->isVisible() )
            draw();
    }
    
    void RenderableComponentBase::registerHandler()
    {
        if( auto scene = Controller::get()->scene().lock() )
        {
            scene->manager()->addListener(fastdelegate::MakeDelegate(this, &RenderableComponentBase::handleDraw), DrawVisibleComponentsEvent::TYPE );
        }else{
            CI_LOG_E("no current scene");
        }
    }
}