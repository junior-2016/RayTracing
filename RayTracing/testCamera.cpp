#include<iostream>
#include<cmath>
#include<string>
#include<fstream>
#include<vector>
#include"Vector3.h"
#include"rgb.h"
#include"image.h"
#include"Shape.h"
#include"Triangle.h"
#include"Sphere.h"
#include"ShapeList.h"
#include"RandomNumber.h"
#include"Vector2.h"
#include<ctime>
#include"Sample.h"
#include"DynamicSphere.h"
#include"Camera.h"
using namespace std;
int main()
{
	//Camera调试如下(只改变照相机与成像平面的距离(最后一个参数)以及gaze向量(第二个参数))
	//很明显只有物体处于成像平面部分的渲染才是清晰的,而偏离成像平面的部分(无论是偏离在成像平面前还是成像平面后都是模糊的(DefocusBlur)),
	//当物体越靠近成像平面时越清晰.

	//1,Camera cam(Vector3(0, 0, 0), Vector3(0, 0,-500 ), Vector3(0, 1, 0),50, -600, 600, 600, -600, 500);
	//Camera image plane 位于(0,0,-500),即在所有物体之前,会发现所有物体都产生散焦模糊(DefocusBlur).
	//2,Camera cam(Vector3(0, 0, 0), Vector3(0, 0, -800), Vector3(0, 1, 0), 50, -600, 600, 600, -600, 800);
	//3,Camera cam(Vector3(0, 0, 0), Vector3(0, 0, -1000), Vector3(0, 1, 0), 50, -600, 600, 600, -600, 1000);
	//4,Camera cam(Vector3(0, 0, 0), Vector3(0, 0, -1100), Vector3(0, 1, 0), 50, -600, 600, 600, -600, 1100);
	Camera cam(Vector3(0, 0, 0), Vector3(0, 0, -1100), Vector3(0, 1, 0), 50, -800, 800, 800, -800, 1100);
	//如果随时间变化改变照相机的第三个参数vup向量,可以实现照相机旋转,也就间接实现图像旋转
	int nx = 500;
	int ny = 500;
	image im(nx, ny);
	int sam_num = 100;//sam_num要刚好可以开方
	ShapeList shapes;

	shapes.add(new Sphere(Vector3(300, 300, -1700), 100, rgb(0.2, 0.2, 0.8)));
	shapes.add(new Sphere(Vector3(150, 150, -1500), 100, rgb(0.4, 0.3, 0.2)));
	shapes.add(new Sphere(Vector3(50, 50, -1300), 100, rgb(0.5, 0.7, 0.4)));
	shapes.add(new Sphere(Vector3(-50, -50, -1100), 100, rgb(0.7, 0.2, 0.5)));
	shapes.add(new Sphere(Vector3(-200, -200, -1000), 100, rgb(0.5, 0.7, 0.2)));

	RandomNumber  rm((ULL)time(NULL));
	for (int i = 0;i <nx;i++)
	{
		for (int j = 0;j < ny;j++)
		{
			float pixel_x = ((float)i + 0.5f) / (float)nx;
			float pixel_y = ((float)j + 0.5f) / (float)ny;
			//照相机获取光线的函数getRay()的第一个和第二个参数是像素在成像平面的x和y坐标(范围[0,1]),
			//原始的像素坐标(i,j)到(pixel_x,pixel_y)的映射方法:
			//pixel_x = (i + 0.5) / nx;
			//pixel_y = (j + 0.5) / ny;

			rgb total_color(0, 0, 0);
			Vector2*samples = new Vector2[sam_num];
			Sample sm((ULL)time(NULL));
			sm.jitter(samples, sam_num);
			//使用正方形采样算法产生光线在照相机光圈的采样点,会产生bokeh(弥散)效果.

			sm.SquareToDisk(samples, sam_num);
			//二次采样.将正方形的采样点映射到圆形区域.
			for (int k = 0;k < sam_num;k++)
			{
				HitRecord record;
				bool is_hit = false;
				float tmax = 100000.0f;
				Ray r = cam.getRay(pixel_x, pixel_y, samples[k].x(),samples[k].y());
				is_hit = shapes.hit(r, 0.00001f, tmax,0.0, record);
				//第四个参数time只对有Dynamic_开头的形状类(可以通过时间改变形状参数)有效,其他普通的形状类无效.
				//并且第四个参数必须是(0,1)范围内的与时间相关的数,
				//很遗憾的是,现在这个程序不是实时的,只能一次一张图片或者通过循环一次打印多张图片,
				//不过这样子做非常耗费内存,因为我现在的数据计算都是在CPU而不是在GPU上的,
				//如果想要明显的动画效果必须一秒钟渲染60张以上的图片并且呈现在win32应用程序上,
				//后面打算加入Win32框架(或者使用已有的图形框架QT)搭建图形界面作为图片载体;
				//第二步是加入GPU和C++并行处理,把复杂的数据计算丢给GPU才有可能加速渲染.
				if (is_hit)
					total_color += 0.5*rgb(record.normal.x()+1,record.normal.y()+1,record.normal.z()+1);
				else
				{
					float  Y_interpolation = (r.direction().y() + 1.0)*0.5;
					//ray的direction向量已经单位化,范围在[-1,1].
					//获取direction向量的y分量然后转为范围为[0,1]的Y轴方向的插值
					total_color += Y_interpolation*rgb(0.5,0.7,1.0) + (1.0 - Y_interpolation)*rgb(1.0,1.0,1.0);
					//将天蓝色与白色插值
				}
			}
			im.setColor(i, j, total_color / sam_num);
			delete[]samples;
		}
	}
	ofstream of("F:\\VisualStudio Project\\ComputerGraphic\\RayTracing\\image\\FiveDynamicSphere(JitterToDisk).ppm");

	if (of)
	{
		im.writeP3PPM(of);
	}
	else
	{
		cout << "ErrorPrintPPM";
	}
	system("pause");
	return 0;
}