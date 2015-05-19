//
//  UpdateComponentBase.h
//  System_test
//
//  Created by Mike Allison on 5/5/15.
//
//

#pragma once
#include "Common.h"
#include "ComponentBase.h"

namespace ec {

    class UpdatableComponentBase : virtual public ComponentBase {
    
public:
        static ComponentType            TYPE;
        virtual void                    update( TimeStepType step ) = 0;
        
        virtual ~UpdatableComponentBase();

protected:
        
        UpdatableComponentBase();
        
        void handleUpdateComponent( EventDataRef );
        void handleSceneChange( EventDataRef );
        void registerHandler();
        
};

}