//
//  Triangle.cpp
//  TriGen
//
//  Created by Quinn on 1/16/15.
//∫
//

#include "Triangle.h"

Triangle::Triangle(Vertex *v1, Vertex *v2, Vertex *v3):v1(v1),v2(v2),v3(v3) {
	v1->addTri(this);
	v2->addTri(this);
	v3->addTri(this);
	updateNormal();
}

void Triangle::flip() {
	// reverse vertex winding order, and negate normal vector
	Vertex *tmp = v1;
	v1 = v3;
	v3 = tmp;
	normal = -normal;
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

void Triangle::updateNormal() {
	normal = (v1->pos-v2->pos).cross(v1->pos-v3->pos).normalize();
}