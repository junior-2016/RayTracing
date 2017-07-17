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
}//ʹ��ʱ,������if(!setColor(x,y,color)){cerr<<"Can't setColr"<<endl;exit(-1);}
rgb image::getColor(int x, int y)const
{
	x = (x >= 0 ? x : 0);
	x = (x < nx ? x : nx - 1);
	y = (y >= 0 ? y : 0);
	y = (y < ny ? y : ny - 1);
	return raster[x][y];
}
/*
�����gamma������д���ļ�����writePPM()�ϲ�
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
}//������,��raster[i][j]��ֵ����Ϊraster[i][j]^(1.0/gamma)
 /*
 RGB:����float����RGB����������ɫǿ�ȵ�ֵ,��Χ[0,1),��f��ʾ,��f��Χ[0,1),f������ɫ��ǿ��,
 ����f�����Ա�ʾ��,��f=0.5����һ�����ɫǿ��.
 ������rgb��ʱ,rgb�ķ���������ɫǿ�ȶ�������ɫֵ(��ɫֵ�ķ�Χ��[0,255]).

 ������ϵͳ����ɫǿ������ɫֵ�Ĺ�ϵ�Ƿ����Ե�,������Ҫ����ת��.
 ��֪ϵͳͼƬ��ÿһ�����ص����ɫֵ��RGB(��RGBA)��ʾ,ÿ����ɫֵ����i�ķ�Χ����[0,255],
 ��ɫǿ��ֵ������(i/256)^��(���ڴ��PC��2.2).����f��i�Ĺ�ϵ��f=(i/256)^��;
 ��fת��ΪϵͳͼƬ����ɫ����ֵ��ʾ:i=(int)(256*f^(1/��)).
 */
void image::writeP6PPM(ostream & out)//�ڶ�������Ĭ����2.2
{
	out << "P6\n" << nx << " " << ny << "\n255\n";//P6���͵��ļ��洢������unsigned char����ʽ�洢.
	unsigned int i;
	for (int y = ny - 1;y >= 0;y--)
   //nx����ͼƬ���,ny����ͼƬ�߶�,��Ȼraster��[nx][ny]����,
   //����д���ļ�ʱ�ͱ�����nyΪ��ѭ��,nxΪ��ѭ��,���ܷ���ͼƬ��
   //���nx(��Ϊ����Ҳ�����е���Ŀ,��column����Ŀ)
   //�͸߶�ny(��Ϊ����Ҳ�����е���Ŀ,��row����Ŀ)����
	{
		for (int x = 0;x < nx;x++)
		{
			float gamma = 1.0 /2.2 ;
			raster[x][y] = rgb(pow(raster[x][y].red(), gamma), 
				pow(raster[x][y].green(), gamma),
				pow(raster[x][y].blue(), gamma));//�ȶ����ݽ���gamma����
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
	int x, y, cols, rows;//cols:���е���Ŀ;rows:���е���Ŀ
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
		   //PS:��������������ת��Ϊ����:(int)(float+0.5),����5.6,���ֱ��(int)5.6=5(ֱ�ӽ�ȡ��������),
		   //���(int)(5.6+0.5)=(int)6.1=6,ʵ������������.
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