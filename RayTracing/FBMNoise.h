#ifndef FBM_NOISE_H
#define FBM_NOISE_H
#include "SolidNoise.h"
#include"Vector3.h"
#include<cmath>
class FBMNoise //�Ի���������ϵ������FBM��ͺ��γɵ�������
{
private:
	int num_octaves;//��ʹ���
	float amplitude;//���
	float frequency;//Ƶ��
	SolidNoise noise;
public:
	FBMNoise(int _num_octaves, float _amplitude, float _frequency);
	float FBMNoiseValue(const Vector3& p) const;
};
#endif // !FBM_NOISE_H
