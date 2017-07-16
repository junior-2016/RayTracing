#ifndef VECTOR3_H
#define VECTOR3_H
#include<iostream>
#include<cmath>
using namespace std;
class Vector3
{
private:
	float elem[3];
public:
	Vector3() {}
	Vector3(float e0, float e1, float e2);
	Vector3(const Vector3& v) { *this = v; }

	float x() const{ return elem[0]; }
	float y() const { return elem[1]; }
	float z() const { return elem[2]; }

	float length() const;
	float squaredLength() const;
	void makeUnitVector();
	void setX(float x) { elem[0] = x; }
	void setY(float y) { elem[1] = y; }
	void setZ(float z) { elem[2] = z; }
	float minComponent() const;
	float maxComponent() const;
	float minAbsComponent() const;
	float maxAbsComponent() const;
	int indexOfMaxComponent() const;
	int indexOfMinComponent() const;
	int indexOfAbsMaxComponent() const;
	int indexOfAbsMinComponent() const;

	const Vector3& operator+() const;
	Vector3 operator-() const;
	float operator[](int index) const { return elem[index]; }
	//vector[index]只能作为右值,不能做左值,比如cout<<v[1]<<endl;可以但是v[1]=1.1不可以.
	float& operator[] (int index) { return elem[index]; }
	//既可以作为右值也可以作为左值,比如vector[1]=1.1;
	friend bool operator==(const Vector3& v1, const Vector3& v2);
	friend bool operator!=(const Vector3& v1, const Vector3& v2);

	friend ostream& operator<<(ostream& out, const Vector3& v);
	friend istream& operator >> (istream& in, Vector3& v);

	friend Vector3 operator+(const Vector3& v1, const Vector3& v2);
	friend Vector3 operator- (const Vector3& v1, const Vector3& v2);
	friend Vector3 operator/(const Vector3& v, float scalar);
	friend Vector3 operator*(const Vector3& v, float scalar);
	friend Vector3 operator*(float scalar, const Vector3& v);

	Vector3& operator=(const Vector3& v);
	Vector3& operator+=(const Vector3& v);
	Vector3& operator-=(const Vector3& v);
	Vector3& operator*=(const float scalar);
	Vector3& operator/=(const float scalar);

	friend Vector3 unitVector(const Vector3& v);
	friend Vector3 minVec(const Vector3& v1, const Vector3& v2);
	friend Vector3 maxVec(const Vector3& v1, const Vector3& v2);
	friend Vector3 cross(const Vector3& v1, const Vector3& v2);//cross:叉乘
	friend float dot(const Vector3& v1, const Vector3& v2);//dot:点乘
	friend float tripleProduct(const Vector3& v1, const Vector3& v2, const Vector3& v3);//tripleProduct:混合积

};
inline Vector3::Vector3(float e0, float e1, float e2)
{
	elem[0] = e0;
	elem[1] = e1;
	elem[2] = e2;
}
inline float Vector3::length() const
{
	return sqrt(elem[0] * elem[0] + elem[1] * elem[1] + elem[2] * elem[2]);
}
inline float Vector3::squaredLength() const
{
	return elem[0] * elem[0] + elem[1] * elem[1] + elem[2] * elem[2];
}
inline void Vector3::makeUnitVector()
{
	*this = *this / (*this).length();
}
inline float Vector3::minComponent() const
{
	float temp = elem[0];
	if (temp > elem[1]) temp = elem[1];
	if (temp > elem[2])temp = elem[2];
	return temp;
}
inline float Vector3::maxComponent() const
{
	float temp = elem[0];
	if (temp < elem[1]) temp = elem[1];
	if (temp < elem[2]) temp = elem[2];
	return temp;
}
inline float Vector3::minAbsComponent() const
{
	float temp = fabs(elem[0]);
	if (temp > fabs(elem[1])) temp = elem[1];
	if (temp > fabs(elem[2])) temp = elem[2];
	return temp;
}
inline float Vector3::maxAbsComponent() const
{
	float temp = fabs(elem[0]);
	if (temp < fabs(elem[1])) temp = elem[1];
	if (temp < fabs(elem[2])) temp = elem[2];
	return temp;
}
inline int Vector3::indexOfMaxComponent() const
{
	float temp = elem[0];
	int index = 0;
	if (temp < elem[1]) { temp = elem[1]; index = 1; }
	if (temp < elem[2]) index = 2;
	return index;
}
inline int Vector3::indexOfMinComponent() const
{
	float temp = elem[0];
	int index = 0;
	if (temp > elem[1]) { temp = elem[1]; index = 1; }
	if (temp > elem[2]) index = 2;
	return index;
}
inline int Vector3::indexOfAbsMaxComponent() const
{
	float temp = fabs(elem[0]);
	int index = 0;
	if (temp < fabs(elem[1])) { temp = elem[1];index = 1; }
	if (temp < fabs(elem[2])) index = 2;
	return index;
}
inline int Vector3::indexOfAbsMinComponent() const
{
	float temp = fabs(elem[0]);
	int index = 0;
	if (temp > fabs(elem[1])) {temp = elem[1];index = 1;}
	if (temp > fabs(elem[2])) index = 2;
	return index;
}
inline const Vector3& Vector3::operator+() const
{
	return *this;
}
inline Vector3 Vector3::operator-() const
{
	return Vector3(-elem[0], -elem[1], -elem[2]);
}
inline bool operator==(const Vector3& v1, const Vector3& v2)
{
	if (v1.elem[0]!=v2.elem[0]) return false;
	if (v1.elem[1]!=v2.elem[1])  return false;
	if (v1.elem[2]!=v2.elem[2]) return false;
	return true;
}
inline bool operator!=(const Vector3& v1, const Vector3& v2)
{
	return !(v1 == v2);
}

