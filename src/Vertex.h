//
//  Vertex.h
//  TriGen
//
//  Created by Quinn on 1/16/15.
//
//

#pragma once

#include "vec3.h"

class Triangle;

class Vertex {
public:
	Vertex(vec3f pos);
	~Vertex();
	
	// functions for manipulation and stuff
	void addTri(Triangle* t) { addTri(t, t->getNextVert(this)); }
	void addTri(Triangle* t, Vertex* v);
	void removeTri(Triangle* t, Vertex* v);
	bool onUpdate(class Mesh* mesh);
	
	vec3f pos;
	unsigned char valence;
	Triangle** aTris;
	Vertex** aVerts;
	
};