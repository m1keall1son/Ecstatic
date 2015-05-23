//
//  RenderableComponentBase.h
//  System_test
//
//  Created by Mike Allison on 5/18/15.
//
//

#pragma once
#include "Common.h"
#include "ComponentBase.h"
#include "VisibleComponentBase.h"
#include "TransformComponent.h"
#include "UpdatableComponentBase.h"

namespace ec {
    
    class RenderableComponentBase : public UpdatableComponentBase {
        
    public:
        
        static  ComponentType           TYPE;
        virtual void                    draw() = 0;
        
        virtual ~RenderableComponentBase();
        
    protected:
        
        RenderableComponentBase( Actor * context );
        
        void handleDraw( EventDataRef );
        void handleSceneChange( EventDataRef );
        void registerHandler();
        
    };
    
}
