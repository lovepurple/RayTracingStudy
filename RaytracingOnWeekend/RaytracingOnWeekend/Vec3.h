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

	inline float u() const { return e[0]; }
	inline float v() const { return e[1]; }

	inline const vec3& operator+() const { return *this; }
	inline vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); }
	inline float operator[](int i) const { return e[i]; }			//C++啥都能重载。。。
	inline float& operator[](int i) { return e[i]; }				//一个有const 一个没有

	inline vec3& operator+=(const vec3& v2);			//声明方法签名
	inline vec3& operator-=(const vec3& v2);
	inline vec3& operator*=(const vec3& v2);
	inline vec3& operator/=(const vec3& v2);
	inline vec3& operator*=(const float f);
	inline vec3& operator/=(const float f);
	inline bool operator==(const vec3& v2);


	inline float length() const			//C++ 1. 函数后加const 作用是声明函数为只读函数，只有const 成员才能调用 2.此函数不能修改成员变量的值。
	{
		return sqrt(e[0] * e[0] + e[1] * e[1] + e[2] * e[2]);		//这里直接返回了一个float指，并没修改函数中的成员
	}

	inline float squared_length() const
	{
		return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
	}

	inline void make_unit_vector();			//inline 在编译时，会自动展开，适合操作比较简单的函数。
	vec3 normalize() const;

	float e[3];
	static vec3 ZERO;
	static vec3 ONE;
	static vec3 UP;
	static vec3 DOWN;
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

//调用的时候不需要vec3:: 理解，只要是include这个头 该函数就有了
inline float square_distance(const vec3& v1, const vec3& v2) {
	vec3 v2Tov1 = v2 - v1;
	return dot(v2Tov1, v2Tov1);
}

inline float distance(const vec3& v1, const vec3& v2) {
	return sqrt(square_distance(v1, v2));
}


//实现定义的方法体
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

inline bool vec3::operator==(const vec3& v2)
{
	return e[0] == v2.e[0] &&
		e[1] == v2.e[1] &&
		e[2] == v2.e[2];
}


//normalize
inline vec3 unit_vector(vec3 v)
{
	return v / v.length();
}

inline vec3 toColor(const vec3& v) {
	return (v + 1.0) * 0.5f;
}

inline vec3 toColor(float val) {
	float clamp01 = (val + 1.0) * 0.5f;
	return vec3(clamp01, clamp01, clamp01);
}

inline vec3 toGammaColor(vec3& v, float gammaValue) {
	vec3 gammaColor = toColor(v);
	gammaColor.e[0] = pow(gammaColor.e[0], gammaValue);
	gammaColor.e[1] = pow(gammaColor.e[1], gammaValue);
	gammaColor.e[2] = pow(gammaColor.e[2], gammaValue);

	return gammaColor;
}

/**
 * 反射向量
 */
inline vec3 reflect(const vec3& input, const vec3& normal) {
	return input - 2 * dot(input, normal) * normal;
}

inline  vec3 lerp(const vec3& vec1, const vec3& vec2, float factor) {
	return (1 - factor) * vec1 + vec2 * factor;
}

/**
 * 求折射向量

	n1_over_n2 为 入射介质常量 / 介质内部常量

	坑爹，书中折射公式给的有问题，一会用的是Normalized 一会用的原来的
 */
inline bool refract(const vec3& inputDir, const vec3& normalDir, float n1_over_n2, vec3& refractDir) {
	vec3 normalizeInputDir = unit_vector(inputDir);
	float IDotN = dot(normalizeInputDir, normalDir);
	float discriminant = 1.0 - n1_over_n2 * (1.0 - IDotN * IDotN);

	if (discriminant > 0)
	{
		refractDir = n1_over_n2 * (normalizeInputDir - normalDir * IDotN) - normalDir * sqrt(discriminant);
		refractDir = unit_vector(refractDir);
		return true;
	}

	return false;		//全反射，如果n1 n2相等 直接全反射
}

/*
std::ostream& operator<<(std::ostream& out, vec3& v) {
	std::cout << v.e[0] << "," << v.e[1] << "," << v.e[2] << std::endl;
	return out;
}*/

#endif