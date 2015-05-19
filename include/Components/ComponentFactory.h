//
//  ComponentFactory.h
//  System_test
//
//  Created by Mike Allison on 4/30/15.
//
//

#pragma once

#include "ComponentBase.h"
#include "cinder/Json.h"
#include "FactoryBase.h"
#include "Common.h"

namespace ec {
    
    class Actor;
    
    class ComponentFactory {
    public:
        
        virtual ComponentBaseRef createComponent( Actor* context, const ci::JsonTree& init ) = 0;
        
    };
    
}