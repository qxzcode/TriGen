//
//  Vertex.cpp
//  TriGen
//
//  Created by Quinn on 1/16/15.
//
//

#include "Vertex.h"

#include "Triangle.h"
#include <string>

Vertex::Vertex(vec3f pos):pos(pos),valence(0),aTris(NULL),aVerts(NULL) {
	
}

Vertex::~Vertex() {
	delete[] aTris;
	delete[] aVerts;
}

void Vertex::addTri(Triangle* t) {
	addTri(t, t->getNextVert(this));
}

void Vertex::addTri(Triangle* t, Vertex* v) {
	Triangle** oldTris = aTris;
	Vertex** oldVerts = aVerts;
	aTris = new Triangle*[valence+1];
	aVerts = new Vertex*[valence+1];
	for (int i = 0; i < valence; i++) {
		aTris[i] = oldTris[i];
		aVerts[i] = oldVerts[i];
	}
	aTris[valence] = t;
	aVerts[valence] = v;
	valence++;
	delete[] oldTris;
	delete[] oldVerts;
}

void Vertex::removeTri(Triangle* t, Vertex* v) {
	Triangle** oldTris = aTris;
	Vertex** oldVerts = aVerts;
	aTris = new Triangle*[valence-1];
	aVerts = new Vertex*[valence-1];
	for (int i = 0, ti = 0, vi = 0; i < valence; i++) {
		if (oldTris[i] != t)
			aTris[ti++] = oldTris[i];
		if (oldVerts[i] != v )
			aVerts[vi++] = oldVerts[i];
	}
	valence--;
	delete[] oldTris;
	delete[] oldVerts;
}

void Vertex::replaceTri(Triangle* oldT, Triangle* newT) {
	for (int i = 0; i < valence; i++) {
		if (aTris[i] == oldT) {
			aTris[i] = newT;
			break;
		}
	}
}

void Vertex::replaceVert(Vertex* oldV, Vertex* newV) {
	for (int i = 0; i < valence; i++) {
		if (aVerts[i] == oldV) {
			aVerts[i] = newV;
			break;
		}
	}
}

std::string Vertex::str() {
	return "("+std::to_string(pos.x)+","+std::to_string(pos.y)+","+std::to_string(pos.z)+")";
}

