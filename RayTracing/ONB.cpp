#include<iostream>
#include"ONB.h"
#include"Vector3.h"
using namespace  std;
#define ONB_EPSILON 0.01f//����onb����ϵ�Ĳ�����
/*
ǰ�����:
1,ONB����ϵ����U,V,W֮��Ĺ�ϵ,Ĭ��W=UxV.W��UxVָ��,���밴�����˳��.
2,ONB����ϵ��������������������Ҫ�ǵ�λ����,����Ҫ���������Ҳ���Ϊ0����(��������̫С)
*/
/*
��������(initFromU,initFromV,initFromW)��Ա������������֪��һ���ض��������������������ϵ.
*/
void ONB::initFromU(const Vector3& u)
//�������ض���U����(��Ҫ���ض�����������ʱ,���������)��������ϵ,������������������(ֻҪ�ܹ�������ϵ����),
//�����������ʹ��ONB_EPSILONϵ����������ϵ.
{
	Vector3 n(1.0f, 0.0f, 0.0f);
	Vector3 m(0.0f, 1.0f, 0.0f);
	U = unitVector(u);//���ض���U������ɵ�λ����
	V = cross(U, n);
	//���Ѿ��淶��U������n�������в�˻�ȡV����,�����ⲻһ�������յ�V����,��Ϊ��˲�������������̫С(��ԭ��
	//̫�ӽ�,�������Ժ���),���ʱ��ͱ����������,�ĳ�ʹ�ù淶��U������m�������в��(���U��n������˵Ľ��
	//�ǳ�С,��ô��m������˵Ľ��һ�������෴,�Ϳ�������Ҫ��.)
	//PS:Uxn=(0,Zu,-Yu),Uxm=(-Zu,0,Xu),����Xu^2+Yu^2+Zu^2=1,���length(Uxn)=sqrt(0+Zu^2+(-Yu)^2)̫С,
	//(������Ҫ�趨һ����ֵ(ONB_EPSILON)Ϊ0.01),��length(Uxn)<ONB_EPSILON(0.01)ʱ����ΪUxn̫С,̫�ӽ�ԭ��,�ͻ���
	//��Uxm��ΪV����,���ʱ��length(Uxm)=sqrt(Zu^2+Xu^2)�����ӽ�1,������������ϵ�������Ҫ��.
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
	V = cross(W,U);//��ΪĬ��W=UxV,���Թ���V������WxU��������UxW.
}
/*
����������Ա����������һ����δ��׼����������������Ϊ��һ������,�Լ�һ���ض�����(��������)�ķ�������
��Ϊ�ڶ�������(ע��ڶ�����������������������,��Ϊ���ķ�������,����һ�����һ����������).
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
}//ע������ONB����ϵʱ,ֻ��ǰ���������������������,������������Ч,ONB��UV(��һ����ڶ������������)��������ϵ
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
