#ifndef TEXTURE_SPHERE_H
#define TEXTURE_SPHERE_H
#include"Texture.h"
#include"Shape.h"
#include"Vector3.h"
#include"Ray.h"
class TextureSphere:public Shape
{
private:
	Vector3 center;//ÖÐÐÄ
	float radius;//°ë¾¶
	Texture * tex;//ÎÆÀí
public:
	TextureSphere(const Vector3& _center, float _radius,Texture*_tex);
	bool hit(const Ray& ray, float tmin, float tmax, float time, HitRecord& record) const;
	bool shadowHit(const Ray& ray, float tmin, float tmax, float time) const;
};
#endif // !TEXTURE_SPHERE_H

