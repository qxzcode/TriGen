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
	Vertex* v1 = addVert(vec3f(0,0,1));
	Vertex* v2 = addVert(vec3f(1,0,0));
	Vertex* v3 = addVert(vec3f(0,1,0));
	Vertex* v4 = addVert(vec3f(0,0,0));
	addTri(v1, v2, v3);
	addTri(v4, v2, v1);
	addTri(v4, v3, v2);
	addTri(v4, v1, v3);
	
	for (int n = 0; n < 10; n++) {
//		for (Vertex &v : vertices) {
//			updateVert(&v);
//		}
		updateVert(v1);
	}
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

edgeData::edgeData(Vertex* v1, Vertex* v2):v1(v1),v2(v2) {
	// COULD USE SOME OPTIMIZATION (MAYBE)
	t1 = t2 = NULL;
	for (int i = 0; i < v1->valence; i++) {
		Triangle* t = v1->aTris[i];
		if (t->hasVertex(v2)) {
			if (!t1) {
				t1 = t;
			} else {
				t2 = t;
				break;
			}
		}
	}
	if (!t2) printf("Couldn't find %s edge triangles\n", t1? "two" : "any");
	v3 = t1->getThirdVert(v1, v2);
	v4 = t2->getThirdVert(v1, v2);
	lenSq = (v1->pos - v2->pos).lenSq();
}

void Mesh::updateVert(Vertex* v) {
	// loop through adjacent edges until no more updates are needed
	bool done;
	do {
		done = true;
		for (int i = 0; i < v->valence; i++) {
			Vertex* v2 = v->aVerts[i];
			edgeData edge(v, v2);
			
			// check against thresholds
			if (edge.lenSq > MAX_EDGE_LEN_SQ) { // split if longer than upper threshold
				splitEdge(edge);
				done = false; break;
			} else if (edge.lenSq < MIN_EDGE_LEN_SQ) { // collapse if shorter than lower threshold
				collapseEdge(edge);
				done = false; break;
			}
			
			// TODO: valence regularization via flipEdge
			// TODO: vertex relocation via ...?
		}
	} while (!done);
	
	
}

void Mesh::flipEdge(edgeData edge) {
	// get the two other vertices & triangles involved
	Triangle *t1 = edge.t1, *t2 = edge.t2;
	Vertex *v1 = edge.v1, *v2 = edge.v2, *v3 = edge.v3, *v4 = edge.v4;
	
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

void Mesh::splitEdge(edgeData edge) {
	// get the two other vertices & triangles involved
	Triangle *t1 = edge.t1, *t2 = edge.t2;
	Vertex *v1 = edge.v1, *v2 = edge.v2, *v3 = edge.v3, *v4 = edge.v4;
	
	// create the new vertex & two new triangles
	Vertex* v5 = addVert((v1->pos+v2->pos)/2 + (t1->normal+t2->normal).normalize()*0.3f);
	Triangle* t3;
	Triangle* t4;
	if (t1->areOrdered(v1, v2)) {
		t3 = addTri(v2, v3, v5, false);
		t4 = addTri(v2, v5, v4, false);
	} else {
		t3 = addTri(v2, v5, v3, false);
		t4 = addTri(v2, v4, v5, false);
	}
	
	// update adjacency information
	t1->replaceVert(v2, v5);
	t2->replaceVert(v2, v5);
	v1->replaceVert(v2, v5);
	v2->replaceVert(v1, v5);
	v2->replaceTri(t1, t3);
	v2->replaceTri(t2, t4);
	v3->addTri(t3, v5);
	v4->addTri(t4, v5);
	v5->addTri(t1, v1);
	v5->addTri(t2, v2);
	v5->addTri(t3, v3);
	v5->addTri(t4, v4);
}

void Mesh::collapseEdge(edgeData edge) {
	// get the two other vertices & triangles involved
	Triangle *t1 = edge.t1, *t2 = edge.t2;
	Vertex *v1 = edge.v1, *v2 = edge.v2, *v3 = edge.v3, *v4 = edge.v4;
	
	//...
}

Vertex* Mesh::addVert(vec3f pos) {
	vertices.emplace_front(pos);
	return &vertices.front();
}

Triangle* Mesh::addTri(Vertex* v1, Vertex* v2, Vertex* v3, bool adjUpdate) {
	triangles.emplace_front(v1, v2, v3, adjUpdate);
	return &triangles.front();
}






