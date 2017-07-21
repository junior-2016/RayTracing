#ifndef TEXTURE_H
#define TEXTURE_H
#include"Vector2.h"
#include"Vector3.h"
#include"rgb.h"
class Texture
{
public:
	virtual rgb value(const Vector2& uv, const Vector3& hit_point)const =0;
	//纹理类通用接口
};
#endif // !TEXTURE_H

