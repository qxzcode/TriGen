//
//  vec3.h
//  TriGen
//
//  Created by Quinn on 1/16/15.
//
//

#pragma once

#include <math.h>

struct vec3f {
	vec3f():x(0),y(0),z(0) {}
	vec3f(float x, float y, float z):x(x),y(y),z(z) {}
	
	float x, y, z;
	
	vec3f operator-() const {
		return vec3f(-x,-y,-z);
	}
	vec3f operator+(const vec3f& v) const {
		return vec3f(x+v.x,y+v.y,z+v.z);
	}
	vec3f operator-(const vec3f& v) const {
		return vec3f(x-v.x,y-v.y,z-v.z);
	}
	vec3f operator*(const float& f) const {
		return vec3f(x*f,y*f,z*f);
	}
	vec3f operator/(const float& f) const {
		return vec3f(x/f,y/f,z/f);
	}
	float len() const {
		return sqrtf(x*x + y*y + z*z);
	}
	float lenSq() const {
		return x*x + y*y + z*z;
	}
	vec3f normalize() const {
		float len = this->len();
		if (len == 0) return vec3f();
		return *this/len;
	}
	float dot(const vec3f& v) const {
		return x*v.x + y*v.y + z*v.z;
	}
	vec3f cross(const vec3f& v) const {
		return vec3f(y*v.z-z*v.y, z*v.x-x*v.z, x*v.y-y*v.x);
	}
};