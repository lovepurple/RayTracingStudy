#pragma once
#include "Vec3.h"
class ray
{
public:
	ray();
	~ray();

	//a是原点 b为方向
	ray(const vec3& originPoint, const vec3& direction) { A = originPoint; B = direction; }		// &在变量定义的时候就表示变量的引用。与C#里直接定义类的成员一致。
	vec3 origin() const { return A; }
	vec3 direction() const { return B; }
	vec3 point_at_parameter(float t) const { return A + B * t; };

	vec3 A;
	vec3 B;
};