inline Vector3 operator+(const Vector3& v1, const Vector3& v2) 
{
	return Vector3(v1.elem[0] + v2.elem[0], v1.elem[1] + v2.elem[1], v1.elem[2] + v2.elem[2]);
}
inline Vector3 operator- (const Vector3& v1, const Vector3& v2)
{
	return Vector3(v1.elem[0] - v2.elem[0], v1.elem[1] - v2.elem[1], v1.elem[2] - v2.elem[2]);
}
inline Vector3 operator/(const Vector3& v, float scalar)
{
	return Vector3(v.elem[0] / scalar, v.elem[1] / scalar, v.elem[2] / scalar);
}
inline Vector3 operator*(const Vector3& v, float scalar)
{
	return Vector3(v.elem[0] * scalar, v.elem[1] * scalar, v.elem[2] * scalar);
}
inline Vector3 operator*(float scalar, const Vector3& v)
{
	return Vector3(v.elem[0] * scalar, v.elem[1] * scalar, v.elem[2] * scalar);
}

inline Vector3& Vector3::operator=(const Vector3& v)
{
	elem[0] = v.elem[0];
	elem[1] = v.elem[1];
	elem[2] = v.elem[2];
	return *this;
}
inline Vector3& Vector3::operator+=(const Vector3& v)
{
	*this = *this + v;
	return *this;
}
inline Vector3& Vector3::operator-=(const Vector3& v)
{
	*this = *this - v;
	return *this;
}
inline Vector3& Vector3::operator*=(const float scalar)
{
	*this = *this*scalar;
	return *this;
}
inline Vector3& Vector3::operator/=(const float scalar)
{
	*this = *this/scalar;
	return *this;
}

inline Vector3 unitVector(const Vector3& v)
{
	return v / (v.length());
}
inline Vector3 minVec(const Vector3& v1, const Vector3& v2)
{
	Vector3 temp(v1);
	if (v1.elem[0] > v2.elem[0]) temp.setX(v2.elem[0]);
	if (v1.elem[1] > v2.elem[1]) temp.setY(v2.elem[1]);
	if (v1.elem[2] > v2.elem[2]) temp.setZ(v2.elem[2]);
	return temp;
}
inline Vector3 maxVec(const Vector3& v1, const Vector3& v2)
{
	Vector3 temp(v1);
	if (v1.elem[0] < v2.elem[0]) temp.setX(v2.elem[0]);
	if (v1.elem[1] < v2.elem[1]) temp.setY(v2.elem[1]);
	if (v1.elem[2] < v2.elem[2]) temp.setZ(v2.elem[2]);
	return temp;
}
inline Vector3 cross(const Vector3& v1, const Vector3& v2)
{
	Vector3 temp;
	temp.setX(v1.y()*v2.z() - v1.z()*v2.y());
	temp.setY(v1.z()*v2.x() - v1.x()*v2.z());
	temp.setZ(v1.x()*v2.y() - v1.y()*v2.x());
	return temp;
}
inline float dot(const Vector3& v1, const Vector3& v2)
{
	return v1.x()*v2.x() + v1.y()*v2.y() + v1.z()*v2.z();
}
#endif // !VECTOR3_H

