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
	//Camera��������(ֻ�ı�����������ƽ��ľ���(���һ������)�Լ�gaze����(�ڶ�������))
	//������ֻ�����崦�ڳ���ƽ�沿�ֵ���Ⱦ����������,��ƫ�����ƽ��Ĳ���(������ƫ���ڳ���ƽ��ǰ���ǳ���ƽ�����ģ����(DefocusBlur)),
	//������Խ��������ƽ��ʱԽ����.

	//1,Camera cam(Vector3(0, 0, 0), Vector3(0, 0,-500 ), Vector3(0, 1, 0),50, -600, 600, 600, -600, 500);
	//Camera image plane λ��(0,0,-500),������������֮ǰ,�ᷢ���������嶼����ɢ��ģ��(DefocusBlur).
	//2,Camera cam(Vector3(0, 0, 0), Vector3(0, 0, -800), Vector3(0, 1, 0), 50, -600, 600, 600, -600, 800);
	//3,Camera cam(Vector3(0, 0, 0), Vector3(0, 0, -1000), Vector3(0, 1, 0), 50, -600, 600, 600, -600, 1000);
	//4,Camera cam(Vector3(0, 0, 0), Vector3(0, 0, -1100), Vector3(0, 1, 0), 50, -600, 600, 600, -600, 1100);
	Camera cam(Vector3(0, 0, 0), Vector3(0, 0, -1100), Vector3(0, 1, 0), 50, -800, 800, 800, -800, 1100);
	//�����ʱ��仯�ı�������ĵ���������vup����,����ʵ���������ת,Ҳ�ͼ��ʵ��ͼ����ת
	int nx = 500;
	int ny = 500;
	image im(nx, ny);
	int sam_num = 100;//sam_numҪ�պÿ��Կ���
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
			//�������ȡ���ߵĺ���getRay()�ĵ�һ���͵ڶ��������������ڳ���ƽ���x��y����(��Χ[0,1]),
			//ԭʼ����������(i,j)��(pixel_x,pixel_y)��ӳ�䷽��:
			//pixel_x = (i + 0.5) / nx;
			//pixel_y = (j + 0.5) / ny;

			rgb total_color(0, 0, 0);
			Vector2*samples = new Vector2[sam_num];
			Sample sm((ULL)time(NULL));
			sm.jitter(samples, sam_num);
			//ʹ�������β����㷨�����������������Ȧ�Ĳ�����,�����bokeh(��ɢ)Ч��.

			sm.SquareToDisk(samples, sam_num);
			//���β���.�������εĲ�����ӳ�䵽Բ������.
			for (int k = 0;k < sam_num;k++)
			{
				HitRecord record;
				bool is_hit = false;
				float tmax = 100000.0f;
				Ray r = cam.getRay(pixel_x, pixel_y, samples[k].x(),samples[k].y());
				is_hit = shapes.hit(r, 0.00001f, tmax,0.0, record);
				//���ĸ�����timeֻ����Dynamic_��ͷ����״��(����ͨ��ʱ��ı���״����)��Ч,������ͨ����״����Ч.
				//���ҵ��ĸ�����������(0,1)��Χ�ڵ���ʱ����ص���,
				//���ź�����,�������������ʵʱ��,ֻ��һ��һ��ͼƬ����ͨ��ѭ��һ�δ�ӡ����ͼƬ,
				//�������������ǳ��ķ��ڴ�,��Ϊ�����ڵ����ݼ��㶼����CPU��������GPU�ϵ�,
				//�����Ҫ���ԵĶ���Ч������һ������Ⱦ60�����ϵ�ͼƬ���ҳ�����win32Ӧ�ó�����,
				//����������Win32���(����ʹ�����е�ͼ�ο��QT)�ͼ�ν�����ΪͼƬ����;
				//�ڶ����Ǽ���GPU��C++���д���,�Ѹ��ӵ����ݼ��㶪��GPU���п��ܼ�����Ⱦ.
				if (is_hit)
					total_color += 0.5*rgb(record.normal.x()+1,record.normal.y()+1,record.normal.z()+1);
				else
				{
					float  Y_interpolation = (r.direction().y() + 1.0)*0.5;
					//ray��direction�����Ѿ���λ��,��Χ��[-1,1].
					//��ȡdirection������y����Ȼ��תΪ��ΧΪ[0,1]��Y�᷽��Ĳ�ֵ
					total_color += Y_interpolation*rgb(0.5,0.7,1.0) + (1.0 - Y_interpolation)*rgb(1.0,1.0,1.0);
					//������ɫ���ɫ��ֵ
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