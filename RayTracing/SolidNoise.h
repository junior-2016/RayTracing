#ifndef SOLID_NOISE_H
#define SOLID_NOISE_H
#include<cmath>
#include"Vector3.h"
class SolidNoise
{
private:
	Vector3 grad[16];//梯度数组,其中前面12个元素取正方体12条边的中点,剩下的4个任取
	int index[16];//索引数组,作为索引梯度向量的数组
public:
	SolidNoise();
	//实现一种基本固体噪声:Perlin Noise
	SolidNoise(int seed);
	float NoiseInterpolation(float t)const;//插值函数
	Vector3 getGradByIndex(int, int, int)const;//利用(i,j,k)获取对应索引的梯度向量
	float NoiseSumExpression(int, int, int, Vector3&)const;//噪声的辅助函数
	float NoiseValue(const Vector3&)const;//获取噪声系数,系数的范围[-1,1]
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

