//
//  DynamicLightComponent.h
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
#include "LightComponentBase.h"
#include "UpdatableComponentBase.h"
#include "LightManager.h"

class DynamicLightComponent : public LightComponentBase, public ec::UpdatableComponentBase {
    
public:
    
    static ec::ComponentType TYPE;
    
    static DynamicLightComponentRef create( ec::Actor* context );
    
    bool                initialize( const ci::JsonTree &tree )override{ return true; }
    ci::JsonTree        serialize()override{ return ci::JsonTree(); }

    const ec::ComponentNameType   getName() const override;
    const ec::ComponentUId        getId() const override;
    const ec::ComponentType       getType() const override;

    inline LightType getLightType(){ return mLightType; }

    void update( ec::TimeStepType delta ) override;

private:

    DynamicLightComponent( ec::Actor* context );
    LightType mLightType;
    ec::ComponentUId mId;

};
