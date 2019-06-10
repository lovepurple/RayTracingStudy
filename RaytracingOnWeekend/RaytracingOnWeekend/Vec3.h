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
	vec3(float e0, float e1) { e[0] = e0, e[1] = e1, e[2] = 0; }

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

	inline vec3& operator+=(const vec3& v2);			//��������ǩ��
	inline vec3& operator-=(const vec3& v2);
	inline vec3& operator*=(const vec3& v2);
	inline vec3& operator/=(const vec3& v2);
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
	static vec3 ZERO;
	static vec3 ONE;
};


//input stream
inline std::istream& operator>>(std::istream& is, vec3& t)
{
	is >> t.e[0] >> t.e[1] >> t.e[2];
	return is;
}

//output stream
inline std::ostream& operator<<(std::ostream& os, const vec3& t)
{
	os << t.e[0] << " " << t.e[1] << " " << t.e[2];
}

inline void vec3::make_unit_vector()
{
	float k = 1.0 / sqrt(e[0] * e[0] + e[1] * e[1] + e[2] * e[2]);
	e[0] *= k;
	e[1] *= k;
	e[2] *= k;
}

inline vec3 operator+(const vec3& v1, const vec3& v2)
{
	return vec3(v1.e[0] + v2.e[0], v1.e[1] + v2.e[1], v1.e[2] + v2.e[2]);
}

inline vec3 operator+(const vec3& v1, const float constValue)
{
	return vec3(v1.e[0] + constValue, v1.e[1] + constValue, v1.e[2] + constValue);
}

inline vec3 operator-(const vec3& v1, const vec3& v2)
{
	return vec3(v1.e[0] - v2.e[0], v1.e[1] - v2.e[1], v1.e[2] - v2.e[2]);
}

inline vec3 operator*(const vec3& v1, const vec3& v2)
{
	return vec3(v1.e[0] * v2.e[0], v1.e[1] * v2.e[1], v1.e[2] * v2.e[2]);
}

inline vec3 operator/(const vec3& v1, const vec3& v2)
{
	return vec3(v1.e[0] / v2.e[0], v1.e[1] / v2.e[1], v1.e[2] / v2.e[2]);
}

inline vec3 operator*(const vec3& v1, float t)
{
	return vec3(v1.e[0] * t, v1.e[1] * t, v1.e[2] * t);
}

inline vec3 operator*(float t, const vec3& v1)
{
	return v1 * t;
}

inline vec3 operator/(vec3 v, float t)
{
	return vec3(v.e[0] / t, v.e[1] / t, v.e[2] / t);
}

inline float dot(const vec3& v1, const vec3& v2)
{
	return v1.e[0] * v2.e[0] + v1.e[1] * v2.e[1] + v1.e[2] * v2.e[2];
}

inline vec3 cross(const vec3& v1, const vec3& v2)
{
	return vec3(
		(v1.e[1] * v2.e[2] - v2.e[1] * v1.e[2]),
		(v1.e[2] * v2.e[0] - v2.e[2] * v1.e[0]),
		(v1.e[0] * v2.e[1] - v2.e[0] * v1.e[1]));
}

//���õ�ʱ����Ҫvec3:: ��⣬ֻҪ��include���ͷ �ú���������
inline float square_distance(const vec3& v1, const vec3& v2) {
	vec3 v2Tov1 = v2 - v1;
	return dot(v2Tov1, v2Tov1);
}

inline float distance(const vec3& v1, const vec3& v2) {
	return sqrt(square_distance(v1, v2));
}



//ʵ�ֶ���ķ�����
inline vec3& vec3::operator +=(const vec3& v)
{
	e[0] += v.e[0];
	e[1] += v.e[1];
	e[2] += v.e[2];

	return *this;
}



inline vec3& vec3::operator -=(const vec3& v)
{
	e[0] -= v.e[0];
	e[1] -= v.e[1];
	e[2] -= v.e[2];

	return *this;
}

inline vec3& vec3::operator *=(const vec3& v)
{
	e[0] *= v.e[0];
	e[1] *= v.e[1];
	e[2] *= v.e[2];

	return *this;
}

inline vec3& vec3::operator /=(const vec3& v)
{
	e[0] /= v.e[0];
	e[1] /= v.e[1];
	e[2] /= v.e[2];

	return *this;
}

inline vec3& vec3::operator *=(const float t)
{
	e[0] *= t;
	e[1] *= t;
	e[2] *= t;

	return *this;
}

inline vec3& vec3::operator /=(const float t)
{
	float  k = 1.0 / t;
	e[0] *= k;
	e[1] *= k;
	e[2] *= k;

	return *this;
}

//normalize
inline vec3 unit_vector(vec3 v)
{
	return v / v.length();
}

inline vec3 toColor(const vec3& v) {
	return (v + 1.0) * 0.5f;
}

inline vec3 toGammaColor(vec3& v, float gammaValue) {
	vec3 gammaColor = toColor(v);
	gammaColor.e[0] = pow(gammaColor.e[0], gammaValue);
	gammaColor.e[1] = pow(gammaColor.e[1], gammaValue);
	gammaColor.e[2] = pow(gammaColor.e[2], gammaValue);

	return gammaColor;
}

/**
 * ��������
 */
inline vec3 reflect(const vec3& input, const vec3& normal) {
	return input - 2 * dot(input, normal) * normal;
}

/*
std::ostream& operator<<(std::ostream& out, vec3& v) {
	std::cout << v.e[0] << "," << v.e[1] << "," << v.e[2] << std::endl;
	return out;
}*/

#endif