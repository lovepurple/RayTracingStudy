#pragma once
#include "Vec3.h"
class ray
{
public:
	ray();
	~ray();

	//a是原点 b为方向
	ray(const vec3& originPoint, const vec3& direction) { A = originPoint; B = direction; }		// &在变量定义的时候就表示变量的引用。与C#里直接定义类的成员一致。

	//模拟时间
	ray(const vec3& originPoint, const vec3& direction, float time) {
		A = originPoint;
		B = direction;
		m_time = time;
	}
	vec3 origin() const { return A; }
	vec3 direction() const { return B; }
	vec3 point_at_parameter(float t) const { return A + B * t; };

	float getTime() const;

private:
	vec3 A;
	vec3 B;
	float m_time;
};

