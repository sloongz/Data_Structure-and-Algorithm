#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define Accuracy 0.000001

double msqrt(double num)
{
	double mid = 0;
	double start = 0.0;
	double end = num;

	while (1) {
		mid = (start + end)/2;

		if ((mid*mid - num) <= Accuracy && (mid*mid - num) >= -Accuracy) {
			return mid;
		}

		if ((mid*mid - num) > Accuracy) {
			end = mid;
		} else {
			start = mid;
		} 
	}

	return mid;
}


//https://zh.wikipedia.org/wiki/%E5%B9%B3%E6%96%B9%E6%A0%B9%E5%80%92%E6%95%B0%E9%80%9F%E7%AE%97%E6%B3%95
float Q_rsqrt( float number )
{
	long i;
	float x2, y;
	const float threehalfs = 1.5F;

	x2 = number * 0.5F;
	y  = number;
	i  = * ( long * ) &y;                       // evil floating point bit level hacking（对浮点数的邪恶位元hack）
	i  = 0x5f3759df - ( i >> 1 );               // what the fuck?（这他妈的是怎么回事？）
	y  = * ( float * ) &i;
	y  = y * ( threehalfs - ( x2 * y * y ) );   // 1st iteration （第一次迭代）
	//y  = y * ( threehalfs - ( x2 * y * y ) );   // 2nd iteration, this can be removed（第二次迭代，可以删除）

	return 1/y;
}

int main(int argc, char **argv)
{
	double result=0;
	double num = 0.0;

	printf("please input val:\n");
	scanf("%lf", &num);
	result = msqrt(num);
	printf("num:%f sqrt is %f\n", num, result);
	result = Q_rsqrt(num);
	printf("num:%f sqrt is %f\n", num, result);


	return 0;
}
