#include<iostream>
#include<cmath>
#include<fstream>
#include<string>
#include<assert.h>
#include"image.h"
using namespace std;
image::image(){}
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
		raster[i] =NULL;
	}
	delete[] raster;
	raster = NULL;
}
bool image::setColor(int x, int y, rgb & color)
{
	if (x<0 || x>nx) return false;
	if (y<0 || y>ny) return false;
	raster[x][y] = color;
	return true;
}//使用时,必须用if(!setColor(x,y,color)){cerr<<"Can't setColr"<<endl;exit(-1);}
rgb image::getColor(int x, int y)const
{
	x = (x >= 0 ? x : 0);
	x = (x < nx ? x : nx - 1);
	y = (y >= 0 ? y : 0);
	y = (y < ny ? y : ny - 1);
	return raster[x][y];
}
/*
后面把gamma修正与写入文件函数writePPM()合并
void image::gammaCorrect(float gamma)
{
	rgb temp;
	float power = 1.0 / gamma;
	for (int i = 0;i < nx;i++)
	{
		for (int j = 0;j < ny;j++)
		{
			temp = raster[i][j];
			raster[i][j] = rgb(pow(temp.red(), power), pow(temp.green(), power), pow(temp.blue(), power));
		}
	}
}//γ修正,将raster[i][j]的值修正为raster[i][j]^(1.0/gamma)
 /*
 RGB:设置float储存RGB三个分量颜色强度的值,范围[0,1),用f表示,即f范围[0,1),f代表颜色的强度,
 这里f是线性表示的,即f=0.5代表一半的颜色强度.
 因此设计rgb类时,rgb的分量代表颜色强度而不是颜色值(颜色值的范围是[0,255]).

 但是在系统里颜色强度与颜色值的关系是非线性的,所以需要进行转换.
 已知系统图片的每一个像素点的颜色值用RGB(或RGBA)表示,每个颜色值分量i的范围都是[0,255],
 颜色强度值正比于(i/256)^γ(γ在大多PC是2.2).所以f与i的关系是f=(i/256)^γ;
 将f转换为系统图片的颜色分量值表示:i=(int)(256*f^(1/γ)).
 */
void image::writeP6PPM(ostream & out)//第二个参数默认用2.2
{
	out << "P6\n" << nx << " " << ny << "\n255\n";//P6类型的文件存储最终以unsigned char的形式存储.
	unsigned int i;
	for (int y = ny - 1;y >= 0;y--)
   //nx代表图片宽度,ny代表图片高度,虽然raster是[nx][ny]储存,
   //但是写入文件时就必须以ny为外循环,nx为内循环,才能符合图片的
   //宽度nx(作为竖行也就是列的数目,即column的数目)
   //和高度ny(作为横行也就是行的数目,即row的数目)特征
	{
		for (int x = 0;x < nx;x++)
		{
			float gamma = 1.0 /2.2 ;
			raster[x][y] = rgb(pow(raster[x][y].red(), gamma), 
				pow(raster[x][y].green(), gamma),
				pow(raster[x][y].blue(), gamma));//先对数据进行gamma修正
			i = (unsigned int)(256.0*raster[x][y].red());
			if (i >255) i = 255;
			out.put((unsigned char)i);

			i= (unsigned int)(256.0*raster[x][y].green());
			if (i >255) i = 255;
			out.put((unsigned char)i);

			i= (unsigned int)(256.0*raster[x][y].blue());
			if (i >255) i = 255;
			out.put((unsigned char)i);
		}
	}
}
void image::readPPM(string file_name)
{
	ifstream in;
	in.open(file_name.c_str());
	if (!in.is_open())
	{
		cerr << "ERROR--CAN NOT OPEN FILE " << file_name << endl;
		exit(-1);
	}
	string fileType, garbage;
	int x, y, cols, rows;//cols:竖行的数目;rows:横行的数目
	rgb pixel;
	in >>fileType>> cols >> rows >>garbage;
	nx = cols;
	ny = rows;

	raster = new rgb*[nx];
	for (x = 0;x < nx;x++)
		raster[x] = new rgb[ny];

	if (fileType == "P6")
	{
	    char red, green, blue;
		char new_line;
		in.get(new_line);
		for (y = ny - 1;y >= 0;y--)
		{
			for (x = 0;x < nx;x++)
			{
				in.get(red);
				in.get(green);
				in.get(blue);
				pixel.setRed(pow((((float)((unsigned char)red) + 0.5) / 256.0),2));
				pixel.setGreen(pow((((float)((unsigned char)green) + 0.5) / 256.0),2));
				pixel.setBlue(pow((((float)((unsigned char)blue) + 0.5) / 256.0),2));
		   //PS:浮点数四舍五入转化为整数:(int)(float+0.5),比如5.6,如果直接(int)5.6=5(直接截取整数部分),
		   //如果(int)(5.6+0.5)=(int)6.1=6,实现了四舍五入.
				raster[x][y] = pixel;
			}
		}
	}
	if (fileType == "P3")
	{
		int red, green, blue;
		for (y = ny - 1; y>= 0; y--)
			for (x = 0; x < nx; x++)
			{
				in >> red >> green >> blue;
				pixel.setRed( ((float(red) + 0.5) / 256.0) *
					((float(red) + 0.5) / 256.0));
				pixel.setGreen( ((float(green) + 0.5) / 256.0) *
					((float(green) + 0.5) / 256.0));
				pixel.setBlue(((float(blue) + 0.5) / 256.0) *
					((float(blue) + 0.5) / 256.0));
				raster[x][y] = pixel;
			}
	}
}
void image::writeP3PPM(ostream & out)
{
	out << "P3\n" << nx << " " << ny << "\n255\n";
	for (int y = ny - 1;y >= 0;y--)
	{
		for (int x = 0;x < nx;x++)
		{
			rgb col = raster[x][y];
			int ir = (int)(255.99*col.red());
			int ig = (int)(255.99*col.green());
			int ib = (int)(255.99*col.blue());
			out << ir << " " << ig << " " << ib << "\n";
		}
	}
}