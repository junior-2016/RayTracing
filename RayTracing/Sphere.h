#ifndef SPHERE_H
#define SPHERE_H
#include"Shape.h"
class Sphere :public Shape
{
private:
	Vector3 center;//ÖÐÐÄ
	float radius;//°ë¾¶
	rgb color;
public:
	Sphere(const Vector3& _center, float _radius, const rgb& _color);
	bool hit(const Ray& ray, float tmin, float tmax, float time, HitRecord& record) const;
    bool shadowHit(const Ray& ray, float tmin, float tmax, float time) const;
};
#endif // !SPHERE_H

