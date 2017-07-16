#ifndef VECTOR2_H
#define VECTOR2_H
#include<iostream>
using namespace  std;
class Vector2 //Vector2主要用在储存采样点
{
private:
	float elem[2];
public:
	Vector2() {}
	Vector2(float e0, float e1);
	Vector2(const Vector2& v) { *this = v; }

	float x() const { return elem[0]; }
	float y() const { return elem[1]; }

	float length() const;
	float squaredLength() const;
	void makeUnitVector();
	void setX(float x) { elem[0] = x; }
	void setY(float y) { elem[1] = y; }
	
	const Vector2& operator+() const;
	Vector2 operator-() const;
	float operator[](int index) const { return elem[index]; }
	
	float& operator[] (int index) { return elem[index]; }

	friend bool operator==(const Vector2& v1, const Vector2& v2);
	friend bool operator!=(const Vector2& v1, const Vector2& v2);

	friend ostream& operator<<(ostream& out, const Vector2& v);
	friend istream& operator >> (istream& in, Vector2& v);

	friend Vector2 operator+(const Vector2& v1, const Vector2& v2);
	friend Vector2 operator- (const Vector2& v1, const Vector2& v2);
	friend Vector2 operator/(const Vector2& v, float scalar);
	friend Vector2 operator*(const Vector2& v, float scalar);
	friend Vector2 operator*(float scalar, const Vector2& v);

	Vector2& operator=(const Vector2& v);
	Vector2& operator+=(const Vector2& v);
	Vector2& operator-=(const Vector2& v);
	Vector2& operator*=(const float scalar);
	Vector2& operator/=(const float scalar);

	friend Vector2 unitVector(const Vector2& v);
};
inline Vector2::Vector2(float e0, float e1)
{
	elem[0] = e0;
	elem[1] = e1;
}
inline float Vector2::length() const
{
	return sqrt(elem[0] * elem[0] + elem[1] * elem[1]);
}
inline float Vector2::squaredLength() const
{
	return elem[0] * elem[0] + elem[1] * elem[1];
}
inline void Vector2::makeUnitVector()
{
	*this = *this / (*this).length();
}

inline const Vector2& Vector2::operator+() const
{
	return *this;
}
inline Vector2 Vector2::operator-() const
{
	return Vector2(-elem[0], -elem[1]);
}
inline bool operator==(const Vector2& v1, const Vector2& v2)
{
	if (v1.elem[0] != v2.elem[0]) return false;
	if (v1.elem[1] != v2.elem[1])  return false;
	return true;
}
inline bool operator!=(const Vector2& v1, const Vector2& v2)
{
	return !(v1 == v2);
}

inline Vector2 operator+(const Vector2& v1, const Vector2& v2)
{
	return Vector2(v1.elem[0] + v2.elem[0], v1.elem[1] + v2.elem[1]);
}
inline Vector2 operator- (const Vector2& v1, const Vector2& v2)
{
	return Vector2(v1.elem[0] - v2.elem[0], v1.elem[1] - v2.elem[1]);
}
inline Vector2 operator/(const Vector2& v, float scalar)
{
	return Vector2(v.elem[0] / scalar, v.elem[1] / scalar);
}
inline Vector2 operator*(const Vector2& v, float scalar)
{
	return Vector2(v.elem[0] * scalar, v.elem[1] * scalar);
}
inline Vector2 operator*(float scalar, const Vector2& v)
{
	return Vector2(v.elem[0] * scalar, v.elem[1] * scalar);
}

inline Vector2& Vector2::operator=(const Vector2& v)
{
	elem[0] = v.elem[0];
	elem[1] = v.elem[1];
	return *this;
}
inline Vector2& Vector2::operator+=(const Vector2& v)
{
	*this = *this + v;
	return *this;
}
inline Vector2& Vector2::operator-=(const Vector2& v)
{
	*this = *this - v;
	return *this;
}
inline Vector2& Vector2::operator*=(const float scalar)
{
	*this = *this*scalar;
	return *this;
}
inline Vector2& Vector2::operator/=(const float scalar)
{
	*this = *this / scalar;
	return *this;
}

inline Vector2 unitVector(const Vector2& v)
{
	return v / (v.length());
}
#endif // !VECTOR2_H

