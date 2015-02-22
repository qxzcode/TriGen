//
//  Triangle.cpp
//  TriGen
//
//  Created by Quinn on 1/16/15.
//
//

#include "Triangle.h"

#include <string>

Triangle::Triangle(Vertex *v1, Vertex *v2, Vertex *v3, bool adjUpdate):v1(v1),v2(v2),v3(v3),itBefore(NULL) {
	if (adjUpdate) {
		v1->addTri(this);
		v2->addTri(this);
		v3->addTri(this);
	}
	updateNormal();
}

Triangle::~Triangle() {
	setItBefore(NULL);
}

void Triangle::setItBefore(void* it) {
	delete (triIt*)itBefore;
	itBefore = it;
}

void Triangle::flip() {
	// reverse vertex winding order, and negate normal vector
	Vertex *tmp = v1;
	v1 = v3;
	v3 = tmp;
	normal = -normal;
}

void Triangle::replaceVert(Vertex* oldV, Vertex* newV) {
	if (v1==oldV)
		v1 = newV;
	else if (v2==oldV)
		v2 = newV;
	else
		v3 = newV;
	updateNormal();
}

Vertex* Triangle::getThirdVert(Vertex* vv1, Vertex* vv2) {
	if (v1!=vv1 && v1!=vv2)
		return v1;
	else if (v2!=vv1 && v2!=vv2)
		return v2;
	else
		return v3;
}

Vertex* Triangle::getNextVert(Vertex* v) {
	if (v == v1)
		return v2;
	else if (v == v2)
		return v3;
	else
		return v1;
}

Vertex* Triangle::getPrevVert(Vertex* v) {
	if (v == v1)
		return v3;
	else if (v == v2)
		return v1;
	else
		return v2;
}

bool Triangle::hasVertex(Vertex* v) {
	return v1==v || v2==v || v3==v;
}

bool Triangle::areOrdered(Vertex* vv1, Vertex* vv2) {
	return getNextVert(vv1) == vv2;
}

void Triangle::updateNormal() {
	normal = (v1->pos-v2->pos).cross(v1->pos-v3->pos).normalize();
}

std::string Triangle::str() {
	return "["+v1->str()+", "+v2->str()+", "+v3->str()+"]";
}

