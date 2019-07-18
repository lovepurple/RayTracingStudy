#pragma once
#include "Hitable.h"
/*
	y-z平面上的plane
*/
class YZ_Rect :
	public Hitable
{
public:
	YZ_Rect() {}
	YZ_Rect(float yMin, float yMax, float zMin, float zMax, float x, Material* mat);


	virtual bool Hit(const ray& ray, float t_min, float t_max, HitInfo& hitInfo) const override;


	virtual AABB* getHitable_AABB(float time0, float time1) override;

private:
	float m_yMin, m_yMax;
	float m_zMin, m_zMax;
	float m_x;
	Material* m_mat;
};

