#include"MarbleTexture.h"
#include<cmath>
MarbleTexture::MarbleTexture(image * _MarbleImg, float _perturbation, int num, float am, float fre)
	:MarbleImg(_MarbleImg), perturbation(_perturbation), fbm_noise(num, am, fre) {}
rgb MarbleTexture::value(const Vector2& uv, const Vector3& hit_point)const
{
	float noise = fbm_noise.FBMNoiseValue(hit_point);
	float y = hit_point.y() + perturbation*noise;
	float u = (1.0 + sin(y)) / 2.0;
	int row = 0;
	int column = (int)(u*(MarbleImg->width() - 1));
	return (MarbleImg->getColor(column,row));
}