#ifndef FBM_NOISE_H
#define FBM_NOISE_H
#include "SolidNoise.h"
#include"Vector3.h"
#include<cmath>
class FBMNoise //对基本的噪声系数进行FBM求和后形成的新噪声
{
private:
	int num_octaves;//求和次数
	float amplitude;//振幅
	float frequency;//频率
	SolidNoise noise;
public:
	FBMNoise(int _num_octaves, float _amplitude, float _frequency);
	float FBMNoiseValue(const Vector3& p) const;
};
#endif // !FBM_NOISE_H
