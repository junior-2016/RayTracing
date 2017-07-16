#include"Vector3.h"
using namespace std;
ostream& operator<<(ostream& out, const Vector3& v)
{
	out << "(" << v.elem[0] << "," << v.elem[1] << "," << v.elem[2] << ")";
	return out;
}
istream& operator>> (istream& in, Vector3& v)
{
	float f;
	in >> f;
	v.elem[0] = f;
	in >> f;
	v.elem[1] = f;
	in >> f;
	v.elem[2] = f;
	return in;
}
float tripleProduct(const Vector3& v1, const Vector3& v2, const Vector3& v3)
{
	return dot(v1,cross(v2,v3));
	/*
	tripleProduct(v1,v2,v3)按照三阶行列式的顺序:
	|v1x,v1y,v1z|
	|v2x,v2y,v2z|=tripleProduct(v1,v2,v3).
	|v3x,v3y,v3z|
	*/
}