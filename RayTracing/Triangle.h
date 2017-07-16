#ifndef TRIANGLE_H
#define TRIANGLE_H
#include"Shape.h"
#include"Vector3.h"
#include"Ray.h"
#include"rgb.h"
#include<iostream>
using namespace std;
class Triangle :public Shape
{
private:
	Vector3 a, b, c;//用于表示一个三角形面的三个向量,S=a+beta*(b-a)+gamma*(c-a);
	rgb color;//用一个颜色表示一个三角形切面的像素,一个物体的颜色由多个三角形切面组成
public:
	Triangle(const Vector3& v1, const Vector3& v2, const Vector3& v3, const rgb& c);
	bool hit(const Ray& ray, float tmin, float tmax, float time, HitRecord& record) const;
	bool shadowHit(const Ray& ray, float tmin, float tmax, float time) const;
};
#endif // !TRIANGLE_H

