#ifndef RAY_H
#define RAY_H
#include"Vector3.h"
#include<iostream>
using namespace std;
class Ray
{
private:
	Vector3 data[2];
public:
	Ray(){}
	Ray(const Vector3& start_point, const Vector3& direction_vector)
	{
		data[0] = start_point;
		data[1] = direction_vector;
	}
	Ray(const Ray& r) { data[0] = r.data[0];data[1] = r.data[1];}
	Vector3 startPoint()const { return data[0]; }
	Vector3 direction() const { return data[1]; }
	Vector3 pointByParameter(float t) const
	{
		return data[0] + t*data[1];
	}
	//ͨ��ray=point+t*direction����������ϵ�ĳһ��������(һ��
	//�趨�������з�Χ��,����t�ķ�Χ[t1,t2]���Թ����[t1,t2]��Χ�Ĺ���)
	friend ostream& operator<<(ostream&out, const Ray&r);
};
inline ostream& operator<<(ostream&out, const Ray&r)
{
	out << "Ray:("<<r.startPoint() << "+t" << r.direction()<<")";
	return out;
}
#endif // !RAY_H
