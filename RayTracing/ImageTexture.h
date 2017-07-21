#ifndef IMAGE_TEXTURE_H
#define IMAGE_TEXTURE_H
#include"Texture.h"
#include"image.h"
#include"rgb.h"
#include<cmath>
class ImageTexture :public Texture
{
private:
	image* img;
public:
	ImageTexture(char* file_name);
	rgb value(const Vector2& uv, const Vector3& p)const;
};
#endif // !IMAGE_TEXTURE_H
