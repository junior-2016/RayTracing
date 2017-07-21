#include"MarbleTexture.h"
#include<cmath>
MarbleTexture::MarbleTexture(image * _MarbleImg, float _perturbation)
	:MarbleImg(_MarbleImg),perturbation(_perturbation){}
rgb MarbleTexture::value(const Vector2& uv, const Vector3& hit_point)const
{
	float noise = (1.0+solid_noise.NoiseValue(hit_point*0.5))/2.0;//把噪声处理到[0,1]
	float y = hit_point.y() + perturbation*noise;
	float u = (1.0 + sin(y)) / 2.0;
	int row = 0;
	int column = (int)(u*(MarbleImg->width() - 1));
	return (MarbleImg->getColor(column,row));
}