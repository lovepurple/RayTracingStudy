#include "DRand48.h"

long long DRand48::seed = 123456;

double DRand48::drand48()
{
	seed = (a10 * seed + c10) & 0xFFFFFFFFFFFFLL;
	unsigned int x = seed >> 16;

	return ((double)x / (double)m1);
}
