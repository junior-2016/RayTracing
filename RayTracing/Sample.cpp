#include"Sample.h"
#include"Vector2.h"
#include<cmath>
#include<cstdlib>
Sample::Sample(ULL seed):
	rm(seed){}
void Sample::random(Vector2*samples, int num_samples)
{
	for (int i = 0;i < num_samples;i++)
	{
		samples[i].setX(rm());
		samples[i].setY(rm());
	}
}

void Sample::jitter(Vector2*samples, int num_samples)
{
	int sqrt_samples = (int)(sqrt(num_samples));
	//这里假定采样点数目是可以开方为正整数的
	for (int i=0;i<sqrt_samples;i++)
		for (int j = 0;j < sqrt_samples;j++)
		{
			float x = ((float)i + rm()) / (float)sqrt_samples;
			float y = ((float)j + rm()) / (float)sqrt_samples;
			(samples[i*sqrt_samples + j]).setX(x);
			(samples[i*sqrt_samples + j]).setY(y);
		}
}
void Sample::nrooks(Vector2*samples, int num_samples)
{
	//将采样点分布在对角线上
	for (int i = 0;i < num_samples;i++)
	{
		samples[i].setX(((float)i + rm()) / (float)num_samples);
		samples[i].setY(((float)i + rm()) / (float)num_samples);
	}
	//shuffle the x coords.(将成对角线的采样点在x方向散开)
	for (int i = num_samples - 2;i >= 0;i--)
	{
		int target = int(rm()*(float)i);
		float temp = samples[i + 1].x();
		samples[i + 1].setX(samples[target].x());
		samples[target].setX(temp);
	}
}
void Sample::multiJitter(Vector2*samples, int num_samples)//综合Jitter与nrooks
{
	int sqrt_samples = (int)sqrt(num_samples);
	float subcell_width = (1.0f) / (float(num_samples));

	for (int i = 0;i < sqrt_samples;i++)
	{
		for (int j = 0;j < sqrt_samples;j++)
		{
			samples[i*sqrt_samples + j].setX(
				i*sqrt_samples*subcell_width +
				j*subcell_width + rm()*subcell_width
			);
			samples[i*sqrt_samples + j].setY(
				j*sqrt_samples*subcell_width +
				i*subcell_width + rm()*subcell_width
			);
		}
	}

	
	for (int i = 0;i < sqrt_samples;i++)
	{
		for (int j = 0;j < sqrt_samples;j++)
		{
			//shuffle x coords within each column(竖行)
			int k = j + int(rm()*(sqrt_samples - j - 1));
			float temp = samples[i*sqrt_samples + j].x();
			samples[i*sqrt_samples + j].setX(samples[i*sqrt_samples + k].x());
			samples[i*sqrt_samples + k].setX(temp);

			//shuffle y coords within each row(横行)
			k = j + int(rm()*(sqrt_samples - j - 1));
			temp = samples[j*sqrt_samples + i].x();
			samples[j*sqrt_samples + i].setY(samples[k*sqrt_samples + i].y());
			samples[k*sqrt_samples + i].setY(temp);
		}
	}

}
