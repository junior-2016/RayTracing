#include"SolidNoise.h"
#include"RandomNumber.h"
#include<ctime>
SolidNoise::SolidNoise()
{
	RandomNumber rm((ULL)time(NULL));
	grad[0] = Vector3(1, 1, 0);
	grad[1] = Vector3(-1, 1, 0);
	grad[2] = Vector3(1, -1, 0);
	grad[3] = Vector3(-1, -1, 0);
	grad[4] = Vector3(1, 0, 1);
	grad[5] = Vector3(-1, 0, 1);
	grad[6] = Vector3(1, 0, -1);
	grad[7] = Vector3(-1, 0, -1);
	grad[8] = Vector3(0, 1, 1);
	grad[9] = Vector3(0, -1, 1);
	grad[10] = Vector3(0, 1, -1);
	grad[11] = Vector3(0, -1, -1);

	grad[12] = Vector3(1, 1, 0);
	grad[13] = Vector3(-1, 1, 0);
	grad[14] = Vector3(0, -1, 1);
	grad[15] = Vector3(0, -1, -1);

	for (int i = 0;i < 16;i++)
	{
		index[i] = i;
	}//索引数组储存16个整数(0到15),用作索引梯度数组的下标

	 //下面用随机数混淆索引数组
	for (int i = 14;i >= 0;i--)
	{
		int target = int(rm()*i);
		int temp = index[i + 1];
		index[i + 1] = index[target];
		index[target] = temp;
	}
}
SolidNoise::SolidNoise(int seed)
{
	RandomNumber rm(seed);
	grad[0] = Vector3(1, 1, 0);
	grad[1] = Vector3(-1, 1, 0);
	grad[2] = Vector3(1, -1, 0);
	grad[3] = Vector3(-1, -1, 0);
	grad[4] = Vector3(1, 0, 1);
	grad[5] = Vector3(-1, 0, 1);
	grad[6] = Vector3(1, 0, -1);
	grad[7] = Vector3(-1, 0, -1);
	grad[8] = Vector3(0, 1, 1);
	grad[9] = Vector3(0, -1, 1);
	grad[10] = Vector3(0, 1, -1);
	grad[11] = Vector3(0, -1, -1);

	grad[12] = Vector3(1, 1, 0);
	grad[13] = Vector3(-1, 1, 0);
	grad[14] = Vector3(0, -1, 1);
	grad[15] = Vector3(0, -1, -1);

	for (int i = 0;i < 16;i++)
	{index[i] = i;}//索引数组储存16个整数(0到15),用作索引梯度数组的下标

	//下面用随机数混淆索引数组
	for (int i = 14;i >= 0;i--)
	{
		int target = int(rm()*i);
		int temp = index[i + 1];
		index[i + 1] = index[target];
		index[target] = temp;
	}
}
float SolidNoise::NoiseValue(const Vector3& p)const
{
	int fi, fj, fk;
	float fu, fv, fw, sum;
	Vector3 v;

	fi = int(floor(p.x()));
	fj = int(floor(p.y()));
	fk = int(floor(p.z()));
	fu = p.x() - float(fi);
	fv = p.y() - float(fj);
	fw = p.z() - float(fk);
	sum = 0.0;

	v = Vector3(fu, fv, fw);
	sum += NoiseSumExpression(fi, fj, fk, v);

	v = Vector3(fu - 1, fv, fw);
	sum += NoiseSumExpression(fi + 1, fj, fk, v);

	v = Vector3(fu, fv - 1, fw);
	sum += NoiseSumExpression(fi, fj + 1, fk, v);

	v = Vector3(fu, fv, fw - 1);
	sum += NoiseSumExpression(fi, fj, fk + 1, v);

	v = Vector3(fu - 1, fv - 1, fw);
	sum += NoiseSumExpression(fi + 1, fj + 1, fk, v);

	v = Vector3(fu - 1, fv, fw - 1);
	sum += NoiseSumExpression(fi + 1, fj, fk + 1, v);

	v = Vector3(fu, fv - 1, fw - 1);
	sum += NoiseSumExpression(fi, fj + 1, fk + 1, v);

	v = Vector3(fu - 1, fv - 1, fw - 1);
	sum += NoiseSumExpression(fi + 1, fj + 1, fk + 1, v);

	return sum;
}