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
	//shadowHit方法在ShapeList没有任何用处,其实shadowHit()现在基本是一个废弃Api,但是为了继承
	//抽象类Shape从而把ShapeList变成可以创建对象的实体类,必须实现shadowHit()方法.
	//实现它很简单,只需要随便返回一个值即可.
};
#endif // !SHAPELIST_H

