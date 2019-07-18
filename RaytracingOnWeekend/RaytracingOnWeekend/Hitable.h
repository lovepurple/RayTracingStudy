#pragma once
#include "ray.h"
#include "AABB.h"

/**
 * 理解，由于Material.h中需要引用Hitable.h 而 hitable.h又需要include Material.h 造成了循环include
	所以在这里不去include 直接声明要使用的类，提前告诉编译器要使用的类，而且不能使用类本身，必须要用指针，因类在这里，类还没分配内存，而指针就是占用4个字节固定大小
 */
class Material;

/*
	抽象类，用于描述是光线是否击中物理
*/

struct HitInfo
{
	float HitRay_Factor;
	vec3 HitPoint;
	vec3 HitPointNormal;
	Material* mat_ptr;		//所属材质，当多处引用一个对象时，使用指针
	vec3 hitPointUV;
};


class Hitable
{
	//C++ 纯虚函数（抽象函数）,函数结束是=0 ，子类必须实现
public:
	virtual bool Hit(const ray& ray, float t_min, float t_max, HitInfo& hitInfo) const = 0;

	//获取物体的AABB time0,time1表示可移动的物体的时间计算
 	virtual AABB* getHitable_AABB(float time0, float time1) { return m_hitableObjectAABB; };

protected:
	AABB* m_hitableObjectAABB;
};

