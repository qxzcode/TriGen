//
//  Mesh.h
//  TriGen
//
//  Created by Quinn on 1/16/15.
//
//

#pragma once

#include <OpenGL/gl.h>
#include <forward_list>

#include "Triangle.h"

class Mesh {
public:
	Mesh();
	~Mesh();
	
	void updateGlMesh();
	void draw();
	
protected:
	// geometry in ram
	std::forward_list<Triangle> triangles;
	std::forward_list<Vertex> vertices;
	
	// OpenGL buffer stuff
	GLuint meshBuf = 0;
	GLsizei numTriangles;
	
};