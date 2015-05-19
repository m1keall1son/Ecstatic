//
//  SceneFactory.h
//  System_test
//
//  Created by Mike Allison on 5/18/15.
//
//

#pragma once 
#include "Common.h"
#include "cinder/Json.h"

namespace ec {

class SceneFactory {
    
public:
    
    virtual SceneRef createScene( const ci::JsonTree& init ) = 0;
    
};

}