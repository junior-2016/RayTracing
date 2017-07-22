#include"TextureSphere.h"
#include<cmath>
#define M_PI 3.14159265358979323846
TextureSphere::TextureSphere(const Vector3& _center, float _radius, Texture*_tex)
:center(_center),radius(_radius),tex(_tex){}
bool TextureSphere::hit(const Ray& ray, float tmin, float tmax, float time, HitRecord& record) const
{
	Vector3 o = ray.startPoint();
	Vector3 d = ray.direction();
	Vector3 temp = o - center;
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
		Vector3 r = o + t_result * d;
		record.hit_point = r;
		Vector3 n=record.normal = unitVector(r - center);
		record.hit_texture = tex;

		//¼ÆËãuv×ø±ê
		float twopi = 2.0*M_PI;
		float theta = acos(n.z());
		float phi = atan2(n.y(), n.x());
		if (phi < 0.0f) phi += twopi;
		float one_over_2pi = 1.0 / (2.0*M_PI);
		float one_over_pi = 1.0 / M_PI;
		record.uv = Vector2(phi*one_over_2pi, (M_PI - theta)*one_over_pi);
		return true;
	}
}
bool TextureSphere::shadowHit(const Ray& ray, float tmin, float tmax, float time) const
{
	Vector3 o = ray.startPoint();
	Vector3 d = ray.direction();
	Vector3 temp = o - center;
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