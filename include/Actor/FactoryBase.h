//
//  FactoryBase.h
//  System_test
//
//  Created by Mike Allison on 4/30/15.
//
//

#pragma once

#include "Common.h"

namespace ec {
    
    class FactoryBase {
    public:
        virtual FactoryType getType() const = 0;
        virtual ~FactoryBase(){}
    };
    
}
