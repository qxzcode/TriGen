//
//  Mesh.cpp
//  TriGen
//
//  Created by Quinn on 1/16/15.
//
//

#include "Mesh.h"

#include "shaders.h"

Mesh::Mesh() {
	// create a tetrahedron for testing
	Vertex* v1 = (vertices.emplace_front(vec3f(0,0,1)),&vertices.front());
	Vertex* v2 = (vertices.emplace_front(vec3f(1,0,0)),&vertices.front());
	Vertex* v3 = (vertices.emplace_front(vec3f(0,1,0)),&vertices.front());
	Vertex* v4 = (vertices.emplace_front(vec3f(0,0,0)),&vertices.front());
	triangles.emplace_front(Triangle(v1, v2, v3));
	triangles.emplace_front(Triangle(v4, v2, v1));
	triangles.emplace_front(Triangle(v4, v3, v2));
	triangles.emplace_front(Triangle(v4, v1, v3));
}

Mesh::~Mesh() {
	// be a responsible little programmer :)
	glDeleteBuffers(1, &meshBuf);
}

void Mesh::updateGlMesh() {
	// generate mesh data
	GLfloat buf[512*6];
	int bufI = 0;
	numTriangles = 0;
	for (Triangle& t : triangles) {
		buf[bufI++] = t.normal.x;
		buf[bufI++] = t.normal.y;
		buf[bufI++] = t.normal.z;
		buf[bufI++] = 0.0f;
		buf[bufI++] = 1.0f;
		buf[bufI++] = 0.0f;
		buf[bufI++] = t.v1->pos.x;
		buf[bufI++] = t.v1->pos.y;
		buf[bufI++] = t.v1->pos.z;
		buf[bufI++] = t.normal.x;
		buf[bufI++] = t.normal.y;
		buf[bufI++] = t.normal.z;
		buf[bufI++] = 0.0f;
		buf[bufI++] = 1.0f;
		buf[bufI++] = 0.0f;
		buf[bufI++] = t.v2->pos.x;
		buf[bufI++] = t.v2->pos.y;
		buf[bufI++] = t.v2->pos.z;
		buf[bufI++] = t.normal.x;
		buf[bufI++] = t.normal.y;
		buf[bufI++] = t.normal.z;
		buf[bufI++] = 0.0f;
		buf[bufI++] = 1.0f;
		buf[bufI++] = 0.0f;
		buf[bufI++] = t.v3->pos.x;
		buf[bufI++] = t.v3->pos.y;
		buf[bufI++] = t.v3->pos.z;
		numTriangles++;
	}
	
	// allocate buffer if needed
	if (!meshBuf)
		glGenBuffers(1, &meshBuf);
	
	// populate buffer
	glBindBuffer(GL_ARRAY_BUFFER, meshBuf);
	glBufferData(GL_ARRAY_BUFFER, bufI*sizeof(GLfloat), buf, GL_STATIC_READ);
}

void Mesh::draw() {
	glBindBuffer(GL_ARRAY_BUFFER, meshBuf);
	glVertexAttribPointer(shaders::terrain_normal, 3, GL_FLOAT, GL_FALSE, 9*sizeof(GL_FLOAT), (void*)0);
	glColorPointer(3, GL_FLOAT, 9*sizeof(GL_FLOAT), (void*)(3*sizeof(GL_FLOAT)));
	glVertexPointer(3, GL_FLOAT, 9*sizeof(GL_FLOAT), (void*)(6*sizeof(GL_FLOAT)));
	glDrawArrays(GL_TRIANGLES, 0, numTriangles*3);
}


// manipulation functions

void Mesh::flipEdge(Vertex* v1, Vertex* v2) {
	Vertex* v3 = /* todo */;
	Vertex* v4 = /* todo */;
	
	// TODO
}

// COULD USE SOME OPTIMIZATION
void Mesh::getEdgeTris(Vertex* v1, Vertex* v2, class Triangle** t1, Triangle** t2) {
	*t1 = NULL;
	
	
}






