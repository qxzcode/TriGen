//
//  Vertex.cpp
//  TriGen
//
//  Created by Quinn on 1/16/15.
//
//

#include "Vertex.h"

#include "Triangle.h"

Vertex::Vertex(vec3f pos):pos(pos),valence(0),aTris(NULL),aVerts(NULL) {
	
}

Vertex::~Vertex() {
	delete[] aTris;
	delete[] aVerts;
}

//Writing add/remove vert/tri functions of Vertex

void Vertex::addTri(Triangle* t) {
	Triangle** oldTris = aTris;
	aTris = new Triangle*[++valence];
}

void Vertex::edgeTris(Vertex* v1, Vertex* v2, class Triangle** t1, Triangle** t2) {
	// TODO
}