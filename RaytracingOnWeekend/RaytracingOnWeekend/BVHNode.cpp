#include "BVHNode.h"


BVHNode::BVHNode(Hitable** hitableList, int n, float time0, float time1)
{
	//随机选取个坐标轴 进行排序 （按哪个方向）
	int randomAxis = int(DRand48::drand48() * 3);

	if (randomAxis == 0)
		qsort(hitableList, n, sizeof(Hitable*), comparerX);			//C++太难读了。各种define 各种typedef
	else if (randomAxis == 1)
		qsort(hitableList, n, sizeof(Hitable*), comparerY);
	else
		qsort(hitableList, n, sizeof(Hitable*), comparerZ);

	if (n == 1)
	{
		m_leftNode = *(hitableList);
		m_rightNode = *(hitableList);
	}
	else if (n == 2)
	{
		m_leftNode = hitableList[0];
		m_rightNode = hitableList[1];
	}
	else
	{
		m_leftNode = new BVHNode(hitableList, n / 2, time0, time1);
		m_rightNode = new BVHNode(hitableList + n / 2, n - n / 2, time0, time1);
	}

	AABB* leftAABB = m_leftNode->getHitable_AABB(0, 0);
	AABB* rightAABB = m_rightNode->getHitable_AABB(0, 0);

	if (!leftAABB || !rightAABB)
		std::cerr << "No bounding box in bvh_node contractor \n";

	m_aabb = &(AABB::surrounding_box(*leftAABB, *rightAABB));

}

bool BVHNode::Hit(const ray& ray, float t_min, float t_max, HitInfo& hitInfo) const
{
	if (m_aabb->isHit(ray, t_min, t_max))
	{
		HitInfo leftHitInfo, rightHitInfo;
		bool isHitLeft = m_leftNode->Hit(ray, t_min, t_max, leftHitInfo);
		bool isHitRight = m_rightNode->Hit(ray, t_min, t_max, rightHitInfo);

		//两边都击中表示我重叠，取最近的
		if (isHitRight && isHitLeft)
		{
			hitInfo = leftHitInfo.HitRay_Factor <= rightHitInfo.HitRay_Factor ? leftHitInfo : rightHitInfo;
			return true;
		}

		if (isHitLeft)
			hitInfo = leftHitInfo;
		else if (isHitRight)
			hitInfo = rightHitInfo;
		else
			return false;

		return true;
	}
}

AABB* BVHNode::getHitable_AABB(float time0, float time1)
{
	return this->m_aabb;
}


/*
	comparerX不能写在 类里。 qsort 的指针函数签名就是int 如果在类里，会有域的问题。
*/
int comparerX(const void* left, const void* right)
{
	Hitable* leftHitable = *(Hitable * *)left;			//Hitable** 是list 再* 是list的第一个
	Hitable* rightHitable = *(Hitable * *)right;

	AABB* leftHitableAABB = leftHitable->getHitable_AABB(0, 0);
	AABB* rightHitableAABB = rightHitable->getHitable_AABB(0, 0);

	return leftHitableAABB->boundsMin().x() < rightHitableAABB->boundsMin().x() ? -1 : 1;
}

int comparerY(const void* left, const void* right)
{
	Hitable* leftHitable = *(Hitable * *)left;			//Hitable** 是list 再* 是list的第一个
	Hitable* rightHitable = *(Hitable * *)right;

	AABB* leftHitableAABB = leftHitable->getHitable_AABB(0, 0);
	AABB* rightHitableAABB = rightHitable->getHitable_AABB(0, 0);

	return leftHitableAABB->boundsMin().y() < rightHitableAABB->boundsMin().y() ? -1 : 1;
}

int comparerZ(const void* left, const void* right)
{
	Hitable* leftHitable = *(Hitable * *)left;			//Hitable** 是list 再* 是list的第一个
	Hitable* rightHitable = *(Hitable * *)right;

	AABB* leftHitableAABB = leftHitable->getHitable_AABB(0, 0);
	AABB* rightHitableAABB = rightHitable->getHitable_AABB(0, 0);

	return leftHitableAABB->boundsMin().z() < rightHitableAABB->boundsMin().z() ? -1 : 1;
}

