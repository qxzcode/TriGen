//
//  shader_terrain.h
//  TriGen
//
//  Created by Quinn on 1/23/15.
//
//

#pragma once

static const std::string terrainVertSrc = "\
\
attribute vec3 aNormal;\
\
varying vec3 vNormal;\
\
void main() {\
	vNormal = aNormal;\
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;\
	gl_FrontColor = gl_Color;\
}\
\
";

static const std::string terrainFragSrc = "\
\
uniform vec3 uLightDir;\
\
varying vec3 vNormal;\
\
void main() {\
	vec4 col = gl_Color;\
	float lightM = dot(uLightDir, normalize(vNormal));\
	lightM = (lightM+1.0)/2.0;\
	if (lightM < 0.0) lightM = 0.0;\
	float alpha = col.a;\
	col = col * lightM;\
	col.a = alpha;\
	\
	/* Set the fragment's final color */\
	gl_FragColor = col;\
}\
\
";