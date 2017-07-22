#include"NoiseTexture.h"
rgb NoiseTexture::value(const Vector2& uv, const Vector3& hit_point)const
{
	float t = (1.0+solid_noise.NoiseValue(scale*hit_point))/2.0;
	
	//将噪声系数范围从(-1,1)变成(0,1)
	return t*c0 + (1.0f - t)*c1;//利用噪声系数插值,得到最终颜色
}