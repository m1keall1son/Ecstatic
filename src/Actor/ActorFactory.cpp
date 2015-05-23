//
//  ActorFactory.cpp
//  System_test
//
//  Created by Mike Allison on 4/29/15.
//
//

#include "ActorFactory.h"
#include "cinder/Log.h"
#include "ComponentFactory.h"
#include "Controller.h"
#include "EventManager.h"
#include "SystemEvents.h"
#include "Scene.h"


namespace ec {
    
    static ActorFactoryRef sActorFactory = nullptr;
    
    FactoryType ActorFactory::TYPE = getHash("ActorFactory");
    
    ActorFactoryRef ActorFactory::get()
    {
        if(!sActorFactory){
            sActorFactory = ActorFactoryRef( new ActorFactory );
        }
        return sActorFactory;
    }
    
    ActorFactory::ActorFactory()
    {
        //nothing?
    }
    
    FactoryType ActorFactory::getType() const
    {
        return TYPE;
    }
    
    ActorRef ActorFactory::createActor( const ci::JsonTree& init )
    {
        
        ActorRef actor;
        
        std::string name, type, type_qualifier;
        bool active, persistent;
        
        try {
             name = init["name"].getValue<std::string>();
             type = init["type"].getValue<std::string>();
             type_qualifier = init["type_qualifier"].getValue<std::string>();
             active = init["active"].getValue<bool>();
             persistent = init["persistent"].getValue<bool>();

            ///TODO: decide how to activate
            
        } catch ( const ci::JsonTree::ExcChildNotFound &ex	) {
            CI_LOG_E(ex.what());
            CI_LOG_E("actor name not found");
        }
        
        actor = ActorRef( new Actor( name, type, type_qualifier, active, persistent ) );

        
        try {
   
            auto & components = init["components"].getChildren();
            auto end = components.end();
        
            for( auto compIt = components.begin(); compIt != end; ++compIt ) {
                ComponentBaseRef component;
                component = Controller::get()->componentFactory()->createComponent( actor.get(), *compIt );
                actor->mComponents.insert( std::make_pair( component->getType(), component ));
            }
            
        } catch ( const ci::JsonTree::ExcChildNotFound &ex	) {
            CI_LOG_E(ex.what());
            CI_LOG_E("components not found");
        }
    
        return actor;
    }

}