#include"NoiseTextureWrap.h"
rgb NoiseTextureWrap::value(const Vector2& uv, const Vector3& hit_point)const
{
	float t = (1.0f + solid_noise.NoiseValue(hit_point*scale)) / 2.0f; //t��(0,1)��Χ
	t = t*expansion; //t���ԷŴ���(����)
	t = t - floor(t); //t=t-[t],[t]Ϊ������t���������
	return t*c0 + (1.0f - t)*c1;//���в�ֵ
}