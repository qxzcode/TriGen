//
//  Triangle.cpp
//  TriGen
//
//  Created by Quinn on 1/16/15.
//
//

#include "Triangle.h"

Triangle::Triangle(Vertex *v1, Vertex *v2, Vertex *v3):v1(v1),v2(v2),v3(v3) {
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

void Triangle::updateNormal() {
	normal = (v1->pos-v2->pos).cross(v1->pos-v3->pos).normalize();
}