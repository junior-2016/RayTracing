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
	void setColor(int x, int y, rgb & color);
	rgb getColor(int x, int y)const;
	//void gammaCorrect(float gamma);//������
	void writeP6PPM(ostream & out);
	void readPPM(char *);
	
	void writeP3PPM(ostream & out);
	int width();
	int height();
};
#endif // !IMAGE_H


