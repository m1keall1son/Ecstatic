//
//  RoomComponent.h
//  System_test
//
//  Created by Mike Allison on 5/23/15.
//
//

#pragma once
#include "cinder/gl/Batch.h"
#include "cinder/gl/Shader.h"
#include "RenderableComponentBase.h"
#include "UpdatableComponentBase.h"
#include "ComponentFactory.h"
#include "ComponentBase.h"
#include "AppCommon.h"

class RoomComponent : public ec::RenderableComponentBase {
    
public:
    
    static ec::ComponentType TYPE;
    
    static RoomComponentRef create( ec::Actor* context );
    
    bool                          initialize( const ci::JsonTree &tree )override;
    ci::JsonTree                  serialize()override;
    const ec::ComponentNameType   getName() const override;
    const ec::ComponentUId        getId() const override;
    const ec::ComponentType       getType() const override;

    bool postInit()override;
    void draw() override;
    
    void drawShadow( ec::EventDataRef );
    
    void update( ec::TimeStepType delta ) override;
    
    ~RoomComponent();

private:

    RoomComponent( ec::Actor* context );
    ci::gl::BatchRef mRoom;
    ci::gl::BatchRef mRoomShadow;
    float mRoomSize;
    ec::ComponentUId mId;

};