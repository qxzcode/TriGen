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

struct edgeData {
	edgeData(Vertex* v1, Vertex* v2);
	
	Vertex *v1, *v2, *v3, *v4;
	Triangle *t1, *t2;
	float lenSq;
};

class Mesh {
public:
	Mesh();
	~Mesh();
	
	void updateGlMesh();
	void draw();
	
	// manipulation functions
	void updateVert(Vertex* v);
	void flipEdge(edgeData edge);
	void splitEdge(edgeData edge);
	void collapseEdge(edgeData edge);
	Vertex* addVert(vec3f pos);
	Triangle* addTri(Vertex* v1, Vertex* v2, Vertex* v3, bool adjUpdate = true);
	
protected:
	// geometry in ram
	std::forward_list<Triangle> triangles;
	std::forward_list<Vertex> vertices;
	
	// OpenGL buffer stuff
	GLuint meshBuf = 0;
	GLsizei numTriangles;
	
};