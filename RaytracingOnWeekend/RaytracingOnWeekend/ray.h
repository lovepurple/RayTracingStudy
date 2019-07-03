#pragma once
#include "Vec3.h"
class ray
{
public:
	ray();
	~ray();

	//a��ԭ�� bΪ����
	ray(const vec3& originPoint, const vec3& direction) { A = originPoint; B = direction; }		// &�ڱ��������ʱ��ͱ�ʾ���������á���C#��ֱ�Ӷ�����ĳ�Աһ�¡�

	//ģ��ʱ��
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

