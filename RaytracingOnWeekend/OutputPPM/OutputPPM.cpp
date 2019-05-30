
#include <iostream>
#include <fstream>

#define WIDTH  256.0
#define HEIGHT 256.0
#define cout fout			//C++ţ�Ƶĺ꣬��cout�ض���fout

/*
	PPM��ʽ�� ɫֵĿǰ�������ø�����
*/

int main()
{
	//�ض��� cout 
	std::ofstream fout(".\\renderImage.ppm");

	cout << "P3" << std::endl;
	cout << WIDTH << " " << HEIGHT << std::endl;
	cout << "255" << std::endl;

	for (int i = HEIGHT; i > 0; --i)
	{
		for (int j = 0; j < WIDTH; ++j)
		{
			int r = (j / WIDTH) * 255.00f;
			int g = (i / HEIGHT) * 255.00f;
			int b = 0;

			cout << r << " " << g << " " << b << " ";
		}
		cout << std::endl;
	}
}