#ifndef MESH_TRIANGLE_H
#define MESH_TRIANGLE_H
#include"Shape.h"
#include"Mesh.h"

class MeshTriangle :public Shape
{
private:
	int pointIndex[3];//三角形三个顶点的索引
	Mesh * mesh_ptr;  //网格指针
public:
	MeshTriangle(Mesh * _mesh, int p1, int p2, int p3);
	MeshTriangle();
	~MeshTriangle();
	bool hit(const Ray& ray, float tmin, float tmax, float time, HitRecord& record) const;
	bool shadowHit(const Ray& ray, float tmin, float tmax, float time) const;
};
#endif // !MESH_TRIANGLE_H

