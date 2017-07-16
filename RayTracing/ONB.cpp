#include<iostream>
#include"ONB.h"
#include"Vector3.h"
using namespace  std;
#define ONB_EPSILON 0.01f//修正onb坐标系的参数ε
/*
前提规则:
1,ONB坐标系里面U,V,W之间的关系,默认W=UxV.W由UxV指定,必须按照这个顺序.
2,ONB坐标系的三个坐标轴向量不需要是单位向量,但是要求正交并且不能为0向量(分量不能太小)
*/
/*
后面三个(initFromU,initFromV,initFromW)成员函数是利用已知的一个特定方向的向量来构造坐标系.
*/
void ONB::initFromU(const Vector3& u)
//仅利用特定的U向量(在要求特定的向量方向时,比如照相机)构造坐标系,另外两个坐标轴任意(只要能构成正交系即可),
//但是这里必须使用ONB_EPSILON系数修正坐标系.
{
	Vector3 n(1.0f, 0.0f, 0.0f);
	Vector3 m(0.0f, 1.0f, 0.0f);
	U = unitVector(u);//将特定的U向量变成单位向量
	V = cross(U, n);
	//将已经规范的U向量与n向量进行叉乘获取V向量,但是这不一定是最终的V向量,因为叉乘产生的向量可能太小(与原点
	//太接近,几乎可以忽略),这个时候就必须进行修正,改成使用规范的U向量与m向量进行叉乘(如果U与n向量叉乘的结果
	//非常小,那么与m向量叉乘的结果一定与其相反,就可以满足要求.)
	//PS:Uxn=(0,Zu,-Yu),Uxm=(-Zu,0,Xu),并且Xu^2+Yu^2+Zu^2=1,如果length(Uxn)=sqrt(0+Zu^2+(-Yu)^2)太小,
	//(这里需要设定一个阈值(ONB_EPSILON)为0.01),当length(Uxn)<ONB_EPSILON(0.01)时就认为Uxn太小,太接近原点,就换成
	//以Uxm作为V向量,这个时候length(Uxm)=sqrt(Zu^2+Xu^2)基本接近1,可以满足正交系坐标轴的要求.
	if (V.length() < ONB_EPSILON )
		V = cross(U, m);
	W = cross(U, V);
}
void ONB::initFromV(const Vector3& v)
{
	Vector3 n(1.0f, 0.0f, 0.0f);
	Vector3 m(0.0f, 1.0f, 0.0f);
	V = unitVector(v);
	U = cross(V, n);
	if (U.length() < ONB_EPSILON)
		U = cross(V, m);
	W = cross(U, V);
}
void ONB::initFromW(const Vector3& w)
{
	Vector3 n(1.0f, 0.0f, 0.0f);
	Vector3 m(0.0f, 1.0f, 0.0f);
	W = unitVector(w);
	U = cross(W, n);
	if (U.length() < ONB_EPSILON)
		U = cross(W, m);
	V = cross(W,U);//因为默认W=UxV,所以构造V必须是WxU而不能是UxW.
}
/*
后面六个成员函数是利用一个尚未标准化的坐标轴向量作为第一个参数,以及一个特定方向(方向任意)的方向向量
作为第二个参数(注意第二个参数并不是坐标轴向量,因为它的方向任意,并不一定与第一个参数正交).
*/
void ONB::initFromUV(const Vector3& u, const Vector3& v)
{
	U = unitVector(u);
	W = unitVector(cross(u, v));
	V = cross(W, U);
}
void ONB::initFromVU(const Vector3& v, const Vector3& u)
{
	V = unitVector(v);
	W = unitVector(cross(u, v));
	U = cross(V, W);
}
void ONB::initFromUW(const Vector3& u, const Vector3& w)
{
	U = unitVector(u);
	V = unitVector(cross(w, u));
	W = cross(U, V);
}
void ONB::initFromWU(const Vector3& w, const Vector3& u)
{
	W = unitVector(w);
	V = unitVector(cross(w, u));
	U = cross(V, W);
}
void ONB::initFromVW(const Vector3& v, const Vector3& w)
{
	V = unitVector(v);
	U = unitVector(cross(v, w));
	W = cross(U, V);
}
void ONB::initFromWV(const Vector3& w, const Vector3& v)
{
	W = unitVector(w);
	U = unitVector(cross(v, w));
	V = cross(W, U);
}
istream& operator >> (istream& in, ONB&onb)
{
	Vector3 u, v, w;
	in >> u >> v >> w;
	onb.initFromUV(u, v);
	return in;
}//注意输入ONB坐标系时,只有前面输入的两个向量起到作用,第三个向量无效,ONB以UV(第一个与第二个输入的向量)建立正交系
ostream& operator<< (ostream& out, ONB&onb)
{
	out << onb.u() << endl;
	out << onb.v() << endl;
	out << onb.w()<< endl;
	return out;
}
bool operator==(const ONB& o1, const ONB& o2)
{
	return (o1.u() == o2.u() && o1.v() == o2.v() && o1.w() == o2.w());
}
