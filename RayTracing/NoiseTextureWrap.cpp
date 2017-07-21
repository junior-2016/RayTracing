#include"NoiseTextureWrap.h"
rgb NoiseTextureWrap::value(const Vector2& uv, const Vector3& hit_point)const
{
	float t = (1.0f + solid_noise.NoiseValue(hit_point*scale)) / 2.0f; //t在(0,1)范围
	t = t*expansion; //t乘以放大倍数(包裹)
	t = t - floor(t); //t=t-[t],[t]为不大于t的最大整数
	return t*c0 + (1.0f - t)*c1;//进行插值
}