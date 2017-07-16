#ifndef RANDOM_NUMBER_H
#define RANDOM_NUMBER_H
typedef unsigned long long ULL;
class RandomNumber
{
private:
	ULL seed;
	ULL mult;
	ULL llong_max;
	float float_max;
public:
	RandomNumber(ULL _seed = 7564231ULL) :seed(_seed),
		mult(62089911ULL), llong_max(4294967295ULL),
		float_max(4294967295.0f) {}
	float operator()();

};
inline float RandomNumber::operator()()
{
	seed = mult*seed;
	return float(seed%llong_max) / float_max;
}
#endif // !RANDOM_NUMBER_H

