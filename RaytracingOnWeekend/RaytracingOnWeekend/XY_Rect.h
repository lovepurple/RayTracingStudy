#pragma once
#include "Hitable.h"

/*
	@brief: ��ֱ��z���x-y ƽ��
*/
class XY_Rect :
	public Hitable
{
public:
	XY_Rect() {}
	XY_Rect(float xmin, float xmax, float ymin, float ymax, float z, Material* mat);

	virtual bool Hit(const ray& ray, float t_min, float t_max, HitInfo& hitInfo) const override;


	virtual AABB* getHitable_AABB(float time0, float time1) override;

private:
	//�����ĸ��ǵ�����
	float m_xmin, m_xmax;
	float m_ymin, m_ymax;
	float m_z;		//����z������
	Material* m_matPtr;
};

