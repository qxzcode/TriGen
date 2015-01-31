//
//  Mesh.cpp
//  TriGen
//
//  Created by Quinn on 1/16/15.
//
//

#include "Mesh.h"

#include "shaders.h"
#include "mesh_params.h"

Mesh::Mesh() {
	// create a tetrahedron for testing
	Vertex* v1 = (vertices.emplace_front(vec3f(0,0,1)),&vertices.front());
	Vertex* v2 = (vertices.emplace_front(vec3f(1,0,0)),&vertices.front());
	Vertex* v3 = (vertices.emplace_front(vec3f(0,1,0)),&vertices.front());
	Vertex* v4 = (vertices.emplace_front(vec3f(0,0,0)),&vertices.front());
	triangles.emplace_front(v1, v2, v3);
	triangles.emplace_front(v4, v2, v1);
	triangles.emplace_front(v4, v3, v2);
	triangles.emplace_front(v4, v1, v3);
	
	updateVert(v1);
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

bool Mesh::updateVert(Vertex* v) {
	// find longest edge
	float len = MAXFLOAT;
	Vertex* v2;
	for (int i = 0; i < v->valence; i++) {
		float l = (v->pos - v->aVerts[i]->pos).lenSq();
		if (l > len) {
			len = l;
			v2 = v->aVerts[i];
		}
	}
	
	// check against thresholds
	if (len > MAX_EDGE_LEN*MAX_EDGE_LEN) {
		splitEdge(v, v2);
		return true;
	} else if (len < MIN_EDGE_LEN*MIN_EDGE_LEN) {
		collapseEdge(v, v2);
		return true;
	} else {
		return false;
	}
	
	// TODO: valence regularization via flipEdge
	// TODO: vertex relocation via ...?
}

void Mesh::flipEdge(Vertex* v1, Vertex* v2) {
	// get the two other vertices & triangles involved
	Triangle *t1, *t2;
	getEdgeTris(v1, v2, &t1, &t2);
	Vertex* v3 = t1->getThirdVert(v1, v2);
	Vertex* v4 = t2->getThirdVert(v1, v2);
	
	// assign the triangles new vertices and update their normals
	if (t1->areOrdered(v1, v2)) {
		t1->v2 = v4; t1->v3 = v3;
		t2->v2 = v3; t2->v3 = v4;
	} else {
		t1->v2 = v3; t1->v3 = v4;
		t2->v2 = v4; t2->v3 = v3;
	}
	t1->v1 = v1;
	t2->v1 = v2;
	t1->updateNormal();
	t2->updateNormal();
	
	// update adjacency information
	v1->removeTri(t2, v2);
	v2->removeTri(t1, v1);
	v3->addTri(t2, v4);
	v4->addTri(t1, v3);
}

void Mesh::splitEdge(Vertex* v1, Vertex* v2) {
	// get the two other vertices & triangles involved
	Triangle *t1, *t2;
	getEdgeTris(v1, v2, &t1, &t2);
	Vertex* v3 = t1->getThirdVert(v1, v2);
	Vertex* v4 = t2->getThirdVert(v1, v2);
	
	// create the new vertex & two new triangles
	Triangle* t3 = (triangles.emplace_front(/*...*/),&triangles.front());
	Triangle* t4 = (triangles.emplace_front(/*...*/),&triangles.front());
	
	// update adjacency information
	//...
}

// COULD USE SOME OPTIMIZATION (MAYBE)
void Mesh::getEdgeTris(Vertex* v1, Vertex* v2, Triangle** t1, Triangle** t2) {
	*t1 = *t2 = NULL;
	for (int i = 0; i < v1->valence; i++) {
		Triangle* t = v1->aTris[i];
		if (t->hasVertex(v2)) {
			if (!*t1) {
				*t1 = t;
			} else {
				*t2 = t;
				return;
			}
		}
	}
	printf("Couldn't find two edge triangles\n");
}






