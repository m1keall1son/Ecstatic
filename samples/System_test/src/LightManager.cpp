//
//  LightManager.cpp
//  System_test
//
//  Created by Mike Allison on 5/21/15.
//
//

#include "LightManager.h"
#include "CameraComponent.h"
#include "ActorManager.h"
#include "Actor.h"
#include "Controller.h"
#include "SystemEvents.h"
#include "EventManager.h"
#include "FrustumCullComponent.h"
#include "LightComponentBase.h"

LightType LightManager::parseLightType( const ec::ActorTypeQualifier &qualifier )
{
    if( qualifier == "directional" )return LightType::DIRECTIONAL;
    else if( qualifier == "point" )return LightType::POINT;
    else if( qualifier == "spot" )return LightType::SPOT;
    else if( qualifier == "area" )return LightType::AREA;
    else return LightType::DIRECTIONAL;
}

LightManager::LightManager()
{
    
    mLightUboLocation = 0;
    
    ec::Controller::get()->eventManager()->addListener( fastdelegate::MakeDelegate( this, &LightManager::handleLightRegistration), ec::ReturnActorCreatedEvent::TYPE);
    
    BufferableLights lights;
    lights.numLights = 0;
    
    mLightUbo = ci::gl::Ubo::create( sizeof(lights), &lights , GL_DYNAMIC_DRAW);
    mLightUbo->bindBufferBase(mLightUboLocation);
}

LightManager::~LightManager()
{
    ec::Controller::get()->eventManager()->removeListener( fastdelegate::MakeDelegate( this, &LightManager::handleLightRegistration), ec::ReturnActorCreatedEvent::TYPE);
}

void LightManager::handleLightRegistration( ec::EventDataRef event )
{
    auto e = std::dynamic_pointer_cast<ec::ReturnActorCreatedEvent>( event );
    auto strong = e->getActorWeakRef().lock();
    if( strong ){
        if( strong->getType() == "light" ){
            CI_LOG_V("Registering light");
            mLights.push_back( strong->getUId() );
        }
    }
}

void LightManager::update() {
    
    bool updateAll = false;
    ///TODO: could do an event registration here instead of running through all scene lights every frame
    
    std::vector< LightComponentBaseRef > activeLights;
    
    for( auto & light : mLights ){
        
        auto light_strong = ec::ActorManager::get()->retreiveUnique(light).lock();
        if(light_strong){
            auto light_component = light_strong->getComponent<LightComponentBase>().lock();
            
            if(light_component){
                
                if( light_strong->isActive() ){
                    if(activeLights.size() < 24)
                        activeLights.push_back(light_component);
                    if( light_component->needsUpdate() ){
                        updateAll = true;
                    }
                }
            }
        }
    }
    
    if( updateAll ){
        
        BufferableLights lights;
        
        int i = 0;
        for( auto & l : activeLights ){
         
            BufferableLightData data;
            data.ambientColor  = l->getAmbientColor();
            data.diffuseColor  = l->getDiffuseColor();
            data.specularColor = l->getSpecularColor();
            data.specularPower = l->getSpecularPower();
            data.type          = l->getLightType();
            
            lights.lights[i] = data;
            
            i++;
        }
        lights.numLights = activeLights.size();
     
        mLightUbo->bufferSubData(0, sizeof(lights), &lights);
        
    }
    
}