//
//  ConfigManager.h
//  System_test
//
//  Created by Mike Allison on 4/30/15.
//
//

#pragma once
#include "Manager.hpp"
#include "cinder/Json.h"
#include "Common.h"

namespace ec {

class ConfigManager {
  
public:
    
    static ConfigManagerRef create( const ci::JsonTree & master_config );
    static ConfigManagerRef get();
    
    const ci::JsonTree& retreive( const std::string& path = "" );
    const ci::JsonTree& retreiveActorsForScene( const std::string& scene_name );
    const ci::JsonTree& retreiveComponentsForActor( const std::string& scene_name, const std::string& actor_name );
    const ci::JsonTree& retreiveActorConfig( const std::string& scene_name, const std::string& actor_name );
    const ci::JsonTree& retreiveScene( const std::string& scene_name );
    const ci::JsonTree& retreiveComponent( const std::string& scene_name, const std::string& actor_name, const std::string &component_type );

    
private:
    
    ConfigManager( const ci::JsonTree & master_config );
    ci::JsonTree mConfig;
    
};
    
}