//
//  ConfigManager.cpp
//  System_test
//
//  Created by Mike Allison on 4/30/15.
//
//

#include "ConfigManager.h"
#include "cinder/Log.h"

namespace ec {
    
    static ConfigManagerRef sConfigManager = nullptr;
    
    ConfigManagerRef ConfigManager::create( const ci::JsonTree & master_config )
    {
        sConfigManager = ConfigManagerRef( new ConfigManager( master_config ) );
        return sConfigManager;
    }
    ConfigManagerRef ConfigManager::get()
    {
        CI_ASSERT(sConfigManager);
        return sConfigManager;
    }
    
    ConfigManager::ConfigManager( const ci::JsonTree & master_config ):mConfig(master_config)
    {
        
     

    }
    
    const ci::JsonTree& ConfigManager::retreiveScene( const std::string& scene_name )
    {
        try {
            
            auto & scenes = mConfig["scenes"].getChildren();
            
            for( auto & scene : scenes ){
                if( scene.getValueForKey("name") == scene_name) return scene;
            }
            
        }catch( const ci::JsonTree::ExcChildNotFound &e )
        {
            CI_LOG_E( e.what() );
        }
        
        return ci::JsonTree();
    }

    
    const ci::JsonTree& ConfigManager::retreive(const std::string &path)
    {
        try {
            return mConfig[path];
        }catch( const ci::JsonTree::ExcChildNotFound &e )
        {
            CI_LOG_E( e.what() );
        }
        
        return ci::JsonTree();
    }
    
    const ci::JsonTree& ConfigManager::retreiveActorsForScene( const std::string& scene_name )
    {
        try {
            
            auto & scenes = mConfig["scenes"].getChildren();
            
            for( auto & scene : scenes ){
                if( scene.getValueForKey("name") == scene_name) return scene["actors"];
            }
            
        }catch( const ci::JsonTree::ExcChildNotFound &e )
        {
            CI_LOG_E( e.what() );
        }
        
        return ci::JsonTree();
    }
    const ci::JsonTree& ConfigManager::retreiveComponentsForActor( const std::string& scene_name, const std::string& actor_name )
    {
        try {
            
            auto & scenes = mConfig["scenes"].getChildren();
            
            for( auto & scene : scenes ){
                if( scene.getValueForKey("name") == scene_name){
                    
                    auto & actors = scene["actors"].getChildren();
                    for( auto & actor : actors ){
                        if( actor.getValueForKey("name") == actor_name) return actor["components"];
                    }
                    
                }
            }
            
        }catch( const ci::JsonTree::ExcChildNotFound &e )
        {
            CI_LOG_E( e.what() );
        }
        
        return ci::JsonTree();
    }

    const ci::JsonTree& ConfigManager::retreiveActorConfig( const std::string& scene_name, const std::string& actor_name )
    {
        try {
            
            auto & scenes = mConfig["scenes"].getChildren();
            
            for( auto & scene : scenes ){
                if( scene.getValueForKey("name") == scene_name){
                    
                    auto & actors = scene["actors"].getChildren();
                    for( auto & actor : actors ){
                        auto actor_tmp = actor.getValueForKey("name");
                        if( actor_tmp == actor_name){
                            return actor;
                        }
                    }
                    
                }
            }
            
        }catch( const ci::JsonTree::ExcChildNotFound &e )
        {
            CI_LOG_E( e.what() );
        }
        
        return ci::JsonTree();
    }

}