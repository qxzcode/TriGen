//
//  Triangle.cpp
//  TriGen
//
//  Created by Quinn on 1/16/15.
//
//

#include "Triangle.h"

Triangle::Triangle(Vertex &v1, Vertex &v2, Vertex &v3):v1(v1),v2(v2),v3(v3) {
	updateNormal();
}

void Triangle::updateNormal() {
	normal = (v1.pos-v2.pos).cross(v1.pos-v3.pos).normalize();
}