#pragma once	
#include "Vec3.h"

vec3 vec3::ZERO = vec3(0, 0, 0);
vec3 vec3::ONE = vec3(1, 1, 1);
vec3 vec3::DOWN = vec3(0, -1, 0);
vec3 vec3::UP = vec3(0, 1, 0);
vec3 vec3::BACK = vec3(0, 0, -1);
vec3 vec3::FORWARD = vec3(0, 0, 1);
vec3 vec3::LEFT = vec3(-1, 0, 0);
vec3 vec3::RIGHT = vec3(1, 0, 0);

vec3 vec3::normalize() const {
	vec3 normalized = vec3(x(), y(), z());
	return unit_vector(normalized);
}