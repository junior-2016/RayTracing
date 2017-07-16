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
	Camera cam(Vector3(0, 0, 0), Vector3(0, 0,-50 ), Vector3(0, 1, 0), 50, -50, 50, 50, -50, 50);
	//�����ʱ��仯�ı����������vup����,����ʵ���������ת,Ҳ�ͼ��ʵ��ͼ����ת
	int nx = 500;
	int ny = 500;
	image im(nx, ny);
	int sam_num = 100;
	ShapeList shapes;
	shapes.add(new DynamicSphere(Vector3(0,0,-50),sqrt(150),rgb(0.2,0.2,0.8),0.0,2.0));
	RandomNumber  rm((ULL)time(NULL));
	for (int i = 0;i <nx;i++)
	{
		for (int j = 0;j < ny;j++)
		{
			float pixel_x = ((float)i + 0.5f) / (float)nx;
			float pixel_y = ((float)j + 0.5f) / (float)ny;
			//�������ȡ���ߵĺ���getRay()�ĵ�һ���͵ڶ��������������ڳ���ƽ���x��y����(��Χ[0,1]),
			//ԭʼ����������(i,j)��(pixel_x,pixel_y)��ӳ�䷽��:
			//pixel_x = (i + 0.5) / nx;
			//pixel_y = (j + 0.5) / ny;

			rgb total_color(0, 0, 0);
			Vector2*samples = new Vector2[sam_num];
			Sample sm((ULL)time(NULL));
			sm.multiJitter(samples, sam_num);
			//ʹ�������β����㷨�����������������Ȧ�Ĳ�����,�����bokeh(��ɢ)Ч��.
			for (int k = 0;k < sam_num;k++)
			{
				HitRecord record;
				bool is_hit = false;
				float tmax = 100000.0f;
				Ray r = cam.getRay(pixel_x, pixel_y, samples[k].x(),samples[k].y());
				is_hit = shapes.hit(r, 0.00001f, tmax,0.0, record);
				//���ĸ�����timeֻ����Dynamic_��ͷ����״��(����ͨ��ʱ��ı���״����)��Ч,������ͨ����״����Ч.
				//���ҵ��ĸ�����������(0,1)����ʱ����ص���,
				//���ź�����,�������������ʵʱ��,ֻ��һ��һ��ͼƬ����ͨ��ѭ��һ�δ�ӡ����ͼƬ,
				//�������������ǳ��ķ��ڴ�,��Ϊ�����ڵ����ݼ��㶼����CPU��������GPU�ϵ�,
				//�����Ҫ���ԵĶ���Ч������һ������Ⱦ60�����ϵ�ͼƬ���ҳ�����win32Ӧ�ó�����,
				//����������Win32���(����ʹ�����е�ͼ�ο��QT)�ͼ�ν�����ΪͼƬ����;
				//�ڶ����Ǽ���GPU��C++���д���,�Ѹ��ӵ����ݼ��㶪��GPU���п��ܼ�����Ⱦ.
				if (is_hit)
					total_color += record.color;
				else total_color += rgb(0.2, 0.2, 0.2);
			}
			im.setColor(i, j, total_color / sam_num);
			delete[]samples;
		}
	}
	ofstream of("F:\\VisualStudio Project\\ComputerGraphic\\RayTracing\\image\\DynamicSphere(using RetangleMultiJitterSample).ppm");

	if (of)
	{
		im.writePPM(of);
	}
	system("pause");
	return 0;
}