#include"Sphere.h"
Sphere::Sphere(const Vector3& _center, float _radius, const rgb& _color) :
	center(_center), color(_color), radius(_radius) {}
/*
RAY-SPHERE INTERSECTION:
sphere :c=center(cx,cy,cz)
        R=radius
if vector p on sphere:
(p-c)(p-c)-R^2=0;
assume p = ray = strat_point + t*direction;
       o = start_point;
	   d = direction;
	   p = o + t*d;
so: (o+td-c)(o+td-c)-R^2=0;
solve above equation:
(d·d)t^2 + 2d·(o-c)t +(o-c)·(o-c) -R^2 =0;
assume A=(d·d);
       B=2d·(o-c);
	   C=(o-c)·(o-c) -R^2;
then At^2+Bt+C=0;
then      -B(+/-)sqrt(B^2-4AC)
     t = ----------------------
	             2A
if (B^2-4AC<0)
there is no intersection
if (B^2-4AC=0)
the ray is tangent to (相切) sphere.
if (B^2-4AC>0)
the ray is intersect to (相交) sphere.one of t is to enter
the sphere and the other t is to leave sphere.

normal vector (光线与圆的交叉点的法向量):
assume vector p = ray = (x,y,z) ;
       vector c(cx,cy,cz) = center ;
then f(x,y,z)=(x-cx)^2+(y-cy)^2+(z-cz)^2-R^2=0;
then normal vector n =(fx,fy,fz)=2(x-cx,y-cy,z-cz)=2(p-c)
then unit normal vector n=n/|n|=2(p-c)/2R=(p-c)/R.

*/
bool Sphere::hit(const Ray& ray, float tmin, float tmax, float time, HitRecord& record) const
{
	Vector3 o = ray.startPoint();
	Vector3 d = ray.direction();
	Vector3 temp = o - center;
	double A = dot(d, d);
	double B = 2* dot(d, temp);
	double C = dot(temp,temp) - radius*radius;
	double beta = (B*B) - 4* A*C;
	if (beta < 0){return false;}
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
		record.normal = unitVector(r - center);
		return true;
	}
}
bool Sphere::shadowHit(const Ray& ray, float tmin, float tmax, float time) const
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