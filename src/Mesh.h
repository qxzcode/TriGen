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
#include "Vertex.h"

class Mesh {
public:
	Mesh();
	~Mesh();
	
	void updateGlMesh();
	void draw();
	
	// manipulation functions
	bool updateVert(Vertex* v);
	void flipEdge(Vertex* v1, Vertex* v2);
	void splitEdge(Vertex* v1, Vertex* v2);
	void collapseEdge(Vertex* v1, Vertex* v2);
	void getEdgeTris(Vertex* v1, Vertex* v2, Triangle** t1, Triangle** t2);
	Vertex* addVert(vec3f pos);
	Triangle* addTri(Vertex* v1, Vertex* v2, Vertex* v3);
	
protected:
	// geometry in ram
	std::forward_list<Triangle> triangles;
	std::forward_list<Vertex> vertices;
	
	// OpenGL buffer stuff
	GLuint meshBuf = 0;
	GLsizei numTriangles;
	
};