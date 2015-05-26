//
//  ComponentBase.h
//  System_test
//
//  Created by Mike Allison on 4/29/15.
//
//

#pragma once
#include "Common.h"
#include "cinder/Json.h"
#include "cinder/params/Params.h"

namespace ec {

class Actor;
    
class ComponentBase {
    
public:
    
    ComponentBase( Actor* context );
    
    ComponentBase( const ComponentBase & ) = delete;
    ComponentBase( ComponentBase&& ) = delete;
    ComponentBase& operator=( const ComponentBase & ) = delete;
    ComponentBase& operator=( ComponentBase&& ) = delete;
    
    virtual bool                initialize( const ci::JsonTree &tree ) = 0;
    virtual bool                postInit() = 0;
    virtual ci::JsonTree        serialize() = 0;
    virtual void                loadGUI( const ci::params::InterfaceGlRef &gui ) = 0;

    virtual const ComponentNameType   getName() const = 0;
    virtual const ComponentUId        getId() const = 0;
    virtual const ComponentType       getType() const = 0;
        
    virtual ~ComponentBase(){}
    
protected:
    
    Actor* mContext;
    
};

}