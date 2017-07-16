#include"DynamicSphere.h"
DynamicSphere::DynamicSphere(const Vector3& _center, float _radius,
	const rgb& _color, float _mintime, float _maxtime)
	:center(_center),color(_color),mintime(_mintime),maxtime(_maxtime),radius(_radius){}
Vector3 DynamicSphere::getCurrentCenter(float time)const
{
	float realtime = time*maxtime + (1.0f - time)*mintime;
	//注意参数time必须是(0,1)的浮点数,
	//realtime的范围在[mintime,maxtime]之间
	//realtime作为圆移动函数的参数,范围由mintime和maxtime参数确定,
	//可以通过不同的f(realtime)函数来修改圆心从而实现圆的移动,
	//不同的f(realtime)可以产生不同的移动路径,下面只实现圆沿右上里方向线性运动的函数

	return Vector3(center.x() + realtime, center.y() + realtime, center.z() + realtime);
}
bool DynamicSphere::hit(const Ray& ray, float tmin, float tmax, float time, HitRecord& record) const
{
	Vector3 new_center = getCurrentCenter(time);//跟之前唯一的不同就是加入了时间参数对圆心的修改
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
	Vector3 new_center = getCurrentCenter(time);//跟之前唯一的不同就是加入了时间参数对圆心的修改
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