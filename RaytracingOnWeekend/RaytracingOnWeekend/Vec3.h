#ifndef VEC3H
#define VEC3H

#include <math.h>
#include <stdlib.h>
#include <iostream>

class vec3
{
public:
	vec3() {}
	vec3(float e0, float e1, float e2) { e[0] = e0, e[1] = e1, e[2] = e2; }

	inline float x() const { return e[0]; }
	inline float y() const { return e[1]; }
	inline float z() const { return e[2]; }
	inline float r() const { return e[0]; }
	inline float g() const { return e[1]; }
	inline float b() const { return e[2]; }

	inline const vec3& operator+() const { return *this; }
	inline vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); }
	inline float operator[](int i) const { return e[i]; }			//C++ɶ�������ء�����
	inline float& operator[](int i) { return e[i]; }				//һ����const һ��û��

	inline vec3& operator+=(const vec3 &v2);			//��������ǩ��
	inline vec3& operator-=(const vec3 &v2);
	inline vec3& operator*=(const vec3 &v2);
	inline vec3& operator/=(const vec3 &v2);
	inline vec3& operator*=(const float f);
	inline vec3& operator/=(const float f);

	inline float length() const			//C++ 1. �������const ��������������Ϊֻ��������ֻ��const ��Ա���ܵ��� 2.�˺��������޸ĳ�Ա������ֵ��
	{
		return sqrt(e[0] * e[0] + e[1] * e[1] + e[2] * e[2]);		//����ֱ�ӷ�����һ��floatָ����û�޸ĺ����еĳ�Ա
	}

	inline float squared_length() const
	{
		return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
	}

	inline void make_unit_vector();			//inline �ڱ���ʱ�����Զ�չ�����ʺϲ����Ƚϼ򵥵ĺ�����


	float e[3];
};


inline std::istream& operator>>(std::istream &is, vec3 &t)
{
	is >> t.e[0] >> t.e[1] >> t.e[2];
	return is;
}


#endif