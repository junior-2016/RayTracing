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
	
	//2D samples:
	void random(Vector2*samples, int num_samples);
	void jitter(Vector2*samples, int num_samples);
	void nrooks(Vector2*samples, int num_samples);
	void multiJitter(Vector2*samples, int num_samples);

	//1D samples:


	//Filter Algorithm

};
#endif // !SAMPLE_H


