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
    
    
TransformComponent::TransformComponent(): mComponents( new Transformables )
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
		setScale( vec3( 1.0f ) );
	}
	
	return true;
}
	

ci::JsonTree TransformComponent::serialize()
{
    
    auto save = ci::JsonTree();
    save.addChild( ci::JsonTree( "name", getName() ) );
    save.addChild( ci::JsonTree( "id", getId() ) );
    save.addChild( ci::JsonTree( "type", getType() ) );
    
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

	
}