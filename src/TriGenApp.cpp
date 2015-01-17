#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class TriGenApp : public AppNative {
  public:
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
};

void TriGenApp::setup()
{
}

void TriGenApp::mouseDown( MouseEvent event )
{
}

void TriGenApp::update()
{
}

void TriGenApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) ); 
}

CINDER_APP_NATIVE( TriGenApp, RendererGl )
