/*
网格类:利用网格储存一系列三角形的顶点数据和材质,纹理数据,然后三角形绑定一个网格,利用三角形的索引
从网格中获取数据.理论上一个网格指针可以给多个三角形绑定,因为一个网格指针可以存储多个三角形的信息.
如果三角形足够多就可以建立真实的模型.
*/
#ifndef MESH_H
#define MESH_H
#include"Vertex.h"
#include"Texture.h"
#include"Shape.h"
class Mesh 
{
private:
	Texture * tex; //网格的贴图
	VertexUVN * vertUVNs; //网格的顶点数据(顶点坐标,UV坐标以及顶点所在平面的法向量,如果是同一个三角形平面,三个角的法向量是相同的)

	//注意vertUVNs在存储三角形原始UV坐标时,是利用三角形顶点在[0,1]x[0,1]坐标系所占比例来确定的.
	//比如:下面图形是由四个三角形组成的,uv坐标以三角形顶点在[0,1]坐标系的比例确定
	//所以UV坐标分别为:A(0.0,1.0)B(0.0,0.0)C(0.5,0.5)D(0.5,0.0)E(1.0,1.0)F(1.0,0.0)
	//如果这个图形是折叠的,也就是这几个三角形不在同一个平面,就把他们投影到同一个2D平面,计算出原始的UV坐标然后填充到网格数据里,
	//后期还会通过网格三角形的计算确定最后的UV坐标.
	/*
	     C
  A . . . . . . .E
	.     .     .
	.     .     .
  B	. . . . . . .
         D      F
	*/
public:
	Mesh();
	~Mesh();
	Mesh(Texture*_tex,VertexUVN*_vertUVNs);
	Texture* getTexture()const;
	VertexUVN* getVertUVNs()const;
};
#endif // !MESH_H
