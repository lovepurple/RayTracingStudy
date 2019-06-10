#include "Utility.h"

vec3 Utility::random_direction_in_unit_sphere()
{
	//[-1,1]
	vec3 reflectDir = 2.0f * vec3(DRand48::drand48(), DRand48::drand48(), DRand48::drand48()) - vec3::ONE;
	return reflectDir;

}
