#include"Camera.h"
/*
Camera��������������ϵ:
Camera������������������ϵ;
����ƽ�������Camera��uvw����ϵ;
������������ڳ���ƽ��Ķ�ά����ϵ
(����ƽ��Ķ�ά����ϵ������image_plane_corner,image_plane_uVector,image_plane_vVector�����)
����ʵ�������е��������ն���ת��Ϊ��������ϵ��ͳһ����.
*/

Camera::Camera(Vector3 c, Vector3 gaze, Vector3 vup, float apertureDiameter,
	float left, float right, float top, float bottom, float dis)
	:center(c),u0(left),v0(bottom),u1(right),v1(top),distance(dis)
{
	lens_radius = apertureDiameter / 2.0f;//apertureDiameter���������Ȧ��ֱ��,����2�õ��뾶

	uvw.initFromWV(-gaze, vup);//�������������ϵ
	//gaze�ǹ�Ȧָ�����ƽ�������,-gaze�������������ϵ��w����;
	//vup��ָ����һ���������ϵ�����,һ��ȡ(0,1,0)��
    //����ͨ���ı�vup����ת����Ӷ���תͼ��

	image_plane_corner = center + (u0*uvw.u() + v0*uvw.v() - distance*uvw.w());
	//����ƽ�����½�����������ϵ������ = �������������+(����ƽ�����½������������ϵ������)

	image_plane_uVector = (u1 - u0)*uvw.u();
	image_plane_vVector = (v1 - v0)*uvw.v();
}
Camera::Camera(const Camera& cam)
{
	center = cam.center;
	image_plane_corner = cam.image_plane_corner;
	image_plane_uVector = cam.image_plane_uVector;
	image_plane_vVector = cam.image_plane_vVector;
	u0 = cam.u0;
	u1 = cam.u1;
	v0 = cam.v0;
	v1 = cam.v1;
	distance = cam.distance;
	lens_radius = cam.lens_radius;
	uvw = cam.uvw;
}

/*
����λ��(pixel_position_x,pixel_position_y)
ӳ�䷽��:pixel_position_x=(x+0.5)/nx;
         pixel_position_y=(y+0.5)/ny;

rannum_rayOriginXcoord_onAperture��rannum_rayOriginYcoord_onAperture��(0,1)�������,
�������������Ȧ(centerΪԲ��,lens_radiusΪ�뾶)����������Ĺ�����ʼ��origin.

��������ԭ����������Sample�㷨����rannum_rayOriginXcoord_onAperture��rannum_rayOriginYcoord_onAperture������.
������һ����Ҫע��,��Ϊ�������Ȧ��Բ������,һ���ʵ���аѵ�λ�������Ͼ��ȷֲ��Ĳ�����ӳ�䵽��λԲ��,
Ҳ���԰���ӳ�䵽��������ϣ������Ϳ��Լ�ģ���Ư����bokeh(��ɢ)Ч��
(һ��ʼ�Ҿ��ǲ��������ε�MultiJitter�����õ�����ɢЧ��).�޸Ĳ����ܶȵķֲ�Ҳ�ܻ�ò�ͬ����ɢԲ��״.
*/
Ray Camera::getRay(float pixel_position_x, float pixel_position_y, float rannum_rayOriginXcoord_onAperture,
	float rannum_rayOriginYcoord_onAperture)
{
	Vector3 origin = center + 2.0f*(rannum_rayOriginXcoord_onAperture - 0.5f)*lens_radius*uvw.u()
		+ 2.0f*(rannum_rayOriginYcoord_onAperture - 0.5f)*lens_radius*uvw.v();
	Vector3 target = image_plane_corner + pixel_position_x*image_plane_uVector + pixel_position_y*image_plane_vVector;
	/*
	ע������������ص����������ʱ,����:����ƽ������½�����(�Ѿ�ת��Ϊ��������)+(��������ڳ���ƽ������ϵ������),
	����ע�⵽����ƽ������ϵ�����������image_plane_uVector=(u1-u0)*uvw.u()��image_plane_vVector=(v1-v0)*uvw.v()
	��ʵ�Ѿ�ת��Ϊ������������������,����������������������������ϵ��,���������target(Ŀ������)������
	��ʵҲ������������ϵ���.
	*/
	return Ray(origin, unitVector(target - origin));
}
Ray Camera::getRay(float pixel_position_x, float pixel_position_y)
{
	Vector3 origin = center;
	Vector3 target = image_plane_corner + pixel_position_x*image_plane_uVector + pixel_position_y*image_plane_vVector;
	return Ray(origin, unitVector(target - origin));
}