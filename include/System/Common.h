//
//  Common.h
//  System_test
//
//  Created by Mike Allison on 4/29/15.
//
//

#pragma once

namespace ec {

uint64_t getHash( const std::string& to_hash );
    
///SYSTEM
    
const double MAX_DELTA_TIME = .1;
    
using ControllerRef = std::shared_ptr< class Controller >;
using IdType = int64_t;
using FactoryType = IdType;
using TimeStepType = double;
TimeStepType getFrameTimeStep();
using ActorFactoryRef = std::shared_ptr<class ActorFactory>;
using ComponentFactoryRef = std::shared_ptr<class ComponentFactory>;
    
///MANAGERS
    
using ActorManagerRef = std::shared_ptr<class ActorManager>;
using ConfigManagerRef = std::shared_ptr< class ConfigManager >;
    
///EVENT SYSTEM
    
using EventDataRef = std::shared_ptr<class EventData>;
using EventType = IdType;
using EventManagerRef = std::shared_ptr<class EventManager>;
    
///COMPONENTS
    
using ComponentType = uint8_t;
using ComponentNameType = std::string;
using ComponentUId = IdType;
using ComponentBaseRef = std::shared_ptr< class ComponentBase >;
using TransformComponentRef = std::shared_ptr<class TransformComponent>;
using UpdatableComponentBaseRef = std::shared_ptr<class UpdatableComponentBase>;

///ACTORS
    
using ActorRef = std::shared_ptr< class Actor >;
using ActorWeakRef = std::weak_ptr< class Actor >;
using ActorId = IdType;
using ActorUId = IdType;
using ActorNameType = std::string;
using ActorType = std::string;
using ActorTypeQualifier = std::string;
    
///SCENE
    
using SceneRef = std::shared_ptr< class Scene>;
using SceneId = IdType;
using SceneWeakRef = std::weak_ptr< class Scene>;
using SceneFactoryRef = std::shared_ptr< class SceneFactory >;
    
///Events
    
using DestoryActorEventRef = std::shared_ptr< class DestoryActorEvent >;
using CreateActorEventRef = std::shared_ptr< class CreateActorEvent >;
using ReturnActorCreatedEventRef = std::shared_ptr< class ReturnActorCreatedEvent >;
using ReturnCameraActorCreatedEventRef = std::shared_ptr< class ReturnCameraActorCreatedEvent >;
using SceneUpdateEventRef = std::shared_ptr< class SceneUpdateEvent >;
using ScenePreDrawEventRef = std::shared_ptr< class ScenePreDrawEvent >;
using SceneDrawEventRef = std::shared_ptr< class SceneDrawEvent >;
using SceneChangeEventRef = std::shared_ptr< class SceneChangeEvent >;
using UpdateComponentsEventRef = std::shared_ptr< class UpdateComponentsEvent >;
using CullVisibleComponentsEventRef = std::shared_ptr< class CullVisibleComponentsEvent >;
using DrawVisibleComponentsEventRef = std::shared_ptr< class DrawVisibleComponentsEvent >;

///RENDERER
    
using RendererRef = std::shared_ptr< class Renderer >;
using GeomManagerRef = std::shared_ptr< class GeomManager >;

    
}