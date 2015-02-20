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
	
	// misc
	int valExcess(int off=0) {
		int v = valence+off - 6;
		return v*v;
	}
	std::string str();
	
	vec3f pos;
#ifdef DEBUG
	unsigned short // makes values easier to read in the debugger
#else
	unsigned char  // saves a bit of memory
#endif
	valence;
	Triangle** aTris;
	Vertex** aVerts;
	
};