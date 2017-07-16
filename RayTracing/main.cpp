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
	//���������zֵ����Ϊ��ֵ.���z��������Ҫ��������ϵ.
	Vector3 direction(0, 0, -1);
	ShapeList shapes;
	shapes.add(new Sphere(Vector3(250, 250, -1000), 150, rgb(0.2, 0.2, 0.8)));
	shapes.add(new Triangle(Vector3(300.0f, 600.0f, -800),
		Vector3(0.0f, 100.0f, -1000),
		Vector3(450.0f, 20.0f, -1000),
		rgb(0.8, 0.2, 0.2)));
	image im(500,500);

	/*
	image�����:image[nx][ny] ��һά����x����,�ڶ�ά����y����
 y��|------------|
	|            |
 ny	|  .(i,j)    |  (�������ȷ�������ڿ��Ƿ�λ,���󡢻���ͼƬʱ,����ʹ�ù��õ�����ϵ����)
	|            |
	O------------|x��
	     nx
    ��ӡimageʱ:
	for (int j=ny-1;j>=0;j--)
	{
	    for (int i=0;i<nx;i++)
		{
		    ...(print)
		}
	}
	��ͼƬ�����Ͻǿ�ʼ��ӡ,������ӡ������ͼ�����������ϰ�ߵ�����ϵ��Ƴ�����ͼ����һ�µ�.
	*/

	/*
	for (int i = 0;i < 500;i++)
	{
		for (int j = 0;j <500;j++)
		{
			
			rgb total_color(0.0f, 0.0f, 0.0f);
			//ERROR1:�������...һ��ʼ��Ӧ�ð�total_color���ֵ����Ϊ�ֲ�����,ÿ��ִ��һ�����ز���ǰ����Ҫ��ղ���.
			//��Ȼ��total_color����Ϊȫ�ֱ������һ�û�����!!!!!
			Vector2 * samples = new Vector2[sam_num];
			Sample sm((ULL)time(NULL));
			sm.random(samples, sam_num);
			for (int k = 0;k < sam_num;k++)
			{
				tmax = 100000.0f;
				is_hit = false;
				Ray r(Vector3((float)i-0.5f+samples[k].x(),(float)j-0.5f+samples[k].y(), 0.0f), direction);
				//��ÿһ�����ص㴦������һ������,����ֱ������ƽ������

				is_hit = shapes.hit(r, 0.00001f, tmax, 0, record);
				//time��������ֻ����0
				//ShapeList��hit�����������ж��(�Զ��ƽ��)�Ľ�����(��Զ����),ͬʱ�����Ƿ�ɹ��������Ϣ,������Ҫ�ѷ���ֵ��ֵ��is_hit(bool).
				//��recordֻ�ܱ������һ�γɹ��������Ϣ(��Ϊÿһ�ν���ɹ������tmax�ĳɵ�ǰ���ߵ�tֵ,������һ�η�������
				//������tֵ��Ȼ��ȵ�ǰ��tֵ��С,Ҳ����˵���յ�tֵ�ǹ�������������巢������ʱ���������,������ʵ���˽����
				//Զ��������ڵ�����).

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