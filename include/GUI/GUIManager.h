//
//  GUIManager.h
//  Kinect_Component_test
//
//  Created by Mike Allison on 5/26/15.
//
//

#pragma once
#include "Common.h"
#include "cinder/params/Params.h"

namespace ec {
    
class GUIManager : public std::enable_shared_from_this<GUIManager> {
    
public:
    
    using SubGuiSet = std::map< IdType, ci::params::InterfaceGlRef >;
    
    static GUIManagerRef create();
    
    void instertGUI( const IdType& _id, const ci::params::InterfaceGlRef &gui );
    ci::params::InterfaceGlRef findGUI( const IdType& _id );
    
    void removeGUI( const IdType& _id );
    void removeGUIs( const std::vector<IdType>& _ids );

    void postInit();
    void draw();
    
    void handleUninit( EventDataRef );
    
    void enableGUI( bool enable = true );
    
    ~GUIManager();
    
protected:
    
    GUIManager();
    
    
    ci::params::InterfaceGlRef mMainGUI;
    SubGuiSet mSubGUIs;
    
};
    
}

