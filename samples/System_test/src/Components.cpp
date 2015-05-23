//
//  Components.cpp
//  System_test
//
//  Created by Mike Allison on 5/18/15.
//
//

#include "Components.h"
#include "ComponentBase.h"
#include "TransformComponent.h"
#include "CameraComponent.h"
#include "LightComponent.h"
#include "FrustumCullComponent.h"
#include "GeomTeapotComponent.h"
#include "RoomComponent.h"
#include "cinder/Log.h"
#include "Actor.h"
#include "AppSceneBase.h"
#include "Scene.h"
#include "Controller.h"
#include "LightManager.h"
#include "ShadowMap.h"

using namespace ci;
using namespace ci::app;

ComponentFactoryRef ComponentFactory::create()
{
    return ComponentFactoryRef( new ComponentFactory );
}

ec::ComponentBaseRef ComponentFactory::createComponent( ec::Actor* context, const ci::JsonTree& init )
{
    std::string type = "";
    
    try{
        
        type = init.getValueForKey("type");
        
    } catch (const ci::JsonTree::ExcChildNotFound &e) {
        CI_LOG_E( e.what() );
    }
    
    if (type == "transform_component")
    {
        CI_LOG_V("parsed transform component");
        auto transform = ec::TransformComponent::create(context);
        transform->initialize(init);
        return transform;
        
    }
    else if (type == "light_component")
    {
        CI_LOG_V("parsed dynamic_light component");
        auto c = LightComponent::create(context);
        c->initialize(init);
        return c;
        
    }
    else if (type == "geom_teapot_component")
    {
        CI_LOG_V("parsed geom_teapot component");
        auto teapot = GeomTeapotComponent::create(context);
        teapot->initialize(init);
        return teapot;
        
    }
    else if (type == "room_component")
    {
        CI_LOG_V("parsed room_component component");
        auto room = RoomComponent::create(context);
        room->initialize(init);
        return room;
        
    }
    else if (type == "camera_component")
    {
        CI_LOG_V("parsed camera_component component");
        auto camera = CameraComponent::create(context);
        camera->initialize(init);
        return camera;
        
    }
    else{
        CI_LOG_E( "Unknown component type" );
        return nullptr;
    }
    
}

