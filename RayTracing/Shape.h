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
struct HitRecord //HitRecord���ع�����ƽ�潻��Ľ��
{
	float t;//�����ڽ�����t����
	Vector3 normal;//ƽ���ڽ����ķ�����
	Vector2 uv;//����2D����
	Vector3 hit_point;//the point of intersection(�������������Ľ����)
	Texture* hit_texture;//����߽����������������ָ��

	rgb color;//�������!!!!
};
class Shape
//Shape��һ��������,�ṩ����ͨ�õĽӿ�(hit,shadowHit)��Ϊ��������Ľ��溯��(intersection function),
//��ͬ������(������,Բ����,..)�в�ͬ��ʵ�ַ�ʽ,�����ɼ̳е���ʵ��.
{
public:
	virtual bool hit(const Ray& ray, float tmin, float tmax, float time, HitRecord& record) const = 0;
	//���麯��,��Ϊ�ӿ�,hit�ӿڳ����ж��Ƿ񽻲滹���ع�����ƽ�潻�����Ϣ,shadowHitֻ�����Ƿ񽻲�.
	
	virtual bool shadowHit(const Ray& ray, float tmin, float tmax, float time) const = 0;
};
#endif // !SHAPE_H

