//
//  UpdateComponentBase.cpp
//  System_test
//
//  Created by Mike Allison on 5/5/15.
//
//

#include "UpdatableComponentBase.h"
#include "SystemEvents.h"
#include "Controller.h"
#include "Scene.h"
#include "cinder/Log.h"
#include "Actor.h"

namespace ec {
    
    ComponentType UpdatableComponentBase::TYPE = 0x002;
    
    UpdatableComponentBase::UpdatableComponentBase( Actor * context ):ComponentBase( context )
    {
        registerHandler();
        Controller::get()->eventManager()->addListener( fastdelegate::MakeDelegate(this, &UpdatableComponentBase::handleSceneChange), SceneChangeEvent::TYPE);
    }
    
    
    UpdatableComponentBase::~UpdatableComponentBase()
    {
        Controller::get()->eventManager()->removeListener( fastdelegate::MakeDelegate(this, &UpdatableComponentBase::handleSceneChange), SceneChangeEvent::TYPE);

        if( auto scene = Controller::get()->scene().lock() )
        {
            scene->manager()->removeListener(fastdelegate::MakeDelegate(this, &UpdatableComponentBase::handleUpdateComponent), UpdateComponentsEvent::TYPE );
        }else{
            CI_LOG_E("no current scene");
        }
    }
    
    void UpdatableComponentBase::handleUpdateComponent(EventDataRef event)
    {
        auto e = std::dynamic_pointer_cast<UpdateComponentsEvent>(event);
        update( e->getTimeStep() );
    }
    
    void UpdatableComponentBase::handleSceneChange(EventDataRef)
    {
        if(mContext->isPersistent())
            registerHandler();
    }
    
    void UpdatableComponentBase::registerHandler()
    {
        if( auto scene = Controller::get()->scene().lock() )
        {
            CI_LOG_V("registering updatablecomponent to scene event manager");
            scene->manager()->addListener(fastdelegate::MakeDelegate(this, &UpdatableComponentBase::handleUpdateComponent), UpdateComponentsEvent::TYPE );
        }else{
            CI_LOG_E("no current scene");
        }
    }
    
}