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

// Writing add/remove vert/tri functions of Vertex

void Vertex::addTri(Triangle* t) {
	Triangle** oldTris = aTris;
	Vertex** oldVerts = aVerts;
	aTris = new Triangle*[valence+1];
	aVerts = new Vertex*[valence+1];
	for (int i = 0; i < valence; i++) {
		aTris[i] = oldTris[i];
		aVerts[i] = oldVerts[i];
	}
	aTris[valence] = t;
	aVerts[valence] = t->getNextVert(this);
	valence++;
	delete[] oldTris;
	delete[] oldVerts;
}

