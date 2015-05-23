//
//  CameraComponent.cpp
//  System_test
//
//  Created by Mike Allison on 5/21/15.
//
//

#include "CameraComponent.h"
#include "TransformComponent.h"
#include "Actor.h"
#include "ComponentBase.h"

using namespace ci;
using namespace ci::app;

ec::ComponentType CameraComponent::TYPE = ec::UpdatableComponentBase::TYPE | 0x012;

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
        CI_LOG_W(std::string(ex.what())+" setting default camera");
        mCamera.setPerspective(60, getWindowAspectRatio(), .1, 1000);
    }
    
    CI_LOG_V("camera_component initialized");
    
    return true;
}

ci::JsonTree CameraComponent::serialize()
{
    auto save = ci::JsonTree();
    
    save.addChild( ci::JsonTree( "name", getName() ) );
    save.addChild( ci::JsonTree( "id", getId() ) );
    save.addChild( ci::JsonTree( "type", "camera_component" ) );
    save.addChild( ci::JsonTree( "fov", mCamera.getFov() ) );
    save.addChild( ci::JsonTree( "near", mCamera.getNearClip() ) );
    save.addChild( ci::JsonTree( "far", mCamera.getFarClip() ) );
    save.addChild( ci::JsonTree( "aspect", mCamera.getAspectRatio() ) );
    
    return save;
    
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
    auto transform = mContext->getComponent<ec::TransformComponent>().lock();
    mCamera.lookAt( transform->getTranslation(), vec3(0) );
    // mCamera.setViewDirection( glm::eulerAngles( getRotation() ) );
}

