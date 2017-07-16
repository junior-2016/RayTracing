/*
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
	
	HitRecord record;
	bool is_hit;
	float tmax;
	RandomNumber rm;
	int sam_num = 16;
	//后面的向量z值必须为负值.如果z用正数需要左手坐标系.
	Vector3 direction(0, 0, -1);
	ShapeList shapes;
	shapes.add(new Sphere(Vector3(250, 250, -1000), 150, rgb(0.2, 0.2, 0.8)));
	shapes.add(new Triangle(Vector3(300.0f, 600.0f, -800),
		Vector3(0.0f, 100.0f, -1000),
		Vector3(450.0f, 20.0f, -1000),
		rgb(0.8, 0.2, 0.2)));
	image im(500,500);

	/*
	image的设计:image[nx][ny] 第一维储存x分量,第二维储存y分量
 y轴|------------|
	|            |
 ny	|  .(i,j)    |  (这种设计确保我们在考虑方位,想象、绘制图片时,可以使用惯用的坐标系坐标)
	|            |
	O------------|x轴
	     nx
    打印image时:
	for (int j=ny-1;j>=0;j--)
	{
	    for (int i=0;i<nx;i++)
		{
		    ...(print)
		}
	}
	从图片的左上角开始打印,这样打印出来的图像跟我们利用习惯的坐标系设计出来的图像是一致的.
	*/

	/*
	for (int i = 0;i < 500;i++)
	{
		for (int j = 0;j <500;j++)
		{
			
			rgb total_color(0.0f, 0.0f, 0.0f);
			//ERROR1:我真的是...一开始就应该把total_color这个值设置为局部变量,每次执行一个像素采样前都需要清空才行.
			//居然把total_color设置为全局变量而且还没有清空!!!!!
			Vector2 * samples = new Vector2[sam_num];
			Sample sm((ULL)time(NULL));
			sm.random(samples, sam_num);
			for (int k = 0;k < sam_num;k++)
			{
				tmax = 100000.0f;
				is_hit = false;
				Ray r(Vector3((float)i-0.5f+samples[k].x(),(float)j-0.5f+samples[k].y(), 0.0f), direction);
				//在每一个像素点处均发射一条光线,方向垂直于坐标平面往里

				is_hit = shapes.hit(r, 0.00001f, tmax, 0, record);
				//time参数现在只能置0
				//ShapeList的hit方法轮流进行多次(对多个平面)的交叉检测(从远及近),同时返回是否成功交叉的信息,这里需要把返回值赋值给is_hit(bool).
				//而record只能保留最后一次成功交叉的信息(因为每一次交叉成功都会把tmax改成当前光线的t值,所以下一次发生交叉
				//产生的t值必然会比当前的t值更小,也就是说最终的t值是光线与最近的物体发生交叉时计算出来的,这样就实现了近物对
				//远处物体的遮挡作用).

				if (is_hit) total_color += record.color;
				else total_color += rgb(0.2f, 0.2f, 0.2f);
			}
			im.setColor(i, j,total_color/sam_num);
			delete[]samples;
		}
	}
	ofstream of("F:\\VisualStudio Project\\ComputerGraphic\\RayTracing\\image\\randomSample.ppm");
	
	if (of)
	{
		im.writePPM(of);
	}
	system("pause");
	return 0;
}
*/