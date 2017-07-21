#ifndef SIMPLE_TEXTURE_H
#define SIMPLE_TEXTURE_H
#include"Texture.h"

class SimpleTexture:public Texture //这是只有单一颜色的贴图
{
private:
	rgb color;
public:
	SimpleTexture(rgb c):color(c){}
	rgb value(const Vector2&, const Vector3&)const
	{
		return color;
	}
};
#endif // !SIMPLE_TEXTURE_H


