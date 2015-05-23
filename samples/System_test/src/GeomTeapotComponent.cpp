//
//  GeomTeapotComponentComponent.cpp
//  System_test
//
//  Created by Mike Allison on 5/23/15.
//
//

#include "GeomTeapotComponent.h"
#include "Actor.h"
#include "Events.h"
#include "Scene.h"
#include "AppSceneBase.h"
#include "Controller.h"

using namespace ci;
using namespace ci::app;

GeomTeapotComponentRef GeomTeapotComponent::create( ec::Actor* context )
{
    return GeomTeapotComponentRef( new GeomTeapotComponent(context) );
}


void GeomTeapotComponent::update(ec::TimeStepType delta)
{
    auto transform = mContext->getComponent<ec::TransformComponent>().lock();
    transform->setRotation( glm::toQuat( ci::rotate( (float)getElapsedSeconds(), vec3(1.) ) ) );
}

void GeomTeapotComponent::drawShadow( ec::EventDataRef )
{
    
    CI_LOG_V("geom_teapot shadow draw");
    gl::ScopedModelMatrix model;
    auto transform = mContext->getComponent<ec::TransformComponent>().lock();
    gl::multModelMatrix( transform->getModelMatrix() );
    mTeapotShadow->draw();
    
}

void GeomTeapotComponent::draw()
{
    gl::cullFace(GL_BACK);
    
    CI_LOG_V("geom_teapot draw");
    gl::ScopedModelMatrix model;
    auto transform = mContext->getComponent<ec::TransformComponent>().lock();
    gl::multModelMatrix( transform->getModelMatrix() );
    mTeapot->draw();
    
}

ec::ComponentType GeomTeapotComponent::TYPE = ec::RenderableComponentBase::TYPE | 0x011;

bool GeomTeapotComponent::postInit()
{
    
    auto glsl = gl::GlslProg::create( gl::GlslProg::Format().vertex(loadAsset("lighting.vert")).fragment(loadAsset("lighting.frag")) );
    
    auto scene = std::dynamic_pointer_cast<AppSceneBase>( ec::Controller::get()->scene().lock() );
    
    glsl->uniformBlock("uLights", scene->lights()->getLightUboLocation() );
    glsl->uniform("uShadowMap", 3);
    
    mTeapot = ci::gl::Batch::create( ci::geom::Teapot(), glsl );
    
    mTeapotShadow = ci::gl::Batch::create( ci::geom::Teapot(), gl::getStockShader( gl::ShaderDef() ) );
    
    CI_LOG_V("geom_teapot Post init complete");
    
    ///this could reflect errors...
    return true;
}

GeomTeapotComponent::GeomTeapotComponent( ec::Actor* context ):ec::ComponentBase( context ), mId( ec::getHash( context->getName() + "geom_teapot_component" ) )
{
    CI_LOG_V("geom_teapot constructed");
    //TODO this should be in initilialize with ryan's code
    auto scene = std::dynamic_pointer_cast<AppSceneBase>( ec::Controller::get()->scene().lock() );
    scene->manager()->addListener(fastdelegate::MakeDelegate(this, &GeomTeapotComponent::drawShadow), DrawShadowEvent::TYPE);
}

GeomTeapotComponent::~GeomTeapotComponent()
{
    auto scene = std::dynamic_pointer_cast<AppSceneBase>( ec::Controller::get()->scene().lock() );
    scene->manager()->removeListener(fastdelegate::MakeDelegate(this, &GeomTeapotComponent::drawShadow), DrawShadowEvent::TYPE);

}

const ec::ComponentNameType GeomTeapotComponent::getName() const
{
    return "geom_teapot_component";
}

const ec::ComponentUId GeomTeapotComponent::getId() const
{
    return mId;
}

const ec::ComponentType GeomTeapotComponent::getType() const
{
    return TYPE;
}



