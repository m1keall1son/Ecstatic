//
//  LightManager.h
//  System_test
//
//  Created by Mike Allison on 5/21/15.
//
//

#pragma once

#include "AppCommon.h"
#include "Common.h"
#include "cinder/gl/Ubo.h"
#include "LightComponentBase.h"

class LightManager {
    
public:
    
    static LightType parseLightType( const ec::ActorTypeQualifier &qualifier );
    
    inline std::vector< ec::ActorUId >& getLights(){ return mLights; }
    
    inline int getLightUboLocation(){ return mLightUboLocation; }
    
    void update();
    
    ~LightManager();
    
private:
    
    struct BufferableLightData{
        
        ci::vec3 ambientColor;
        ci::vec3 diffuseColor;
        ci::vec3 specularColor;
        float    specularPower;
        int      type;
        ci::vec2 pad;
        
    };
    
    struct BufferableLights {
        
        BufferableLightData lights[24];
        int                 numLights;
    };
    
    
    LightManager();
    
    void handleLightRegistration( ec::EventDataRef );
    
    std::vector< ec::ActorUId > mLights;
    ci::gl::UboRef  mLightUbo;
    int             mLightUboLocation;
    
    friend class AppSceneBase;
    
};