#include"FBMNoise.h"
FBMNoise::FBMNoise(int _num_octaves, float _amplitude, float _frequency)
	:num_octaves(_num_octaves),amplitude(_amplitude),frequency(_frequency){}
float FBMNoise::FBMNoiseValue(const Vector3& p) const
{
	/*
	calculate fbm bounds
	*/
	float fbm_max, fbm_min;
	if (amplitude == 1.0)
		fbm_max = num_octaves;
	else
		fbm_max = (1.0 - pow(amplitude, num_octaves)) / (1.0 - amplitude);
	fbm_min = -fbm_max;

	/*
	calculate fbm value
	*/
	float 	amplitude_change = 1.0;
	float	frequency_change = 1.0;
	float 	fbm = 0.0;

	for (int j = 0; j < num_octaves; j++) {
		fbm += amplitude_change * noise.NoiseValue(frequency_change * p);
		amplitude_change *= amplitude;
		frequency_change *= frequency;
	}

	fbm = (fbm - fbm_min) / (fbm_max - fbm_min);  // map to [0, 1]

	return (fbm);
}