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
	Vertex(vec3f pos):pos(pos) {}
	
	vec3f pos;
	
};