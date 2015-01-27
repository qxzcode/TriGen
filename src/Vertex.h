//
//  Vertex.h
//  TriGen
//
//  Created by Quinn on 1/16/15.
//
//

#pragma once

#include "vec3.h"

class Vertex {
public:
	Vertex(vec3f pos):pos(pos),valence(0) {}
	
	// functions for manipulation and stuff
	bool onUpdate(class Mesh* mesh);
	static void edgeTris(Vertex* v1, Vertex* v2, class Triangle** t1, Triangle** t2);
	
	vec3f pos;
	unsigned char valence;
	
};