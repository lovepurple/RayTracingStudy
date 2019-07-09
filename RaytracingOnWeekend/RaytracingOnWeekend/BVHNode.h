#pragma once
/**
 * Bounding Volume Hierarchies
	层次包围体，log(n) 二份思想 优化碰撞
 */
#include "Hitable.h"
#include "DRand48.h"

class BVHNode :Hitable
{
public:
	BVHNode();

	/**
	 * @brief:构建BVH 树
	 */
	BVHNode(Hitable** hitableList, int n, float time0, float time1);


	// Inherited via Hitable
	virtual bool Hit(const ray& ray, float t_min, float t_max, HitInfo& hitInfo) const override;

	virtual AABB* getHitable_AABB(float time0, float time1) override;

private:
	AABB* m_aabb;
	Hitable* m_leftNode;
	Hitable* m_rightNode;


};
/*
		x比较器
	*/
int comparerX(const void* left, const void* right);		//函数指针
int comparerY(const void* left, const void* right);
int comparerZ(const void* left, const void* right);

