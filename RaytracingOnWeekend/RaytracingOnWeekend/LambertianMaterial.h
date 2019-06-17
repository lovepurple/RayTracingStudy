#pragma once
#include "Material.h"
#include "Utility.h"
/**
 * Lambertian 漫反射材质
 */
class LambertianMaterial :
	public Material
{
public:
	/**
	 * albedo 指的是反射率

	 加不加const 对于调用方式的区别
		 加const 可以直接
			Material* mat_ptr = new LambertianMaterial(vec(1,1,1))
		 如果不加const，个人理解，传入的参数在别的位置可能用到，所以需要有引用
			Vec albedoCol = vec(1,1,1);
			Material* mat_ptr = new LambertianMaterial(albedoCol);
	 */
	LambertianMaterial(const vec3& albedo) { this->m_albedo = albedo; }

	// Inherited via Material
	virtual bool scatter(const ray& incidentRay, const HitInfo& hitInfo, vec3& attenuation, ray& outRay) const override;
};

