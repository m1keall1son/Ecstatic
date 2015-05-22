//
//  AppCommon.h
//  System_test
//
//  Created by Mike Allison on 5/21/15.
//
//

#pragma once

///SCENES

using SceneFactoryRef = std::shared_ptr<class SceneFactory>;
using IntroSceneRef = std::shared_ptr<class IntroScene>;

///COMPONENTS

using ComponentFactoryRef = std::shared_ptr<class ComponentFactory>;
using FrustumCullComponentRef = std::shared_ptr< class FrustumCullComponent >;

///CAMERAS
using CameraManagerRef = std::shared_ptr< class CameraManager >;
using CameraComponentRef = std::shared_ptr< class CameraComponent >;

///LIGHTS

using LightManagerRef = std::shared_ptr< class LightManager >;
using LightComponentBaseRef = std::shared_ptr< class LightComponentBase >;
using DynamicLightComponentRef = std::shared_ptr< class DynamicLightComponent >;
using StaticLightComponentRef = std::shared_ptr< class StaticLightComponent >;
using ShadowLightComponentRef = std::shared_ptr< class ShadowLightComponent >;

///RENDERABLE

using GeomTeapotRef = std::shared_ptr< class GeomTeapot >;

///App EVENTS

using RegisterCameraEventRef = std::shared_ptr<class RegisterCameraEvent>;
