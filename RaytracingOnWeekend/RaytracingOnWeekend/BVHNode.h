#pragma once
/**
 * Bounding Volume Hierarchies
	��ΰ�Χ�壬log(n) ����˼�� �Ż���ײ
 */
#include "Hitable.h"
#include "DRand48.h"

class BVHNode :Hitable
{
public:
	BVHNode();

	/**
	 * @brief:����BVH ��
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
		x�Ƚ���
	*/
int comparerX(const void* left, const void* right);		//����ָ��
int comparerY(const void* left, const void* right);
int comparerZ(const void* left, const void* right);

