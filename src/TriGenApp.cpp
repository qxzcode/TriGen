#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "cinder/Camera.h"

using namespace ci;
using namespace ci::app;
using namespace std;

#include "Mesh.h"
#include "shaders.h"

class TriGenApp : public AppNative {
  public:
	void setup();
	void shutdown();
	void resize();
	void update();
	void draw();
	
	Mesh mesh;
	CameraPersp cam;
	float lastFrame;
	float rot = 0;
	
};

void TriGenApp::setup() {
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_CULL_FACE);
	
	cam.lookAt(Vec3f(0,3,3), Vec3f(0,0,0), Vec3f(0,1,0));
	
	shaders::loadShaders();
	mesh.updateGlMesh();
	
	lastFrame = getElapsedSeconds();
}

void TriGenApp::shutdown() {
	shaders::terrain.deleteProgram();
}

void TriGenApp::resize() {
	cam.setPerspective(45.0f, getWindowAspectRatio(), 0.1f, 1000.0f);
}

void TriGenApp::update() {
	float curTime = getElapsedSeconds();
	float dt = curTime - lastFrame;
	lastFrame = curTime;
	
	rot += 90.0f*dt;
	glUniform3f(shaders::terrain_lightDir, 0, 0.707, 0.707);
}

void TriGenApp::draw() {
	// prepare for drawing
	gl::clear(Color(1, 0.5, 0));
	gl::setMatrices(cam);
	shaders::terrain.useProgram();
	glRotatef(rot, 0, 1, 0);
	
	// draw mesh
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableVertexAttribArray(shaders::terrain_normal);
	mesh.draw();
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableVertexAttribArray(shaders::terrain_normal);
}

CINDER_APP_NATIVE( TriGenApp, RendererGl(RendererGl::AA_NONE) )
