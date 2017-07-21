#ifndef SHAPE_H
#define SHAPE_H
#include<iostream>
#include"Ray.h"
#include"Vector3.h"
#include"rgb.h"
#include"Texture.h"
using namespace std;
class Ray;
class rgb;
struct HitRecord //HitRecord返回光线与平面交叉的结果
{
	float t;//光线在交叉点的t参数
	Vector3 normal;//平面在交叉点的法向量
	Vector2 uv;//用于2D纹理
	Vector3 hit_point;//the point of intersection(光线与最近物体的交叉点)
	Texture* hit_texture;//与光线交叉的最近物体的纹理指针

	rgb color;//打算废弃!!!!
};
class Shape
//Shape是一个抽象类,提供两个通用的接口(hit,shadowHit)作为光线与面的交叉函数(intersection function),
//不同的面型(三角面,圆形面,..)有不同的实现方式,具体由继承的类实现.
{
public:
	virtual bool hit(const Ray& ray, float tmin, float tmax, float time, HitRecord& record) const = 0;
	//纯虚函数,作为接口,hit接口除了判断是否交叉还返回光线与平面交叉的信息,shadowHit只返回是否交叉.
	
	virtual bool shadowHit(const Ray& ray, float tmin, float tmax, float time) const = 0;
};
#endif // !SHAPE_H

