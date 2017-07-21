#ifndef MARBLE_TEXTURE_H
#define MARBLE_TEXTURE_H
#include"rgb.h"
#include"SolidNoise.h"
#include"Texture.h"
#include "image.h"
#include<cmath>
class MarbleTexture :public Texture //����ʯ����,����һЩ�ض��Ĵ���ʯɫ��ͼƬȻ���ͼƬ�ϵ�һ��ɫ���ظ���ת��(�������Ǻ���)��ȡ��ɫ
{
private:
	SolidNoise solid_noise;
	image * MarbleImg;
	float perturbation;//��������ϵ��,���ϵ��Ϊ0,��û������Ӱ��
public:
	MarbleTexture(image * _MarbleImg, float _perturbation);
	rgb value(const Vector2& uv, const Vector3& hit_point)const;
};
#endif // !MARBLE_TEXTURE_H

