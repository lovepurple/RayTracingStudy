#pragma once
#include "Hitable.h"

/*
	x-z平面 水平面
*/
class XZ_Rect :
	public Hitable
{
public:
	XZ_Rect() {}
	XZ_Rect(float xMin, float xMax, float zMin, float zMax, float y, Material* mat, vec3 normal);


	virtual bool Hit(const ray& ray, float t_min, float t_max, HitInfo& hitInfo) const override;


	virtual AABB* getHitable_AABB(float time0, float time1) override;

private:
	float m_xMin, m_xMax;
	float m_zMin, m_zMax;
	float m_y;

	Material* m_mat;
	vec3 m_normal;
};

