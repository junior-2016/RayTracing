#include"Triangle.h"
#include"Vector3.h"
Triangle::Triangle(const Vector3& v1, const Vector3& v2, const Vector3& v3, const rgb& c)
	:a(v1),b(v2),c(v3),color(c){}

/*
Triangle plane and Ray intersection:
Triangle:S=a+beta*(b-a)+gamma*(c-a)
Ray:R=start_point+t*direction_vector
when Ray=Triangle is intersection,
Then: R=S,
Then: start_point + t * direction_vector = a + beta * (b-a) + gamma * (c-a)
assume o(ox,oy,oz)=strat_point ;
       d(dx,dy,dz)=direction_vector;
	   a(ax,ay,az)=a;
	   b(bx,by,bz)=b;
	   c(cx,cy,cz)=c;
Then: ox + t*dx = ax+ beta*(bx-ax) + gamma*(cx-ax)
      ...(like above)
	  ...(like above)
using matrix format display:
[ax-bx ax-cx dx] [beta ]  [ax-ox]
[ay-by ay-cy dy]*[gamma]= [ay-oy]
[az-bz az-cz dz] [  t  ]  [az-oz]
using Cramer's rule(克莱姆法则) to solve beta, gamma, t:

(PS:将行列式(Determinant)的行列互换，行列式的值不变，其中行列互换相当于转置.
即矩阵的行列式的值与这个矩阵的转置矩阵的行列式的值相等.
用符号表示:|A|=|A^T|,后面所有表达式的矩阵行列式都需要变形为对应的转置矩阵的行列式
)

     |ax-ox ax-cx dx|    |ax-ox ay-oy az-oz|
     |ay-oy ay-cy dy|    |ax-cx ay-cy az-cz|
	 |az-oz az-cz dz|    |dx    dy    dz   |         
beta=---------------- = -----------------------
         |A|                    |A|                   

		 |ax-bx ax-ox dx|         |ax-bx ay-by az-bz|
		 |ay-by ay-oy dy|         |ax-ox ay-oy az-oz|
		 |az-bz az-oz dz|         |dx    dy    dz   |
gammma=--------------------- = ------------------------
            |A|                       |A|

	|ax-bx ax-cx ax-ox|         |ax-bx ay-by az-bz|
	|ay-by ay-cy ay-oy|         |ax-cx ay-cy az-cz|
    |az-bz az-cz az-oz|         |ax-ox ay-oy az-oz|
t=------------------------ = -----------------------
            |A|                      |A|

  [ax-bx ax-cx dx]           |ax-bx ax-cx dx|   |ax-bx ay-by az-bz|
A=[ay-by ay-cy dy] , So |A|= |ay-by ay-cy dy| = |ax-cx ay-cy az-cz|
  [az-bz az-cz dz]           |az-bz az-cz dz|   |dx    dy    dz   |

Because: if three vector A=(a,b,c),B=(d,e,f),C=(g,h,i) then:
|a b c|
|d e f|=tripleProduct(B,C,A).
|g h i|
So:assume vector O = a-o
          vector B = a-b
		  vector C = a-c
		  vector D = d  
then:   if ((denom=tripleProduct(B,C,D))!=0) // denom can't be zero,if denom=0 shows that ray is parallel to plane.
        {
		     beta=tripleProduct(O,C,D) / denom;
			 if (beta <= 0.0f || beta >= 1.0f) return false;
			 gamma=tripleProduct(B,O,D) / denom; 
			 if (gamma <= 0.0f || beta+gamma >= 1.0f ) return false;
			 t=tripleProduct(B,C,O) / denom;
			 if (t<=tmax && t>=tmin) { record message;}
		}
		else return false;
normal vector:unitVector((b-a) x (c-a))

PS:
another solution for beta,gamma,t can see on PDF:Fast MinimumStorage RayTriangle Intersection
(just change the form of equation and use another way to change 3x3 matrix determinant.)

Tip:
Determinant's feature:(行列式性质)
1,|A|=|A^T|
2,exchange two arbitrary(任意的) rows(横行),determinant's sign symbol(正负符号) change.
Then |A,B,C|=-|B,A,C|=-(AxC)B (1)
     |A,B,C|=-|A,C,B|=-(CxB)A (2)
eg:
|-D,E1,E2|
=-(E2xE1)(-D)(using (2) formula)
=(E2xE1)D 
=|D,E2,E1|
=|E1,D,E2|(exchange rows twice, keep the same value)
=(DxE2)E1
*/
bool Triangle::hit(const Ray& ray, float tmin, float tmax, float time, HitRecord& record) const
{
	float t_result, beta, gamma, denom;
	Vector3 O = a - ray.startPoint();
	Vector3 B = a - b;
	Vector3 C = a - c;
	Vector3 D = ray.direction();
	denom = tripleProduct(B, C, D);
	if (denom != 0)
	{
		beta = tripleProduct(O, C, D) / denom;
		if (beta <= 0.0f || beta >= 1.0f) return false;
		gamma = tripleProduct(B, O, D) / denom;
		if (gamma <= 0.0f || beta + gamma >= 1.0f) return false;
		t_result = tripleProduct(B, C, O) / denom;
		if (t_result<tmin || t_result>tmax) return false;
		record.t = t_result;
		record.color = color;
		record.normal = unitVector(cross(b - a, c - a));
		return true;
	}
	else
		return false;
}
bool Triangle::shadowHit(const Ray& ray, float tmin, float tmax, float time)const
{
	float t_result, beta, gamma, denom;
	Vector3 O = a - ray.startPoint();
	Vector3 B = a - b;
	Vector3 C = a - c;
	Vector3 D = ray.direction();
	denom = tripleProduct(B, C, D);
	if (denom != 0)
	{
		beta = tripleProduct(O, C, D) / denom;
		if (beta <= 0.0f || beta >= 1.0f) return false;
		gamma = tripleProduct(B, O, D) / denom;
		if (gamma <= 0.0f || beta + gamma >= 1.0f) return false;
		t_result = tripleProduct(B, C, O) / denom;
		return (t_result >= tmin&&t_result <= tmax);
	}
	else
		return false;
}
