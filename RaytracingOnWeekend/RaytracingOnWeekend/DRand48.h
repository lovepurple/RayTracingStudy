#pragma once
#include <stdlib.h>
#define m1 0x100000000LL		//ͬһ������һ�������У���������include ��ֻ����һ��
#define c1 0xB16  
#define a1 0x5DEECE66DLL  

class DRand48
{
public:
	static double drand48();
	static double srand48(unsigned int i);
private:
	static  long long seed;//��̬�����ĳ�ʼ����class�����У���û�����ڴ棬�ڵ���֮�����
};
//long long DRand48::seed = 1;	 ���.h .cpp�Ƿֿ��ģ���ʼ��Ҫ��.cpp����У���������LNK2005  

