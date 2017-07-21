#ifndef NOISE_TEXTURE_WRAP_H
#define NOISE_TEXTURE_WRAP_H
#include"Texture.h"
#include"rgb.h"
#include"SolidNoise.h"
#include<cmath>
#include<ctime>
class NoiseTextureWrap:public Texture 
	//NoiseTextureWrap是基于包裹系数(expansion)将基本固体噪声系数变化,从而使纹理图像变形.
{
private:
	float scale;
	rgb c0, c1;
	SolidNoise solid_noise;
	int expansion;
public:
	NoiseTextureWrap(int _expansion=1,float _scale = 1.0f) :scale(_scale),expansion(_expansion)
	{
		c1 = rgb(0.0, 0.0, 0.0);
		c0 = rgb(0.7, 1.0, 0.5);
	}
	NoiseTextureWrap(const rgb& _c0, const rgb& _c1, int _expansion=1,float _scale = 1.0f) :
		c0(_c0), c1(_c1), scale(_scale),expansion(_expansion) {}
	rgb value(const Vector2& uv, const Vector3& hit_point)const;
};
#endif // !NOISE_TEXTURE_WRAP_H

