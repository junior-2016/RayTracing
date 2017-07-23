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
#include"Sphere.h"
#include"ShapeList.h"
#include"RandomNumber.h"
#include"Vector2.h"
#include<ctime>
#include"Sample.h"
#include"Camera.h"
#include"Texture.h"
#include"NoiseTexture.h"
#include"MarbleTexture.h"
#include"SimpleTexture.h"
#include"NoiseTextureWrap.h"
#include"TextureSphere.h"
#include"ImageTexture.h"
using namespace std;
int main()
{
	int nx = 1024;
	int ny = 1024;
	image im(nx, ny);
	int sam_num = 1;
	RandomNumber rm((ULL)time(NULL));
*/
	/*
	ע������������ʱ��ò�Ҫʹ��֮ǰ�Թ��ߵ�Ĳ��������������������������ʱ������ͼƬ��Ƚ�ģ��.
	����ʹ��Camera�����һ�����غ���getRay(float,float),������غ����̶�������ʼ��Ϊ������ĵ�.
	ͬʱע��Ҫ����sam_numΪ1.
	*/

	//NoiseTexture���ص�,����scale��1.0�𽥽���,��������Խ����(�����0.01,0.02,0.05,0.1x�Ƚ�С�ĸ������Ƚ�����)
	//Texture * tex = new NoiseTexture(0.02);

	//NoiseTextureWrap���ص�,scale������0.01,0.02,0.05,...֮��(��С������),Ȼ��expansion��������Ϊ4,8�Ⱦ�������Ч��.
	//Texture *tex = new NoiseTextureWrap(8,0.01);
    //Texture * tex = new NoiseTextureWrap(8, 0.02);

	
	//����MarbleTexture:
	/*
	char * file_name = "F:\\VisualStudio Project\\ComputerGraphic\\RayTracing\\srcImage\\BlueMarbleRamp.ppm";
	image * MarbleImg = new image();
	MarbleImg->readPPM(file_name);
	Texture * tex = new MarbleTexture(MarbleImg,8,6,0.75,2);//�ڶ�������Ϊ��������ϵ��,�������Ϊ0��û������Ӱ��
	*/
	
	//����ͼƬ����(ImageTexture)
	//�����з���һ�����������Ч��,��ͼƬ������ʹ�������rm()�Թ�����ʼ��������ܻ��в���ģ��Ч��
	/*
	char * file_name = "E:\\FFOutput\\111.ppm";
	Texture * tex = new ImageTexture(file_name);
	*/

	//�Ժ�ȽϺ��ʵ�Camera�����÷�����:
	//Camera cam(Vector3(0, 0, 0), Vector3(0, 0, -1000), Vector3(0, 1, 0), 50, -300,300,300,-300, 1000);
	//Ȼ����������Vector(0,0,-1000),�뾶�����(200,250)����.
	//��Ϊ����������,���԰��������ͬ�Ⱦ�����ת��������Ҳ����,���ʱ����Ҫ�ı��һ������:���������ʼ��,�Լ��ڶ�������:gaze����(=����ƽ����������-�������������)
    //ͬʱ��Ҫע�����һ�������ǳ���ƽ����������ľ���,��ʵ����gaze������ģ��,���gaze������ģ���ı����һ������ҲҪ�仯.
	//��ʱCamera��������:Camera cam(Vector3(-1000,0,-1000), Vector3(1000, 0,0), Vector3(0, 1, 0), 50, -300,300,300, -300, 1000);
	//�Ժ������˺�Ͳ���Ҫ�����������������
/*
	Camera cam(Vector3(0,0,0), Vector3(0,0,-1000), Vector3(0, 1, 0), 50, -600, 600, 600, -600, 1000);

	ShapeList shapes;
	shapes.add(new TextureSphere(Vector3(0,0, -1000),500, tex));

	for (int i = 0;i <nx;i++)
	{
		for (int j = 0;j < ny;j++)
	   {
			float pixel_x = ((float)i +0.5f) / (float)nx;
			float pixel_y = ((float)j +0.5f) / (float)ny;
			
			rgb total_color(0, 0, 0);
		  //Vector2*samples = new Vector2[sam_num];
		  //Sample sm((ULL)time(NULL));
		  //sm.jitter(samples, sam_num);
		  //sm.SquareToDisk(samples, sam_num);
			
			for (int k = 0;k < sam_num;k++)
			{
				HitRecord record;
			    bool is_hit = false;
			    float tmax = 100000.0f;
			    Ray r = cam.getRay(pixel_x, pixel_y);
				//��Ϊ�����������,getRay����ʹ�õڶ���,�����й��ߵ����,������ͼ��ģ��.
				//ͬʱ������Ҫ����sam_num=1(���ƻ�ԭ���Ĵ���ṹ),
				//ͬʱ��ð��������صĴ���ע�͵�,�������Լӿ���Ⱦ)

			    is_hit = shapes.hit(r, 0.00001f, tmax,0.0, record);
				
			    if (is_hit)
			       total_color += record.hit_texture->value(record.uv,record.hit_point);
			    else
			    {
					total_color += rgb(0.5294,0.8078,0.9216);
			    }
				
			}
			   im.setColor(i, j,total_color/sam_num);
			 //delete[] samples;
	  }
   }
 
	
		ofstream of("F:\\VisualStudio Project\\ComputerGraphic\\RayTracing\\image\\MarbleTextureSphere.ppm");
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
*/