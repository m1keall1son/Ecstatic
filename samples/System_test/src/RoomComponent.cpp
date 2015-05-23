//
//  RoomComponent.cpp
//  System_test
//
//  Created by Mike Allison on 5/23/15.
//
//

#include "RoomComponent.h"
#include "ComponentBase.h"
#include "TransformComponent.h"
#include "CameraComponent.h"
#include "LightComponent.h"
#include "FrustumCullComponent.h"
#include "RoomComponent.h"
#include "cinder/Log.h"
#include "Actor.h"
#include "AppSceneBase.h"
#include "Scene.h"
#include "Controller.h"
#include "LightManager.h"
#include "ShadowMap.h"
#include "Events.h"

using namespace ci;
using namespace ci::app;

RoomComponentRef RoomComponent::create( ec::Actor* context )
{
    return RoomComponentRef( new RoomComponent(context) );
}


void RoomComponent::update(ec::TimeStepType delta)
{
    auto transform = mContext->getComponent<ec::TransformComponent>().lock();
    transform->setRotation( glm::toQuat( ci::rotate( (float)getElapsedSeconds(), vec3(1.) ) ) );
}

void RoomComponent::drawShadow(ec::EventDataRef)
{
    CI_LOG_V("room_component shadowDraw");
    gl::ScopedModelMatrix model;
    auto transform = mContext->getComponent<ec::TransformComponent>().lock();
    gl::multModelMatrix( transform->getModelMatrix() );
    mRoomShadow->draw();
}

void RoomComponent::draw()
{
    gl::cullFace(GL_FRONT);
    
    CI_LOG_V("room_component draw");
    gl::ScopedModelMatrix model;
    auto transform = mContext->getComponent<ec::TransformComponent>().lock();
    gl::multModelMatrix( transform->getModelMatrix() );
    mRoom->draw();
    
}

ec::ComponentType RoomComponent::TYPE = ec::RenderableComponentBase::TYPE | 0x011;

bool RoomComponent::postInit()
{
    
    auto glsl = gl::GlslProg::create( gl::GlslProg::Format().vertex(loadAsset("lighting.vert")).fragment(loadAsset("lighting.frag")) );
    
    auto scene = std::dynamic_pointer_cast<AppSceneBase>( ec::Controller::get()->scene().lock() );
    
    glsl->uniformBlock("uLights", scene->lights()->getLightUboLocation() );
    glsl->uniform("uShadowMap", 3);
    
    auto flipNormals = []( const vec3& normal ) { return -normal; };
    mRoom = ci::gl::Batch::create( ci::geom::Cube().size( vec3( mRoomSize )) >> geom::AttribFn<vec3, vec3>( geom::NORMAL, geom::NORMAL, flipNormals ), glsl );
    
    mRoomShadow = gl::Batch::create( geom::Cube().size( vec3( mRoomSize ) ), gl::getStockShader(gl::ShaderDef()) );

    CI_LOG_V("room_component Post init complete");
    
    ///this could reflect errors...
    return true;
}

RoomComponent::RoomComponent( ec::Actor* context ):ec::ComponentBase( context ), mId( ec::getHash( context->getName() + "_room_component" ) )
{
    auto scene = std::dynamic_pointer_cast<AppSceneBase>( ec::Controller::get()->scene().lock() );
    scene->manager()->addListener(fastdelegate::MakeDelegate(this, &RoomComponent::drawShadow), DrawDebugEvent::TYPE);
    CI_LOG_V("room_component constructed");
    //TODO this should be in initilialize with ryan's code
    
}

RoomComponent::~RoomComponent()
{
    auto scene = std::dynamic_pointer_cast<AppSceneBase>( ec::Controller::get()->scene().lock() );
    scene->manager()->removeListener(fastdelegate::MakeDelegate(this, &RoomComponent::drawShadow), DrawDebugEvent::TYPE);
}

const ec::ComponentNameType RoomComponent::getName() const
{
    return "room_component";
}

const ec::ComponentUId RoomComponent::getId() const
{
    return mId;
}

const ec::ComponentType RoomComponent::getType() const
{
    return TYPE;
}



