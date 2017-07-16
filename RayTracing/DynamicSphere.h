#ifndef DYNAMICSPHERE_H
#define DYNAMICSPHERE_H
#include"Shape.h"
#include"Vector3.h"
#include"Ray.h"
#include"rgb.h"
class DynamicSphere :public Shape
{
private:
	Vector3 center;
	float mintime;
	float maxtime;
	float radius;
	rgb color;
public:
	DynamicSphere(const Vector3& _center, float _radius,
		const rgb& _color, float _mintime, float _maxtime);
	Vector3 getCurrentCenter(float time)const;
	bool hit(const Ray& ray, float tmin, float tmax, float time, HitRecord& record) const;
	bool shadowHit(const Ray& ray, float tmin, float tmax, float time) const;
};
#endif // !DYNAMICSPHERE_H

