#ifndef SOLID_NOISE_H
#define SOLID_NOISE_H
#include<cmath>
#include"Vector3.h"
class SolidNoise
{
private:
	Vector3 grad[16];//�ݶ�����,����ǰ��12��Ԫ��ȡ������12���ߵ��е�,ʣ�µ�4����ȡ
	int index[16];//��������,��Ϊ�����ݶ�����������
public:
	SolidNoise();
	//ʵ��һ�ֻ�����������:Perlin Noise
	SolidNoise(int seed);
	float NoiseInterpolation(float t)const;//��ֵ����
	Vector3 getGradByIndex(int, int, int)const;//����(i,j,k)��ȡ��Ӧ�������ݶ�����
	float NoiseSumExpression(int, int, int, Vector3&)const;//�����ĸ�������
	float NoiseValue(const Vector3&)const;//��ȡ����ϵ��,ϵ���ķ�Χ[-1,1]
};
inline float SolidNoise::NoiseInterpolation(float t)const
{
	t = (t > 0.0) ? t : -t;
	return (t < 1.0) ? (-6 * t*t*t*t*t + 15 * t*t*t*t - 10 * t*t*t + 1) : 0.0;
}
inline Vector3 SolidNoise::getGradByIndex(int i, int j, int k)const
{
	int idx;
	idx = index[abs(k) % 16];
	idx = index[abs(j + idx) % 16];
	idx = index[abs(i + idx) % 16];
	return grad[idx];
}
inline float SolidNoise::NoiseSumExpression(int i, int j, int k, Vector3&v)const
{
	return (NoiseInterpolation(v.x())*NoiseInterpolation(v.y())*NoiseInterpolation(v.z())*(dot(getGradByIndex(i, j, k), v)));
}
#endif // !SOLID_NOISE_H

