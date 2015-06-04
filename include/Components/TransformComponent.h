//
//  TransformComponent.h
//  RendererTest
//
//  Created by Ryan Bartley on 9/5/14.
//
//

#pragma once
#include "cinder/Json.h"
#include "ComponentBase.h"
#include "Common.h"

namespace ec {
	
    //TODO: transform component must have target (pointer to another actor location), lookat, view direction etc.
	
class TransformComponent : public ComponentBase {
public:
	
    static ComponentType TYPE;
    
	struct Transformables {
		
		enum UpdatedType {
			SCALE = 1 << 0,
			ROTATION = 1 << 1,
			TRANSLATION = 1 << 2
		};
		
		
		Transformables() : mUpdated(0),	mScale( ci::vec3( 1.0f ) ),
		mTranslation( ci::vec3( 0.0f ) )
		{}
		
		inline void checkUpdated() {
			if( mUpdated == 0 ) return;
			
			// TODO: Changed this alot figure out if it still works
			mModelMatrix = ci::mat4();
			mModelMatrix *= ci::scale( mScale );
			mModelMatrix *= ci::toMat4( mRotation );
			mModelMatrix *= ci::translate( mTranslation );
			mUpdated = 0;
		}
		
		inline ci::mat4& getModelMatrix() {
			checkUpdated();
			return mModelMatrix;
		}
		
		inline void setTranslation( const ci::vec3 &translation ) {
			mUpdated |= UpdatedType::TRANSLATION;
			mTranslation = translation;
		}
		inline void translate( const ci::vec3 &translation ) {
			mUpdated |= UpdatedType::TRANSLATION;
			mTranslation += translation;
		}
		inline void setScale( const ci::vec3 &scale ) {
			mUpdated |= UpdatedType::SCALE;
			mScale = scale;
		}
		inline void setRotation( const ci::quat &rotation ) {
			mUpdated |= UpdatedType::ROTATION;
			mRotation = rotation;
		}
		inline void rotate( const ci::quat &rotation ) {
			mUpdated |= UpdatedType::ROTATION;
			mRotation *= rotation;
		}
		inline const ci::vec3& getTranslation() const { return mTranslation; }
		inline const ci::vec3& getScale() const { return mScale; }
		inline const ci::quat& getRotation() const { return mRotation; }
		
		ci::mat4		mModelMatrix;
		ci::vec3		mTranslation, mScale;
		ci::quat		mRotation;
		uint32_t		mUpdated;
		
		friend class TransformComponent;
	};
    
	virtual ~TransformComponent() {
		delete mComponents;
	}
    
    static TransformComponentRef create( Actor* context );
    
    virtual bool initialize( const ci::JsonTree &tree )override;
    virtual ci::JsonTree serialize()override;

    virtual const ec::ComponentNameType   getName() const override;
    virtual const ec::ComponentUId        getId() const override;
    virtual const ec::ComponentType       getType() const override;
    virtual void                          loadGUI( const ci::params::InterfaceGlRef &gui )override;
    virtual void                          cleanup()override{}
    
    virtual bool postInit()override{ return true; }
    
	inline const ci::mat4& getModelMatrix() const { return mComponents->getModelMatrix(); }
	
	//! Sets the Translation of the write component
	inline void setTranslation( const ci::vec3 &translation ) {
		mComponents->setTranslation( translation );
	}
	inline void translate( const ci::vec3 &translation ) {
		mComponents->translate( translation );
	}
	//! Sets the scale of the write component
	inline void setScale( const ci::vec3 &scale ) {
		mComponents->setScale( scale );
	}
	//! Sets the rotation of the write component
	inline void setRotation( const ci::quat &rotation ) {
		mComponents->setRotation( rotation );
	}
	inline void rotate( const ci::quat &rotation ) {
		mComponents->rotate( rotation );
	}
	inline const ci::vec3& getTranslation() const { return mComponents->getTranslation(); }
	inline const ci::vec3& getScale() const { return mComponents->getScale(); }
	inline const ci::quat& getRotation() const { return mComponents->getRotation(); }
    
    bool hasChanged();
	
protected:
    
    TransformComponent( Actor* context );
    ComponentUId mId;
	Transformables *mComponents;
};
	
}
