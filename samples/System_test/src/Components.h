//
//  Components.h
//  System_test
//
//  Created by Mike Allison on 5/18/15.
//
//

#pragma once
#include "cinder/gl/Batch.h"
#include "cinder/gl/Shader.h"
#include "RenderableComponentBase.h"
#include "UpdatableComponentBase.h"
#include "ComponentFactory.h"
#include "ComponentBase.h"

using ComponentFactoryRef = std::shared_ptr<class ComponentFactory>;

class ComponentFactory : public ec::ComponentFactory {
    
public:
    
    static ComponentFactoryRef create();
    ec::ComponentBaseRef createComponent( ec::Actor* context, const ci::JsonTree& init )override;
};

using CameraComponentRef = std::shared_ptr< class CameraComponent >;

class CameraComponent : public ec::TransformComponent, public ec::UpdatableComponentBase {
    
public:
    
    static ec::ComponentType TYPE;

    static CameraComponentRef create( ec::Actor * context );
    
    bool                initialize( const ci::JsonTree &tree )override;
    ci::JsonTree        serialize()override;

    const ec::ComponentNameType   getName() const override;
    const ec::ComponentUId        getId() const override;
    const ec::ComponentType       getType() const override;

    void update( ec::TimeStepType step )override;
    
    inline ci::CameraPersp& getCamera(){ return mCamera; }
    
private:

    CameraComponent( ec::Actor * context );
    ci::CameraPersp mCamera;
    ec::ComponentUId mId;
    
};


using GeomTeapotRef = std::shared_ptr< class GeomTeapot >;

class GeomTeapot : public ec::RenderableComponentBase {
  
public:
   
    static ec::ComponentType TYPE;
    
    static GeomTeapotRef create( ec::Actor* context );
    
    bool                initialize( const ci::JsonTree &tree )override{ return true; }
    ci::JsonTree        serialize()override{ return ci::JsonTree(); }

    const ec::ComponentNameType   getName() const override;
    const ec::ComponentUId        getId() const override;
    const ec::ComponentType       getType() const override;

    void draw() override;
    void update( ec::TimeStepType delta ) override;
    bool cull() override;

private:
    
    GeomTeapot( ec::Actor* context );
    ci::gl::BatchRef mTeapot;
    ec::ComponentUId mId;

};