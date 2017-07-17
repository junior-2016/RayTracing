#ifndef SAMPLE_H
#define SAMPLE_H
#include"Vector2.h"
#include"RandomNumber.h"
class Sample
{
private:
	RandomNumber rm;
public:
	Sample(ULL seed);
	
	//2D Square(之前写成了Retangle) samples:
	void random(Vector2*samples, int num_samples);
	void jitter(Vector2*samples, int num_samples);
	void nrooks(Vector2*samples, int num_samples);
	void multiJitter(Vector2*samples, int num_samples);

	//1D samples:


	//Filter Algorithm

	//Disk from Square Samples
	//有两种算法将正方形的采样点转化为单位圆(Disk)的采样点,
	//一种是采用蒙特卡洛方法,利用概率密度函数将处于圆形区域的采样点保留,剩下的丢弃,又称Reject Sample(丢弃采样),
	//这种方法不会将采样点的相对位置改变(No Distortion:无变形)但是有损失;
	//另一种是保留全部的采样点,不会有损失但是需要保证较低的变形(Low Distortion)
	//后面只实现第二种算法:
	/*
	第一种思路(polor map 极坐标映射)
	r = sqrt(X) (x与半径映射)
	¢ = 2*pi*y  (y与以圆心为极点的极角¢映射)
	实现了连续,
	但是这种映射不是双射(没有反函数)

	第二种思路(concentric map 同心映射)
	从正方形(a,b)->(r,¢) ,其中a,b都是[-1,1].
	当a+b>0且a-b>0(由b=a与b=-a划分的第一个三角形区域),有
	r = a;
	¢ = (pi/4)*(b/a);
	*/
	void SquareToDisk(Vector2*squareSamples,int num_samples);
};
#endif // !SAMPLE_H


