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
uniform vec3 uLightDir;\
\
attribute vec3 aNormal;\
\
void main() {\
	vec4 col = gl_Color;\
	float lightM = dot(uLightDir, normalize(aNormal));\
	lightM = (lightM+1.0)/2.0;\
	col = vec4(vec3(col)*clamp(lightM, 0.1, 1.0), col.a);\
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;\
	gl_FrontColor = col;\
}\
\
";

static const std::string terrainFragSrc = "\
\
void main() {\
	/* Set the fragment's final color */\
	gl_FragColor = gl_Color;\
}\
\
";