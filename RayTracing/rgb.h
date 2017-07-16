#ifndef RGB_H
#define RGB_H
#include<iostream>
using namespace std;
class rgb
{
private:
	float r;
	float g;
	float b;
public:
	rgb() :r(0), g(0), b(0) {}
	rgb(float red, float green, float blue);
	rgb(const rgb&original) { *this = original; }
	void setRed(float red) { this->r = red; }
	void setGreen(float green) { this->g = green; }
	void setBlue(float blue) { this->b = blue; }
	//单目运算符重载(成员函数实现)
	//设a=rgb(r,g,b),b=rgb(r,g,b),k为常数
	rgb& operator=(const rgb& right_rgb); //a=b;
	rgb& operator+=(const rgb& right_rgb); //a+=b;
	rgb& operator*=(const rgb& right_rgb); //a*=b;
	rgb& operator/=(const rgb& right_rgb); //a/=b;
	rgb& operator*=(float right_op);       //a*=k;
	rgb& operator/=(float right_op);       //a/=k;

	rgb operator+() const { return *this; }//返回+a;
	rgb operator-() const { return rgb(-r, -g, -b); }//返回-a;

	float red() const { return r; }
	float green() const { return g; }
	float blue() const { return b; }

	void clamp();//规范r,g,b的值在[0,1)

	friend ostream& operator<< (ostream & out,const rgb &out_rgb);

	//双目运算符,使用友元函数
	friend rgb operator* (const rgb& c, float f);//a=c*f;
	friend rgb operator* (float f, const rgb& c);//a=f*c;
	friend rgb operator/ (const rgb& c, float f);//a=c/f;
	friend rgb operator* (const rgb& c1, const rgb& c2);//a=c1*c2;
	friend rgb operator/ (const rgb& c1, const rgb& c2);//a=c1/c2;
	friend rgb operator+ (const rgb& c1, const rgb& c2);//a=c1+c2;
};
inline rgb::rgb(float red, float green, float blue)
	:r(red),g(green),b(blue){}
inline rgb& rgb::operator=(const rgb& right_rgb)
{
	r = right_rgb.r;
	g = right_rgb.g;
	b = right_rgb.b;
	return *this;
}
inline rgb&  rgb::operator+=(const rgb& right_rgb)
{
	*this = *this + right_rgb;
	return *this;
}
inline rgb& rgb:: operator*=(const rgb& right_rgb)
{
	*this = *this*right_rgb;
	return *this;
}
inline rgb& rgb::operator/=(const rgb& right_rgb)
{
	*this = *this / right_rgb;
	return *this;
}
inline rgb& rgb::operator*=(float right_op)
{
	*this = *this*right_op;
	return *this;
}
inline rgb& rgb::operator/=(float right_op)
{
	*this = *this / right_op;
	return *this;
}
inline void rgb::clamp()
{
	if (r > 1.0f) r = 1.0f;
	if (r < 0.0f) r = 0.0f;

	if (g > 1.0f) g = 1.0f;
	if (g < 0.0f) g = 0.0f;

	if (b > 1.0f) b = 1.0f;
	if (b < 0.0f) b = 0.0f;
}
inline ostream& operator<< (ostream & out, const rgb &out_rgb)
{
	out << out_rgb.r << " " << out_rgb.g << " " << out_rgb.b << endl;
	return out;
}
inline rgb operator* (const rgb& c, float f)
{
	return rgb(c.r*f, c.g*f, c.b*f);
}
inline rgb operator* (float f, const rgb& c)
{
	return rgb(c.r*f, c.g*f, c.b*f);
}
inline rgb operator/ (const rgb& c, float f)
{
	return rgb(c.r / f, c.g / f, c.b / f);
}
inline rgb operator* (const rgb& c1, const rgb& c2)
{
	return rgb(c1.r*c2.r, c1.g*c2.g, c1.b*c2.b);
}
inline rgb operator/ (const rgb& c1, const rgb& c2)
{
	return rgb(c1.r / c2.r, c1.g / c2.g, c1.b / c2.b);
}
inline rgb operator+ (const rgb& c1, const rgb& c2)
{
	return rgb(c1.r + c2.r, c2.g + c2.g, c1.b + c2.b);
}
#endif // RGB_H
