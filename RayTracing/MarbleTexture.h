#ifndef MARBLE_TEXTURE_H
#define MARBLE_TEXTURE_H
#include"rgb.h"
#include"SolidNoise.h"
#include"Texture.h"
#include "image.h"
#include<cmath>
class MarbleTexture :public Texture //大理石纹理,基于一些特定的大理石色彩图片然后从图片上的一个色带重复旋转地(利用三角函数)获取颜色
{
private:
	SolidNoise solid_noise;
	image * MarbleImg;
	float perturbation;//噪声缩放系数,如果系数为0,则没有噪声影响
public:
	MarbleTexture(image * _MarbleImg, float _perturbation);
	rgb value(const Vector2& uv, const Vector3& hit_point)const;
};
#endif // !MARBLE_TEXTURE_H

