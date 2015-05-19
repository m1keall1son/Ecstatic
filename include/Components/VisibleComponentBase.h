//
//  VisibleComponentBase.h
//  System_test
//
//  Created by Mike Allison on 5/18/15.
//
//

#pragma once
#include "Common.h"
#include "ComponentBase.h"

namespace ec {
    
    class CullableComponentBase : virtual public ComponentBase {
        
    public:
        
        static  ComponentType           TYPE;
        inline  bool                    isVisible(){ return mIsVisible; }
        virtual bool                    cull() = 0;
        
        virtual ~CullableComponentBase();
        
    protected:
        
        CullableComponentBase();
        
        void handleCulling( EventDataRef );
        void handleSceneChange( EventDataRef );
        void registerHandler();
        
    private:
        
        bool mIsVisible;
        
    };
    
}
