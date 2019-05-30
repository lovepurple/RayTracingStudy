
#include <iostream>
#include <fstream>

#define WIDTH  256.0
#define HEIGHT 256.0
#define cout fout			//C++牛逼的宏，把cout重定向到fout

/*
	PPM格式中 色值目前看不能用浮点数
*/

int main()
{
	//重定向 cout 
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