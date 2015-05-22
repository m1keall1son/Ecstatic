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

