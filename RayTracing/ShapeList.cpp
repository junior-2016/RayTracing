#include"ShapeList.h"
using namespace std;
bool ShapeList::hit(const Ray& ray, float tmin, float tmax, float time, HitRecord& record) const
{
	HitRecord temp;
	record.t = tmax;
	bool hit_something = false;
	for (int i = 0; i < Shapes.length(); i++) {
		if (Shapes[i]->hit(ray, tmin, record.t, time, temp)) {
			record = temp;
			hit_something = true;
		}
	}
	return hit_something;
}