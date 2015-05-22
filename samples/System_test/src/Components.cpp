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
#include "DynamicLightComponent.h"
#include "StaticLightComponent.h"
#include "ShadowLightComponent.h"
#include "FrustumCullComponent.h"
#include "cinder/Log.h"
#include "Actor.h"

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
    else if (type == "dynamic_light_component")
    {
        CI_LOG_V("parsed dynamic_light component");
        auto c = DynamicLightComponent::create(context);
        c->initialize(init);
        return c;
        
    }
    else if (type == "geom_teapot")
    {
        CI_LOG_V("parsed geom_teapot component");
        auto teapot = GeomTeapot::create(context);
        teapot->initialize(init);
        return teapot;
        
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

GeomTeapotRef GeomTeapot::create( ec::Actor* context )
{
    return GeomTeapotRef( new GeomTeapot(context) );
}

bool GeomTeapot::cull()
{
    CI_LOG_V("geom_teapot cull");
    return true;
}

void GeomTeapot::update(ec::TimeStepType delta)
{
    setRotation( glm::toQuat( ci::rotate( (float)getElapsedSeconds(), vec3(1.) ) ) );
}

void GeomTeapot::draw()
{
    CI_LOG_V("geom_teapot draw");
    gl::ScopedModelMatrix model;
    gl::multModelMatrix( getModelMatrix() );
    mTeapot->draw();
}

ec::ComponentType GeomTeapot::TYPE = ec::RenderableComponentBase::TYPE | 0x011;

GeomTeapot::GeomTeapot( ec::Actor* context ):ec::ComponentBase( context ), mId( ec::getHash( context->getName() + "geom_teapot" ) )
{
    CI_LOG_V("geom_teapot constructed");
    //TODO this should be in initilialize with ryan's code
    mTeapot = ci::gl::Batch::create( ci::geom::Teapot(), ci::gl::getStockShader(ci::gl::ShaderDef().color() ) );
}

const ec::ComponentNameType GeomTeapot::getName() const
{
    return "geom_teapot";
}

const ec::ComponentUId GeomTeapot::getId() const
{
    return mId;
}

const ec::ComponentType GeomTeapot::getType() const
{
    return TYPE;
}



