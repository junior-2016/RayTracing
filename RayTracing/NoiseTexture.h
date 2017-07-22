#ifndef NOISE_TEXTURE_H
#define NOISE_TEXTURE_H
#include"Texture.h"
#include"rgb.h"
#include"SolidNoise.h"
#include"FBMNoise.h"
#include<cmath>
#include<ctime>
class NoiseTexture:public Texture //NoiseTexture是基于基本固体噪声的纹理
{
private:

	float scale;//幅度值,用来调节hit_point(光线与最近物体的交叉点)的幅度,一般设为1.0f,即不改变hit_point
	rgb c0, c1;//用来插值的颜色
	SolidNoise solid_noise;//固体噪声,用来计算噪声系数
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

