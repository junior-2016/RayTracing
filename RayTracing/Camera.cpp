#include"Camera.h"
/*
Camera类有三个坐标体系:
Camera照相机相对于世界坐标系;
成像平面相对于Camera的uvw坐标系;
像素坐标相对于成像平面的二维坐标系
(成像平面的二维坐标系是利用image_plane_corner,image_plane_uVector,image_plane_vVector构造的)
但是实际上所有的坐标最终都是转化为世界坐标系的统一坐标.
*/

Camera::Camera(Vector3 c, Vector3 gaze, Vector3 vup, float apertureDiameter,
	float left, float right, float top, float bottom, float dis)
	:center(c),u0(left),v0(bottom),u1(right),v1(top),distance(dis)
{
	lens_radius = apertureDiameter / 2.0f;//apertureDiameter是照相机光圈的直径,除以2得到半径

	uvw.initFromWV(-gaze, vup);//构造照相机坐标系
	//gaze是光圈指向成像平面的向量,-gaze才是照相机坐标系的w分量;
	//vup是指定的一个方向向上的向量,一般取(0,1,0)，
    //可以通过改变vup来旋转相机从而旋转图像

	image_plane_corner = center + (u0*uvw.u() + v0*uvw.v() - distance*uvw.w());
	//成像平面左下角在世界坐标系的坐标 = 照相机中心坐标+(成像平面左下角在照相机坐标系的坐标)

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
像素位置(pixel_position_x,pixel_position_y)
映射方法:pixel_position_x=(x+0.5)/nx;
         pixel_position_y=(y+0.5)/ny;

rannum_rayOriginXcoord_onAperture和rannum_rayOriginYcoord_onAperture是(0,1)的随机数,
用来在照相机光圈(center为圆心,lens_radius为半径)上生成随机的光线起始点origin.

可以利用原来的正方形Sample算法产生rannum_rayOriginXcoord_onAperture和rannum_rayOriginYcoord_onAperture的数据.
但是有一点需要注意,因为照相机光圈是圆形区域,一般的实现中把单位正方形上均匀分布的采样点映射到单位圆上,
也可以把它映射到正多边形上，这样就可以简单模拟出漂亮的bokeh(弥散)效果
(一开始我就是采用正方形的MultiJitter采样得到了弥散效果).修改采样密度的分布也能获得不同的弥散圆形状.
*/
Ray Camera::getRay(float pixel_position_x, float pixel_position_y, float rannum_rayOriginXcoord_onAperture,
	float rannum_rayOriginYcoord_onAperture)
{
	Vector3 origin = center + 2.0f*(rannum_rayOriginXcoord_onAperture - 0.5f)*lens_radius*uvw.u()
		+ 2.0f*(rannum_rayOriginYcoord_onAperture - 0.5f)*lens_radius*uvw.v();
	Vector3 target = image_plane_corner + pixel_position_x*image_plane_uVector + pixel_position_y*image_plane_vVector;
	/*
	注意这里计算像素点的世界坐标时,是用:成像平面的左下角坐标(已经转化为世界坐标)+(像素相对于成像平面坐标系的坐标),
	并且注意到成像平面坐标系的坐标轴分量image_plane_uVector=(u1-u0)*uvw.u()和image_plane_vVector=(v1-v0)*uvw.v()
	其实已经转化为照相机的坐标轴分量了,而照相机的坐标是相对于世界坐标系的,所以这里的target(目标像素)的坐标
	其实也是在世界坐标系里的.
	*/
	return Ray(origin, unitVector(target - origin));
}
Ray Camera::getRay(float pixel_position_x, float pixel_position_y)
{
	Vector3 origin = center;
	Vector3 target = image_plane_corner + pixel_position_x*image_plane_uVector + pixel_position_y*image_plane_vVector;
	return Ray(origin, unitVector(target - origin));
}