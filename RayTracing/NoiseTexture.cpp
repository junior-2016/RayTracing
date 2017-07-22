#include"NoiseTexture.h"
rgb NoiseTexture::value(const Vector2& uv, const Vector3& hit_point)const
{
	float t = (1.0+solid_noise.NoiseValue(scale*hit_point))/2.0;
	
	//������ϵ����Χ��(-1,1)���(0,1)
	return t*c0 + (1.0f - t)*c1;//��������ϵ����ֵ,�õ�������ɫ
}