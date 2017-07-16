#ifndef SHAPELIST_H
#define SHAPELIST_H
#include"Shape.h"
#include"DynamicArray.h"
class ShapeList:public Shape
{
private:
	DynamicArray<Shape*>Shapes;
public:
	ShapeList(){}
	virtual ~ShapeList() {
	}
	bool add(Shape* s) { return Shapes.append(s); }
	int length() { return Shapes.length(); }
	bool hit(const Ray& ray, float tmin, float tmax, float time, HitRecord& record) const;
    bool shadowHit(const Ray& ray, float tmin, float tmax, float time) const
	{return false;}
	//shadowHit������ShapeListû���κ��ô�,��ʵshadowHit()���ڻ�����һ������Api,����Ϊ�˼̳�
	//������Shape�Ӷ���ShapeList��ɿ��Դ��������ʵ����,����ʵ��shadowHit()����.
	//ʵ�����ܼ�,ֻ��Ҫ��㷵��һ��ֵ����.
};
#endif // !SHAPELIST_H

