//
//  FrustumCullComponent.cpp
//  System_test
//
//  Created by Mike Allison on 5/22/15.
//
//

#include "FrustumCullComponent.h"
#include "CameraManager.h"
#include "Actor.h"
#include "AppSceneBase.h"
#include "Controller.h"
#include "TransformComponent.h"

ec::ComponentType FrustumCullComponent::TYPE = ec::CullableComponentBase::TYPE | 0x013;

FrustumCullComponentRef FrustumCullComponent::create(ec::Actor *context)
{
    return FrustumCullComponentRef( new FrustumCullComponent( context ) );
}

FrustumCullComponent::FrustumCullComponent( ec::Actor * context ): ec::CullableComponentBase(context), mId( ec::getHash( context->getName()+"_frustum_cull_component" ) )
{
    
}

FrustumCullComponent::~FrustumCullComponent()
{
    
}

bool FrustumCullComponent::cull()
{
    
    if( mContext->isActive() ){
        
        auto scene = std::dynamic_pointer_cast<AppSceneBase>(ec::Controller::get()->scene().lock());
        if(scene){
            ci::Frustumf visibleWorld( scene->cameras()->getCamera(CameraManager::CameraType::MAIN_CAMERA) );
            ci::AxisAlignedBox3f worldBoundingBox;
            auto transform = mContext->getComponent<ec::TransformComponent>().lock();
            worldBoundingBox = worldBoundingBox.transformed( transform->getModelMatrix() );
            mIsVisible = !visibleWorld.intersects( worldBoundingBox );
        }
        else
            CI_LOG_E("no scene");
    }
    return mIsVisible;

}

ci::JsonTree FrustumCullComponent::serialize()
{
    auto save = ci::JsonTree();
    save.addChild( ci::JsonTree( "name", getName() ) );
    save.addChild( ci::JsonTree( "id", getId() ) );
    save.addChild( ci::JsonTree( "type", getType() ) );
    save.addChild( ci::JsonTree( "current_visibility", mIsVisible ) );
    return save;
}

const ec::ComponentNameType FrustumCullComponent::getName() const
{
    return "frustum_cull_component";
}
const ec::ComponentUId FrustumCullComponent::getId() const
{
    return mId;
}
const ec::ComponentType FrustumCullComponent::getType() const
{
    return TYPE;
}