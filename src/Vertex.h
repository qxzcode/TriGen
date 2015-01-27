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
	void addTri(Triangle* t);
	void removeTri(Triangle* t);
	void addVert(Vertex* v);
	void removeVert(Vertex* v);
	bool onUpdate(class Mesh* mesh);
	static void edgeTris(Vertex* v1, Vertex* v2, Triangle** t1, Triangle** t2);
	
	vec3f pos;
	unsigned char valence;
	Triangle** aTris;
	Vertex** aVerts;
	
};