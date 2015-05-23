#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/Json.h"
#include "cinder/Log.h"

#include "Controller.h"
#include "Scenes.h"
#include "Components.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class System_testApp : public App {
  public:
	void setup() override;
	void mouseDown( MouseEvent event ) override;
    void keyUp( KeyEvent event ) override;
	void update() override;
	void draw() override;
    bool mDebug = false;
};

void System_testApp::setup()
{
    //configure system with my concrete scene factory and component factory
    ec::Controller::create( SceneFactory::create(), ComponentFactory::create() );
    //init system
    ec::Controller::get()->initialize( JsonTree( loadAsset("config.json") ) );
    
    gl::enableFaceCulling();
    gl::enableDepthRead();
    gl::enableDepthWrite();
    
}

void System_testApp::mouseDown( MouseEvent event )
{
}

void System_testApp::keyUp( KeyEvent event )
{
    mDebug = !mDebug;
    ec::Controller::get()->enableDebug( mDebug );
}

void System_testApp::update()
{
    ec::Controller::get()->update();
}

void System_testApp::draw()
{
    gl::clear( ColorA( 0,0,0,1 ) );
    ec::Controller::get()->draw();
}

void prepareSettings( App::Settings*settings )
{
    settings->setFullScreen();
}

CINDER_APP( System_testApp, RendererGl, prepareSettings )
