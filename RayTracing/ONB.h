#ifndef ONB_H //Orthonormal Basis Class,即标准正交化坐标系类
#define ONB_H
#include"Vector3.h"
class ONB
{
private:
	Vector3 U, V, W;//U,V,W分别是三个正交坐标系的方向向量(单位向量)
public:
	ONB() {}
	ONB(const Vector3& u, const Vector3& v, const  Vector3& w)
	:U(u),V(v),W(w){}
	void set(const Vector3& u, const Vector3& v, const Vector3& w)
	{
		U = u;V = v;W = w;
	}
	Vector3 u()const { return U; }
	Vector3 v()const { return V; }
	Vector3 w()const { return W; }
	void initFromU(const Vector3& u);
	void initFromV(const Vector3& v);
	void initFromW(const Vector3& w);
	void initFromUV(const Vector3& u, const Vector3& v);
	void initFromVU(const Vector3& v, const Vector3& u);
	void initFromUW(const Vector3& u, const Vector3& w);
	void initFromWU(const Vector3& w, const Vector3& u);
	void initFromVW(const Vector3& v, const Vector3& w);
	void initFromWV(const Vector3& w, const Vector3& v);
	friend istream& operator >> (istream& in, ONB&onb);
	friend ostream& operator<< (ostream& out, ONB&onb);
	friend bool operator==(const ONB& o1, const ONB& o2);

};
#endif // !ONB_H

