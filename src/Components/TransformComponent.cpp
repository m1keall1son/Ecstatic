//
//  TransformComponent.cpp
//  RendererTest
//
//  Created by Ryan Bartley on 9/5/14.
//
//

#include "TransformComponent.h"
#include "Actor.h"

using namespace ci;
using namespace std;

namespace ec {
	
ComponentType TransformComponent::TYPE = 0x001;
    
TransformComponentRef TransformComponent::create(ec::Actor *context)
{
    return TransformComponentRef( new TransformComponent(context) );
}

const ec::ComponentNameType TransformComponent::getName() const
{
    return "transform_component";
}
const ec::ComponentUId TransformComponent::getId() const
{
    return mId;
}
const ec::ComponentType TransformComponent::getType() const
{
    return TYPE;
}
    
TransformComponent::TransformComponent( Actor* context ): ComponentBase(context),  mComponents( new Transformables ), mId( getHash(context->getName()+"_transform_component") )
{
    
}

bool TransformComponent::initialize( const JsonTree &tree )
{
	try {
		auto translations = tree["translation"].getChildren();
		auto end = translations.end();
		vec3 translation;
		int i = 0;
		for( auto translationIt = translations.begin(); translationIt != end; ++translationIt ) {
			 translation[i++] = (*translationIt).getValue<float>();
		}
		setTranslation( translation );
	} catch ( JsonTree::ExcChildNotFound ex	) {
        CI_LOG_W("no translation found, use default");
	}
	
	try {
		auto rotations = tree["rotation"].getChildren();
		auto end = rotations.end();
		quat rotation;
		int i = 0;
		for( auto rotationIt = rotations.begin(); rotationIt != end; ++rotationIt ) {
			rotation[i++] = (*rotationIt).getValue<float>();
		}
		setRotation( rotation );
	} catch ( JsonTree::ExcChildNotFound ex	) {
        CI_LOG_W("no rotation found, use default");
	}
	
	try {
		auto scales = tree["scale"].getChildren();
		auto end = scales.end();
		vec3 scale;
		int i = 0;
		for( auto scaleIt = scales.begin(); scaleIt != end; ++scaleIt ) {
			scale[i++] = (*scaleIt).getValue<float>();
		}
		setScale( scale );
	} catch ( JsonTree::ExcChildNotFound ex	) {
        CI_LOG_W("no scale found, use default vec3(1.)");
	}
	
	return true;
}
	

ci::JsonTree TransformComponent::serialize()
{
    
    auto save = ci::JsonTree();
    save.addChild( ci::JsonTree( "type", getName() ) );
    save.addChild( ci::JsonTree( "id", (uint64_t)getId() ) );
    
    auto scale = ci::JsonTree::makeArray( "scale" );
    for( int i = 0; i<3; i++ ){
        scale.addChild( JsonTree( "", getScale()[i] ) );
    }
    
    save.addChild(scale);
    
    auto rotation = ci::JsonTree::makeArray( "rotation" );
    for( int i = 0; i<4; i++ ){
        rotation.addChild( JsonTree("", getRotation()[i] ) );
    }
    
    save.addChild(rotation);
    
    auto translation = ci::JsonTree::makeArray( "translation" );
    for( int i = 0; i<3; i++ ){
        translation.addChild( JsonTree("", getTranslation()[i] ) );
    }
    
    save.addChild(translation);
    return save;
}

bool TransformComponent::hasChanged()
{
    return mComponents->mUpdated;
}
    
void TransformComponent::loadGUI(const ci::params::InterfaceGlRef &gui)
    {
        gui->addSeparator();
        gui->addText( mContext->getName() +" : "+ getName());
        
        auto updateTranslationFn = [&]{ mComponents->mUpdated |= Transformables::UpdatedType::TRANSLATION; };
        gui->addParam(mContext->getName() +" : translation", &mComponents->mTranslation).updateFn(updateTranslationFn);
        
        auto updateScaleFn = [&]{ mComponents->mUpdated |= Transformables::UpdatedType::SCALE; };
        gui->addParam(mContext->getName() +" : scale", &mComponents->mScale).updateFn(updateScaleFn);
        
        auto updateRotationFn = [&]{ mComponents->mUpdated |= Transformables::UpdatedType::ROTATION; };
        gui->addParam(mContext->getName() +" : rotation", &mComponents->mRotation).updateFn(updateRotationFn);

    }
    
}