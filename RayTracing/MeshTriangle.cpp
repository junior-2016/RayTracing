#include"MeshTriangle.h"
#include"Mesh.h"
MeshTriangle::MeshTriangle(Mesh * _mesh, int p1, int p2, int p3)
	:mesh_ptr(_mesh)
{
	pointIndex[0] = p1;
	pointIndex[1] = p2;
	pointIndex[2] = p3;
}
MeshTriangle::MeshTriangle(){}
MeshTriangle::~MeshTriangle()
{
	delete[] mesh_ptr;
}
bool MeshTriangle::hit(const Ray& ray, float tmin, float tmax, float time, HitRecord& record) const
{
	//获取网格里的顶点数据
	VertexUVN * vertUVNs = mesh_ptr->getVertUVNs();
	//获取三角形的三个顶点
	Vector3 a(vertUVNs[pointIndex[0]].vertex);
	Vector3 b(vertUVNs[pointIndex[1]].vertex);
	Vector3 c(vertUVNs[pointIndex[2]].vertex);
	//计算光线与三角形是否交叉
	float t_result, beta, gamma, denom;
	Vector3 O = a - ray.startPoint();
	Vector3 B = a - b;
	Vector3 C = a - c;
	Vector3 D = ray.direction();
	denom = tripleProduct(B, C, D);
	if (denom != 0)
	{
		beta = tripleProduct(O, C, D) / denom;
		if (beta <= 0.0f || beta >= 1.0f) return false;
		gamma = tripleProduct(B, O, D) / denom;
		if (gamma <= 0.0f || beta + gamma >= 1.0f) return false;
		t_result = tripleProduct(B, C, O) / denom;
		if (t_result<tmin || t_result>tmax) return false;
	
		//记录record信息
		//先计算UV坐标(三角形UV坐标计算需要先有网格里的原始UV数据)
		float alpha = 1.0f - beta - gamma;
		Vector2 UVa((vertUVNs[pointIndex[0]]).uv);
		Vector2 UVb((vertUVNs[pointIndex[1]]).uv);
		Vector2 UVc((vertUVNs[pointIndex[2]]).uv);
		record.uv = Vector2(alpha*UVa.x() + beta*UVb.x() + gamma*UVc.x(),
			alpha*UVa.y() + beta*UVb.y() + gamma*UVc.y());

		record.t = t_result;
		record.hit_texture = mesh_ptr->getTexture();
		record.normal = unitVector(cross(b - a, c - a));
		return true;
	}
	else
		return false;
}
bool MeshTriangle::shadowHit(const Ray& ray, float tmin, float tmax, float time) const
{
	//获取网格里的顶点数据
	VertexUVN * vertUVNs = mesh_ptr->getVertUVNs();
	//获取三角形的三个顶点
	Vector3 a(vertUVNs[pointIndex[0]].vertex);
	Vector3 b(vertUVNs[pointIndex[1]].vertex);
	Vector3 c(vertUVNs[pointIndex[2]].vertex);
	float t_result, beta, gamma, denom;
	Vector3 O = a - ray.startPoint();
	Vector3 B = a - b;
	Vector3 C = a - c;
	Vector3 D = ray.direction();
	denom = tripleProduct(B, C, D);
	if (denom != 0)
	{
		beta = tripleProduct(O, C, D) / denom;
		if (beta <= 0.0f || beta >= 1.0f) return false;
		gamma = tripleProduct(B, O, D) / denom;
		if (gamma <= 0.0f || beta + gamma >= 1.0f) return false;
		t_result = tripleProduct(B, C, O) / denom;
		return (t_result >= tmin&&t_result <= tmax);
	}
	else
		return false;
}