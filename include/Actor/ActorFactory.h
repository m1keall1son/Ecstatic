//
//  ActorFactory.h
//  System_test
//
//  Created by Mike Allison on 4/29/15.
//
//

#pragma once

#include "Actor.h"
#include "cinder/Json.h"
#include "FactoryBase.h"

namespace ec {

    class ActorFactory : public FactoryBase {
    public:
        
        static FactoryType TYPE;
        
        static ActorFactoryRef get();
        
        FactoryType getType() const override;
        ActorRef createActor( const ci::JsonTree& init );
        
        ActorFactory( const ActorFactory & ) = delete;
        ActorFactory( ActorFactory&& ) = delete;
        ActorFactory& operator=( const ActorFactory & ) = delete;
        ActorFactory& operator=( ActorFactory&& ) = delete;
        
        ~ActorFactory(){}
        
    private:
        
        ActorFactory();
        
    };
    
}