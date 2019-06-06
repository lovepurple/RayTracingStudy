#pragma once
#include <stdlib.h>
#define m1 0x100000000LL		//同一个宏在一个程序中（包括各种include ）只能有一次
#define c1 0xB16  
#define a1 0x5DEECE66DLL  

class DRand48
{
public:
	static double drand48();
	static double srand48(unsigned int i);
private:
	static  long long seed;//静态变量的初始化，class定义中，并没分配内存，在调用之后分配
};
//long long DRand48::seed = 1;	 如果.h .cpp是分开的，初始化要在.cpp里进行，否则会出现LNK2005  

