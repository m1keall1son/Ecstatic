//
//  CameraComponent.h
//  System_test
//
//  Created by Mike Allison on 5/21/15.
//
//

#pragma once

#include "AppCommon.h"
#include "Common.h"
#include "ComponentBase.h"
#include "TransformComponent.h"
#include "UpdatableComponentBase.h"

class CameraComponent : public ec::UpdatableComponentBase {
    
public:
    
    static ec::ComponentType TYPE;
    
    static CameraComponentRef create( ec::Actor * context );
    
    bool                          initialize( const ci::JsonTree &tree )override;
    bool                          postInit()override{}
    ci::JsonTree                  serialize()override;
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
