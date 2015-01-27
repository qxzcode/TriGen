//
//  shaders.cpp
//  TriGen
//
//  Created by Quinn on 1/23/15.
//
//

#include "shaders.h"

#include "shader_terrain.h"

ShaderProgram shaders::terrain;
GLint shaders::terrain_lightDir, shaders::terrain_normal;

void shaders::loadShaders() {
	terrain.newProgram(terrainVertSrc, terrainFragSrc);
	terrain_lightDir = glGetUniformLocation(terrain.progObj, "uLightDir");
	terrain_normal = glGetAttribLocation(terrain.progObj, "aNormal");
}