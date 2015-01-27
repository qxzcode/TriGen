//
//  shaders.h
//  TriGen
//
//  Created by Quinn on 1/23/15.
//
//

#pragma once

#include "ShaderProgram.h"

namespace shaders {
	extern ShaderProgram terrain;
	extern GLint terrain_lightDir, terrain_normal;
	
	void loadShaders();
}