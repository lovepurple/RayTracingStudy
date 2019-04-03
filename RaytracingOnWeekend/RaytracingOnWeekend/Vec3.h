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
	inline float operator[](int i) const { return e[i]; }			//C++啥都能重载。。。
	inline float& operator[](int i) { return e[i]; }				//一个有const 一个没有

	inline vec3& operator+=(const vec3 &v2);			//声明方法签名
	inline vec3& operator-=(const vec3 &v2);
	inline vec3& operator*=(const vec3 &v2);
	inline vec3& operator/=(const vec3 &v2);
	inline vec3& operator*=(const float f);
	inline vec3& operator/=(const float f);

	inline float length() const			//C++ 1. 函数后加const 作用是声明函数为只读函数，只有const 成员才能调用 2.此函数不能修改成员变量的值。
	{
		return sqrt(e[0] * e[0] + e[1] * e[1] + e[2] * e[2]);		//这里直接返回了一个float指，并没修改函数中的成员
	}

	inline float squared_length() const
	{
		return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
	}

	inline void make_unit_vector();			//inline 在编译时，会自动展开，适合操作比较简单的函数。


	float e[3];
};


inline std::istream& operator>>(std::istream &is, vec3 &t)
{
	is >> t.e[0] >> t.e[1] >> t.e[2];
	return is;
}


#endif