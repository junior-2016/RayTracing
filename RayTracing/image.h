#ifndef IMAGE_H
#define IMAGE_H
#include<cmath>
#include<fstream>
#include<string>
#include<cstdlib>
#include"rgb.h"
using namespace std;
class image
{
private:
	rgb ** raster;//raster:��դ
	int nx;//raster���
	int ny;//raster�߶�
public:
	image();
	image(int width, int height);
	image(int width, int height, rgb background_color);
	~image();
	bool setColor(int x, int y, rgb & color);
	rgb getColor(int x, int y)const;
	//void gammaCorrect(float gamma);//������
	void writePPM(ostream & out,float gamma=2.2f);
	void readPPM(string file_name,float gamma=2.2f);
};
#endif // !IMAGE_H

