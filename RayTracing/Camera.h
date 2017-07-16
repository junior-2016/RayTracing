#ifndef CAMERA_H
#define CAMERA_H
#include"ONB.h"
#include"Vector3.h"
#include"Ray.h"
class Camera
{
private:
	Vector3 center;//�������Ȧ����
	Vector3 image_plane_corner;//�������ƽ������½�
	Vector3 image_plane_uVector;//�������ƽ���u����
	Vector3 image_plane_vVector;//�������ƽ���v����
	ONB uvw;//���������ϵ
	float lens_radius;//�������Ȧ�뾶
	float u0,v0,u1,v1;//�������ƽ������½�����(u0,v0)�����Ͻ�����(u1,v1),
	float distance;//�������Ȧ���������ƽ��ľ���
public:
	Camera(Vector3 c,Vector3 gaze,Vector3 vup,float apertureDiameter,
	float left,float right,float top,float bottom,float distance);
	Camera(const Camera& cam);
	Ray getRay(float pixel_position_x, float pixel_position_y, float rannum_rayOriginXcoord_onAperture,
		float rannum_rayOriginYcoord_onAperture);
};
#endif // !CAMERA_H

