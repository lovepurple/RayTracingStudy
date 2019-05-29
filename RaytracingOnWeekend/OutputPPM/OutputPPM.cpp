
#include <iostream>
#include <fstream>

#define WIDTH  800
#define HEIGHT 500

int main()
{
	//ÖØ¶¨Ïò cout 
	std::ofstream fout("./renderImage.ppm");
	std::cout << "P3" << std::endl;
	std::cout << WIDTH << " " << HEIGHT << "256";


}

