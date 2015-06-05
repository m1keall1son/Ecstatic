//
//  GUIManager.cpp
//  Kinect_Component_test
//
//  Created by Mike Allison on 5/26/15.
//
//

#include "GUIManager.h"
#include "Controller.h"
#include "EventManager.h"
#include "cinder/Log.h"

namespace ec {
    
    GUIManagerRef GUIManager::create()
    {
        return GUIManagerRef( new GUIManager );
    }
    
    GUIManager::GUIManager()
    {
        mMainGUI = ci::params::InterfaceGl::create(ci::app::getWindow(), "Main GUI", ci::vec2(200,300));
    }
    
    GUIManager::~GUIManager()
    {
    }
    
    void GUIManager::instertGUI(const IdType &_id, const ci::params::InterfaceGlRef &gui)
    {
        mSubGUIs.insert( std::make_pair( _id, gui ) );
    }
    
    ci::params::InterfaceGlRef GUIManager::findGUI( const IdType& _id )
    {
        auto found = mSubGUIs.find(_id);
        if(found != mSubGUIs.end())return found->second;
        else{
            CI_LOG_E("GUI NOT FOUND");
            return nullptr;
        }
    }
    
    void GUIManager::removeGUI( const IdType& _id )
    {
        if( mSubGUIs.find(_id) != mSubGUIs.end() )mSubGUIs.erase(_id);
    }
    void GUIManager::removeGUIs( const std::vector<IdType>& _ids )
    {
        for(auto & _id : _ids){
            if( mSubGUIs.find(_id) != mSubGUIs.end() )mSubGUIs.erase(_id);
        }
    }
    
    void GUIManager::handleSceneChange(ec::EventDataRef)
    {
        mMainGUI->clear();
        ec::Controller::get()->eventManager()->triggerEvent(InitGUIEvent::create( this ));
        enableGUI(false);
    }
    
    void GUIManager::postInit()
    {
        mMainGUI->clear();
        ec::Controller::get()->eventManager()->triggerEvent(InitGUIEvent::create( this ));
    }
    void GUIManager::draw()
    {
        if(mMainGUI)
            mMainGUI->draw();
        for(auto&gui:mSubGUIs)gui.second->draw();
    }
    
    void GUIManager::handleUninit(EventDataRef event)
    {
        auto e = std::dynamic_pointer_cast<UninitGUIEvent>(event);
        for(auto & _id : e->getIds()){
            if( mSubGUIs.find(_id) != mSubGUIs.end() )mSubGUIs.erase(_id);
        }
    }
    
    void GUIManager::clear()
    {
        mSubGUIs.clear();
    }
    
    void GUIManager::enableGUI(bool enable)
    {
        if(enable){
            if(mMainGUI)
                mMainGUI->show();
            for(auto gui : mSubGUIs)gui.second->show();
        }
        else
        {
            if(mMainGUI)
                mMainGUI->hide();
            for(auto gui : mSubGUIs)gui.second->hide();
        }
    }
    
}
