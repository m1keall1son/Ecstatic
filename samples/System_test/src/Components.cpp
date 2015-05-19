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
    
    if (type == "geom_teapot")
    {
        CI_LOG_V("parsed geom_teapot component");
        auto teapot = GeomTeapot::create(context);
        teapot->initialize(init);
        return teapot;
        
    }
    if (type == "camera_component")
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

ec::ComponentType CameraComponent::TYPE = ec::UpdatableComponentBase::TYPE | TransformComponent::TYPE | 0x012;

CameraComponentRef CameraComponent::create( ec::Actor * context )
{
    return CameraComponentRef( new CameraComponent(context) );
}

CameraComponent::CameraComponent( ec::Actor* context ) : ec::ComponentBase( context ), mId(ec::getHash( context->getName() + "camera_component" ))
{
    CI_LOG_V("camera_component constructed");
}

bool CameraComponent::initialize( const ci::JsonTree &tree )
{
    //init base class
    TransformComponent::initialize(tree);
    
    
    try {
        auto fov = tree["fov"].getValue<float>();
        auto near = tree["near"].getValue<float>();
        auto far = tree["far"].getValue<float>();
        auto aspect = tree["aspect"].getValue();
        
        if(aspect == "window")
            mCamera.setPerspective( fov, getWindowAspectRatio(), near, far);
        else
            mCamera.setPerspective(fov, std::stof(aspect), near, far);

    } catch ( JsonTree::ExcChildNotFound ex	) {
        CI_LOG_E(std::string(ex.what())+" setting default camera");
        mCamera.setPerspective(60, getWindowAspectRatio(), .1, 1000);
    }
    
    CI_LOG_V("camera_component initialized");

    return true;
}

ci::JsonTree CameraComponent::serialize()
{
    return ci::JsonTree();
}

const ec::ComponentNameType CameraComponent::getName() const
{
    return "camera_component";
}

const ec::ComponentUId CameraComponent::getId() const
{
    return mId;
}

const ec::ComponentType CameraComponent::getType() const
{
    return TYPE;
}

void CameraComponent::update(ec::TimeStepType step)
{
    CI_LOG_V("camera_component update");
    //TODO: transform must have target (pointer to another actor location), lookat, view direction,
    auto & t = getTranslation();
    mCamera.lookAt( t, vec3(0) );
   // mCamera.setViewDirection( glm::eulerAngles( getRotation() ) );
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



