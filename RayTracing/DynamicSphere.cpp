#include"DynamicSphere.h"
DynamicSphere::DynamicSphere(const Vector3& _center, float _radius,
	const rgb& _color, float _mintime, float _maxtime)
	:center(_center),color(_color),mintime(_mintime),maxtime(_maxtime),radius(_radius){}
Vector3 DynamicSphere::getCurrentCenter(float time)const
{
	float realtime = time*maxtime + (1.0f - time)*mintime;
	//ע�����time������(0,1)�ĸ�����,
	//realtime�ķ�Χ��[mintime,maxtime]֮��
	//realtime��ΪԲ�ƶ������Ĳ���,��Χ��mintime��maxtime����ȷ��,
	//����ͨ����ͬ��f(realtime)�������޸�Բ�ĴӶ�ʵ��Բ���ƶ�,
	//��ͬ��f(realtime)���Բ�����ͬ���ƶ�·��,����ֻʵ��Բ�������﷽�������˶��ĺ���

	return Vector3(center.x() + realtime, center.y() + realtime, center.z() + realtime);
}
bool DynamicSphere::hit(const Ray& ray, float tmin, float tmax, float time, HitRecord& record) const
{
	Vector3 new_center = getCurrentCenter(time);//��֮ǰΨһ�Ĳ�ͬ���Ǽ�����ʱ�������Բ�ĵ��޸�
	Vector3 o = ray.startPoint();
	Vector3 d = ray.direction();
	Vector3 temp = o - new_center;
	double A = dot(d, d);
	double B = 2 * dot(d, temp);
	double C = dot(temp, temp) - radius*radius;
	double beta = (B*B) - 4 * A*C;
	if (beta < 0) { return false; }
	else
	{
		beta = sqrt(beta);
		double t_result = (-B - beta) / (2 * A);
		if (t_result < tmin)
			t_result = (-B + beta) / (2 * A);
		if (t_result<tmin || t_result>tmax) return false;
		record.t = t_result;
		record.color = color;
		Vector3 r = o + t_result * d;
		record.normal = unitVector(r - new_center);
		return true;
	}
}
bool DynamicSphere::shadowHit(const Ray& ray, float tmin, float tmax, float time) const
{
	Vector3 new_center = getCurrentCenter(time);//��֮ǰΨһ�Ĳ�ͬ���Ǽ�����ʱ�������Բ�ĵ��޸�
	Vector3 o = ray.startPoint();
	Vector3 d = ray.direction();
	Vector3 temp = o - new_center;
	double A = dot(d, d);
	double B = 2 * dot(d, temp);
	double C = dot(temp, temp) - radius*radius;
	double beta = (B*B) - 4 * A*C;
	if (beta < 0) { return false; }
	else
	{
		beta = sqrt(beta);
		double t_result = (-B - beta) / (2 * A);
		if (t_result < tmin)
			t_result = (-B + beta) / (2 * A);
		if (t_result<tmin || t_result>tmax) return false;
		return true;
	}
}