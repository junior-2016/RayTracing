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
#include"Mesh.h"
#include"MeshTriangle.h"
#include"Vertex.h"
using namespace std;
int main()
{
	int nx = 1024;
	int ny = 1024;
	image im(nx, ny);
	int sam_num = 1;
	int vertices_num = 100;
	char * file_name = "E:\\FFOutput\\3.ppm";
	VertexUVN * vertUVNs = new VertexUVN[vertices_num];//开启最多储存100个三角顶点的顶点数据结构
	Camera cam(Vector3(0, 0, 0), Vector3(0, 0, -1000), Vector3(0, 1, 0), 50, -600, 600, 600, -600, 1000);
	vertUVNs[0].vertex = Vector3(-600,600,-600);
	vertUVNs[1].vertex = Vector3(-600,0,-1200);
	vertUVNs[2].vertex = Vector3(-600,-600,-500);
	vertUVNs[3].vertex = Vector3(0,-600,-700);
	vertUVNs[4].vertex = Vector3(600,-600,-500);
	vertUVNs[5].vertex = Vector3(600,0,-1200);
	vertUVNs[6].vertex = Vector3(600,600,-600);
	vertUVNs[7].vertex = Vector3(0,600,-800);
	vertUVNs[8].vertex = Vector3(0,0,-1100);
	//uv坐标与图片的坐标相对应,uv坐标范围是[0,1]
	Vector2 img_left_bottom  = Vector2(0.0, 0.0);
	Vector2 img_left_top     = Vector2(0.0, 1.0);
	Vector2 img_right_bottom = Vector2(1.0, 0.0);
	Vector2 img_right_top    = Vector2(1.0, 1.0);

	vertUVNs[0].uv = img_left_top;
	vertUVNs[1].uv = img_left_bottom;
	vertUVNs[2].uv = img_left_top;
	vertUVNs[3].uv = img_right_top;
	vertUVNs[4].uv = img_left_top;
	vertUVNs[5].uv = img_left_bottom;
	vertUVNs[6].uv = img_left_top;
	vertUVNs[7].uv = img_right_top;
	vertUVNs[8].uv = img_right_bottom;

	Texture * tex = new ImageTexture(file_name);
	Mesh*mesh= new Mesh(tex, vertUVNs);
	
	ShapeList shapes;
	shapes.add(new MeshTriangle(mesh, 0, 1, 8));
	shapes.add(new MeshTriangle(mesh, 0, 7, 8));
	shapes.add(new MeshTriangle(mesh, 1, 2, 8));
	shapes.add(new MeshTriangle(mesh, 2, 3, 8));
	shapes.add(new MeshTriangle(mesh, 3, 4, 8));
	shapes.add(new MeshTriangle(mesh, 4, 5, 8));
	shapes.add(new MeshTriangle(mesh, 5, 6, 8));
	shapes.add(new MeshTriangle(mesh, 6, 7, 8));
	for (int i = 0;i <nx;i++)
	{
		for (int j = 0;j < ny;j++)
		{
			float pixel_x = ((float)i + 0.5f) / (float)nx;
			float pixel_y = ((float)j + 0.5f) / (float)ny;

			rgb total_color(0, 0, 0);
			for (int k = 0;k < sam_num;k++)
			{
				HitRecord record;
				bool is_hit = false;
				float tmax = 100000.0f;
				Ray r = cam.getRay(pixel_x, pixel_y);
				is_hit = shapes.hit(r, 0.00001f, tmax, 0.0, record);

				if (is_hit)
					total_color += record.hit_texture->value(record.uv, record.hit_point);
				else
				{
					total_color += rgb(0.5294, 0.8078, 0.9216);
				}

			}
			im.setColor(i, j, total_color / sam_num);
		}
	}


	ofstream of("F:\\VisualStudio Project\\ComputerGraphic\\RayTracing\\image\\MeshTriangle.ppm");
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