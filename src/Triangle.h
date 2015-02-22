//
//  Triangle.h
//  TriGen
//
//  Created by Quinn on 1/16/15.
//
//

#pragma once

#include "Vertex.h"

class Triangle {
public:
	Triangle(Vertex *v1, Vertex *v2, Vertex *v3, bool adjUpdate = true);
	~Triangle();
	
	// basic functions for mesh algorithms
	void flip(); // reverses the triangle's vertex order, flipping its normal
	void replaceVert(Vertex* oldV, Vertex* newV); // replaces the given vertex in this triangle
	Vertex* getThirdVert(Vertex* v1, Vertex* v2); // given two vertices in this triangle, gets the third
	Vertex* getNextVert(Vertex* v); // returns the next vertex, according to the winding order
	Vertex* getPrevVert(Vertex* v); // returns the previous vertex, according to the winding order
	bool hasVertex(Vertex* v); // returns true if the vertex is in this triangle
	bool areOrdered(Vertex* v1, Vertex* v2); // returns true if v2 comes after v1 in the winding order
	
	void updateNormal();
	
	void setItBefore(void* it);
	std::string str();
	
	Vertex *v1, *v2, *v3;
	vec3f normal;
	void* itBefore;
};

typedef std::forward_list<Triangle>::iterator triIt;
