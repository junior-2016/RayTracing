#include"image.h"
#include"ImageTexture.h"
#include<string>
#define M_PI 3.14159265358979323846
using namespace std;
ImageTexture::ImageTexture(char* file_name)
{
	img = new image();
	img->readPPM(file_name);
}
rgb ImageTexture::value(const Vector2& uv, const Vector3& p)const
{
	float u = uv.x() - int(uv.x());
	float v = uv.y() - int(uv.y());
	u *= (img->width() - 3);
	v *= (img->height() - 3);
	int iu = (int)u;
	int iv = (int)v;
	float tu = u - iu;
	float tv = v - iv;
	rgb color = img->getColor(iu, iv)*(1 - tu)*(1 - tv) +
		img->getColor(iu + 1, iv)*tu*(1 - tv) +
		img->getColor(iu, iv + 1)*(1 - tu)*tv +
		img->getColor(iu + 1, iv + 1)*tu*tv;
	return color;
}
