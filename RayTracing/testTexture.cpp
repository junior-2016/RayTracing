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
	注意进行纹理测试时最好不要使用之前对光线点的采样处理方法！！！否则进行纹理时产生的图片会比较模糊.
	可以使用Camera类的另一个重载函数getRay(float,float),这个重载函数固定光线起始点为相机中心点.
	同时注意要设置sam_num为1.
	*/

	//NoiseTexture的特点,参数scale从1.0逐渐降低,纹理条纹越明显(最好在0.01,0.02,0.05,0.1x等较小的浮点数比较明显)
	//Texture * tex = new NoiseTexture(0.02);

	//NoiseTextureWrap的特点,scale设置在0.01,0.02,0.05,...之间(较小浮点数),然后expansion参数设置为4,8等就有明显效果.
	//Texture *tex = new NoiseTextureWrap(8,0.01);
    //Texture * tex = new NoiseTextureWrap(8, 0.02);

	
	//测试MarbleTexture:
	/*
	char * file_name = "F:\\VisualStudio Project\\ComputerGraphic\\RayTracing\\srcImage\\BlueMarbleRamp.ppm";
	image * MarbleImg = new image();
	MarbleImg->readPPM(file_name);
	Texture * tex = new MarbleTexture(MarbleImg,8,6,0.75,2);//第二个参数为噪声缩放系数,如果设置为0则没有噪声影响
	*/
	
	//测试图片纹理(ImageTexture)
	//无意中发现一个特殊的纹理效果,在图片纹理中使用随机数rm()对光线起始点采样可能会有玻璃模糊效果
	/*
	char * file_name = "E:\\FFOutput\\111.ppm";
	Texture * tex = new ImageTexture(file_name);
	*/

	//以后比较合适的Camera的配置范例是:
	//Camera cam(Vector3(0, 0, 0), Vector3(0, 0, -1000), Vector3(0, 1, 0), 50, -300,300,300,-300, 1000);
	//然后把物体放在Vector(0,0,-1000),半径大概在(200,250)以内.
	//因为物体是球体,所以把照相机按同等距离旋转到球的左边也可以,这个时候需要改变第一个参数:照相机的起始点,以及第二个参数:gaze向量(=成像平面中心坐标-照相机中心坐标)
    //同时还要注意最后一个参数是成像平面与照相机的距离,其实就是gaze向量的模长,如果gaze向量的模长改变最后一个参数也要变化.
	//此时Camera的配置是:Camera cam(Vector3(-1000,0,-1000), Vector3(1000, 0,0), Vector3(0, 1, 0), 50, -300,300,300, -300, 1000);
	//以后熟练了后就不需要再利用上面的配置了
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
				//因为是与纹理相关,getRay方法使用第二个,不进行光线点采样,否则贴图会模糊.
				//同时这里需要设置sam_num=1(不破坏原来的代码结构),
				//同时最好把与采样相关的代码注释掉,这样可以加快渲染)

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