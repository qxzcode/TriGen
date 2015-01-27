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
	Triangle(Vertex &v1, Vertex &v2, Vertex &v3);
	
	void updateNormal();
	
	Vertex &v1, &v2, &v3;
	vec3f normal;
};