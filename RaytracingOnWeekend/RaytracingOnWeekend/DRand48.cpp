#include "DRand48.h"

long long DRand48::seed = 1;

double DRand48::drand48()
{
	seed = (a1 * seed + c1) & 0xFFFFFFFFFFFFLL;
	unsigned int x = seed >> 16;

	return ((double)x / (double)m1);
}
