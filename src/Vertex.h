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
	void addTri(Triangle* t, Vertex* v);
	void removeTri(Triangle* t, Vertex* v);
	void replaceTri(Triangle* oldT, Triangle* newT);
	void replaceVert(Vertex* oldV, Vertex* newV);
	
	std::string str();
	
	vec3f pos;
	unsigned char valence;
	Triangle** aTris;
	Vertex** aVerts;
	
};