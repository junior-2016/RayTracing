#include<iostream>
#include<cmath>
#include<fstream>
#include<string>
#include<assert.h>
#include"image.h"
using namespace std;
image::image() {}
image::image(int width, int height)
{
	assert(width > 0 && height > 0);
	nx = width;
	ny = height;
	raster = new rgb*[nx];
	assert(raster);
	for (int i = 0;i < nx;i++)
	{
		raster[i] = new rgb[ny];
		assert(raster[i]);
	}
}
image::image(int width, int height, rgb background_color)
{
	assert(width > 0 && height > 0);
	nx = width;
	ny = height;
	raster = new rgb*[nx];
	assert(raster);
	for (int i = 0;i < nx;i++)
	{
		raster[i] = new rgb[ny];
		assert(raster[i]);
		for (int j = 0;j < ny;j++)
			raster[i][j] = background_color;
	}
}
image::~image()
{
	for (int i = 0;i < nx;i++)
	{
		delete[] raster[i];
		raster[i] = NULL;
	}
	delete[] raster;
	raster = NULL;
}
void image::setColor(int x, int y, rgb & color)
{
	assert(x >= 0 && x < nx);
	assert(y >= 0 && y < ny);
	raster[x][y] = color;
}
rgb image::getColor(int x, int y)const
{
	x = (x >= 0 ? x : 0);
	x = (x < nx ? x : nx - 1);
	y = (y >= 0 ? y : 0);
	y = (y < ny ? y : ny - 1);
	return raster[x][y];
}
void image::writeP6PPM(ostream & out)
{
	out << "P6\n" << nx << " " << ny << "\n255\n";
	
	/*
	下面的for循环如果写成:
	 for(unsigned int y=ny-1;y>=0;y--)
	{
		....
	}
	会出现无限循环错误.因为当y=0时,y--变成2^32-1,继续循环.
	解决的方法:
	1,改用int;
	2,改成for (unsigned y=ny-1;y!=0;y--){...}
	*/
	for (int y = ny - 1; y >= 0; y--)
	{
		for (int x = 0;x < nx;x++)
		{
			rgb col = raster[x][y];
			unsigned char cr = (unsigned char)(255.0*col.red());
			unsigned char cg = (unsigned char)(255.0*col.green());
			unsigned char cb = (unsigned char)(255.0*col.blue());
			out <<cr<<cg<<cb ;
		}
	}
	
}
void image::writeP3PPM(ostream & out)
{
	out << "P3\n" << nx << " " << ny << "\n255\n";
	for (int y = ny-1; y >=0 ; y--)
	{
		for (int x = 0;x < nx;x++)
		{
			rgb col = raster[x][y];
			int ir = (int)(255.0*col.red());
			int ig = (int)(255.0*col.green());
			int ib = (int)(255.0*col.blue());
			out << ir << " " << ig << " " << ib << "\n";
		}
	}
}
int image::width()
{
	return nx;
}
int image::height()
{
	return ny;
}
void image::readPPM(char *file_name)
{
	FILE* file = fopen(file_name, "rb");

	if (file == 0) {
		cout << "could not open file" << endl;
	}
	else
		cout << "file opened" << endl;

	unsigned char ppm_type;
	if (fscanf(file, "P%c\n", &ppm_type) != 1) {
		cout << "Invalid PPM signature" << endl;
	}


	if (ppm_type == '6') 
	{
		cout << "PPM P6 type" << endl;



		unsigned char dummy;
		while (fscanf(file, "#%c", &dummy))
			while (fgetc(file) != '\n');



		if (fscanf(file, "%d %d\n", &nx, &ny) != 2) {
			cout << "Invalid image size" << endl;
		}

		if (nx <= 0)
			cout << "Invalid image width" << endl;
		else
			cout << "hres = " << nx << endl;


		if (ny <= 0)
			cout << "Invalid image height" << endl;
		else
			cout << "vres = " << ny << endl;



		unsigned int max_value;
		if (fscanf(file, "%d\n", &max_value) != 1) {
			cout << "Invalid max value" << endl;
		}

		float inv_max_value = 1.0 / (float)max_value;



		raster = new rgb*[nx];
		for (int x = 0;x < nx;x++)
			raster[x] = new rgb[ny];


		for (int y = ny - 1; y >= 0; y--) {
			for (int x = 0; x < nx; x++) {
				unsigned char red;
				unsigned char green;
				unsigned char blue;

				if (fscanf(file, "%c%c%c", &red, &green, &blue) != 3) {
					cout << "Invalid image" << endl;
				}

				float r = red   * inv_max_value;
				float g = green * inv_max_value;
				float b = blue  * inv_max_value;
				rgb c(r, g, b);
				raster[x][y] = c;
			}
		}
	}

	if (ppm_type == '3')
	{
		cout << "PPM P3 type" << endl;



		unsigned char dummy;
		while (fscanf(file, "#%c", &dummy))
			while (fgetc(file) != '\n');



		if (fscanf(file, "%d %d\n", &nx, &ny) != 2) {
			cout << "Invalid image size" << endl;
		}

		if (nx <= 0)
			cout << "Invalid image width" << endl;
		else
			cout << "hres = " << nx << endl;


		if (ny <= 0)
			cout << "Invalid image height" << endl;
		else
			cout << "vres = " << ny << endl;


		unsigned int max_value;
		if (fscanf(file, "%d\n", &max_value) != 1) {
			cout << "Invalid max value" << endl;
		}

		float inv_max_value = 1.0 / (float)max_value;


		raster = new rgb*[nx];
		for (int x = 0;x < nx;x++)
			raster[x] = new rgb[ny];

		for (int y = ny-1; y >=0; y--) {
			for (int x = 0; x < nx; x++) {
				unsigned int red;
				unsigned int green;
				unsigned int blue;

				if (fscanf(file, "%d%d%d\n", &red, &green, &blue) != 3) {
					cout << "Invalid image" << endl;
				}

				float r = red   * inv_max_value;
				float g = green * inv_max_value;
				float b = blue  * inv_max_value;
				rgb c(r, g, b);
				raster[x][y] = c;
			}
		}
	}

	fclose(file);

	cout << "finished reading PPM file" << endl;
}
