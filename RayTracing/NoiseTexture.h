#ifndef NOISE_TEXTURE_H
#define NOISE_TEXTURE_H
#include"Texture.h"
#include"rgb.h"
#include"SolidNoise.h"
#include"FBMNoise.h"
#include<cmath>
#include<ctime>
class NoiseTexture:public Texture //NoiseTexture�ǻ��ڻ�����������������
{
private:

	float scale;//����ֵ,��������hit_point(�������������Ľ����)�ķ���,һ����Ϊ1.0f,�����ı�hit_point
	rgb c0, c1;//������ֵ����ɫ
	SolidNoise solid_noise;//��������,������������ϵ��
public:
	NoiseTexture(float _scale = 1.0f):scale(_scale)
	{
		c1 = rgb(0.0,0.0,0.0);
		c0 = rgb(0.7, 1.0, 0.5);
	}
	NoiseTexture(const rgb& _c0,const rgb& _c1,float _scale=1.0f):
		c0(_c0),c1(_c1),scale(_scale){}
	rgb value(const Vector2& uv, const Vector3& hit_point)const;
};
#endif // !NOISE_TEXTURE_H

