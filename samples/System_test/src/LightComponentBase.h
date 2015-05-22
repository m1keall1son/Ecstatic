//
//  LightComponent.h
//  System_test
//
//  Created by Mike Allison on 5/21/15.
//
//

#pragma once

#include "AppCommon.h"
#include "Common.h"
#include "TransformComponent.h"
#include "ComponentBase.h"

enum LightType { DIRECTIONAL = 0, POINT = 1, SPOT = 2, AREA = 3 };

class LightComponentBase : virtual public ec::ComponentBase {
    
public:
    
    static ec::ComponentType TYPE;

    inline const ci::vec3& getDiffuseColor()const{ return mDiffuse; }
    inline const ci::vec3& getDiffuseColor(){ return mDiffuse; }
    inline void setDiffuseColor( const ci::vec3 &color ){ mDiffuse = color; }
    
    inline const ci::vec3& getSpecularColor()const{ return mSpecular; }
    inline const ci::vec3& getSpecularColor(){ return mSpecular; }
    inline void setSpecularColor( const ci::vec3 &color ){ mSpecular = color; }
    
    inline const ci::vec3& getAmbientColor()const{ return mAmbient; }
    inline const ci::vec3& getAmbientColor(){ return mAmbient; }
    inline void setAmbientColor( const ci::vec3 &color ){ mAmbient = color; }
    
    inline const float& getSpecularPower()const{ return mSpecularPower; }
    inline const float& getSpecularPower(){ return mSpecularPower; }
    inline void setSpecularPower( const float &power ){ mSpecularPower = power; }
    
    inline LightType getLightType(){ return mLightType; }
    
    virtual ~LightComponentBase();
    
protected:
    
    LightComponentBase();
    
    inline bool needsUpdate(){ return mNeedsUpdate; }
    
    ci::vec3 mDiffuse;
    ci::vec3 mSpecular;
    ci::vec3 mAmbient;
    float mSpecularPower;
    LightType mLightType;
    bool mNeedsUpdate;
    
    friend class LightManager;
    
};