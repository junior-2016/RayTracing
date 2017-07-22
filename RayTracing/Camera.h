#ifndef CAMERA_H
#define CAMERA_H
#include"ONB.h"
#include"Vector3.h"
#include"Ray.h"
class Camera
{
private:
	Vector3 center;//照相机光圈中心
	Vector3 image_plane_corner;//成像矩形平面的左下角
	Vector3 image_plane_uVector;//成像矩形平面的u向量
	Vector3 image_plane_vVector;//成像矩形平面的v向量
	ONB uvw;//照相机坐标系
	float lens_radius;//照相机光圈半径
	float u0,v0,u1,v1;//成像矩形平面的左下角坐标(u0,v0)和右上角坐标(u1,v1),
	float distance;//照相机光圈中心与成像平面的距离
public:
	Camera(Vector3 c,Vector3 gaze,Vector3 vup,float apertureDiameter,
	float left,float right,float top,float bottom,float distance);
	Camera(const Camera& cam);

	Ray getRay(float pixel_position_x, float pixel_position_y, float rannum_rayOriginXcoord_onAperture,
		float rannum_rayOriginYcoord_onAperture);
	//第一个getRay()函数,光线的起始点是随机分布在圆盘的,所以可以进行采样算法,但是在纹理贴图(与Texture相关)时
	//采用这种getRay方法会让图像模糊.所以有第二种getRay()

	Ray getRay(float pixel_position_x, float pixel_position_y);
	//第二种getRay()方法固定光线起始点为照相机中心点.无需采样.
};
#endif // !CAMERA_H

