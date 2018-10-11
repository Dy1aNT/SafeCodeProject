#include "stdafx.h"
#include "MathSafe.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define uint uint8_t
#define myINT_MAX 2147483648
#define myINT_MIN (-2147483647 - 1)
#define myINT8_MAX 127
#define myINT8_MIN -128
#define myUINT8_MAX 255


int8_t my_atoi8(char* str, int* of)
/*功能：将 str 指向的整数字符串转换为一个整数类型。本函数只针对[-128,127]范围内的整数执行转换。
参数 str：C 字符串。
参数 of：整数指针，返回转换中的错误情况。Str 合规且转换成功，(*of) = 0；str 不指向数字或者为空，(*of) = -1；str 指向的数字不合法，(*of) = -2.
返回值：返回转换后的整数，如果参数 str 不正确或者指向的数字越界，则返回 0.
提示：p164 例程改造*/
{
	long long result = 0; //8个字节长度  
	int flag = 1;
	if (str == NULL || strlen(str) == 0) {
		(*of) = -1;
		return 0;
	}
	while (isspace(*str)) {	//跳过前面的空白字符  
		++str;
	}
	if (*str == '-') {
		flag = -1;
		++str;
	} else if (*str == '+') {
		++str;
	}
	//把数字字符逐个转换成整数，并校验溢出,溢出返回0  
	while (*str != '\0') {
		if (*str <= '9' && *str >= '0') {
			result = result * 10 + *str - '0';
			if (flag == 1) { //校验是否正溢出  
				if (result > myINT8_MAX) {
					(*of) = -2;
					return 0;
				}
			} else if (flag == -1) { //校验负溢出  
				if (-result < myINT8_MIN) {
					(*of) = -2;
					return 0;
				}
			}
			++str;
		} else if(isspace(*str)) {
			++str;
		} else {
			(*of) = -1;
			return 0;
		}
	}
	(*of) = 0;
	return (int8_t)flag * result;
}

/*参数 of：整数指针，返回计算中的错误情况。(*of) = 0 计算成功；(*of) = -1 表示除零错；
(*of) = -2 表示溢出错。
返回值：计算成功返回计算结果，否则返回 0*/

int iAdd_Safe(int8_t a, int8_t b, int* of)
{
	long long result = a + b;
	if (result > myINT8_MAX || result < myINT8_MIN) {
		(*of) = -2;
		return 0;
	} else {
		(*of) = 0;
		return (int)result;
	}
}
int iSubtract_Safe(int8_t a, int8_t b, int* of)
{
	long long result = a - b;
	if (result > myINT8_MAX || result < myINT8_MIN) {
		(*of) = -2;
		return 0;
	} else {
		(*of) = 0;
		return (int)result;
	}
}

int iMultiply_Safe(int8_t a, int8_t b, int* of)
{
	long long result = a * b;
	if (result > myINT8_MAX || result < myINT8_MIN) {
		(*of) = -2;
		return 0;
	} else {
		(*of) = 0;
		return (int)result;
	}
}

int iDivide_Safe(int8_t a, int8_t b, int* of)
{
	if (b == 0) {
		(*of) = -1;
		return 0;
	}
	long long result = a / b;
	if (result > myINT8_MAX || result < myINT8_MIN) {
		(*of) = -2;
		return 0;
	} else {
		(*of) = 0;
		return (int)result;
	}
}

uint Add_Safe(uint8_t a, uint8_t b, int* of)
{
	long long result = a + b;
	if (result > myUINT8_MAX || result < 0) {
		(*of) = -2;
		return 0;
	} else {
		(*of) = 0;
		return (uint8_t)result;
	}
}

uint Subtract_Safe(uint8_t a, uint8_t b, int* of)
{
	long long result = a - b;
	if (result > myUINT8_MAX || result < 0) {
		(*of) = -2;
		return 0;
	} else {
		(*of) = 0;
		return (uint8_t)result;
	}
}

uint Multiply_Safe(uint8_t a, uint8_t b, int* of)
{
	long long result = a * b;
	if (result > myUINT8_MAX || result < 0) {
		(*of) = -2;
		return 0;
	} else {
		(*of) = 0;
		return (uint8_t)result;
	}
}

uint Divide_Safe(uint8_t a, uint8_t b, int* of)
{
	if (b == 0) {
		(*of) = -1;
		return 0;
	}
	long long result = a / b;
	if (result > myUINT8_MAX || result < 0) {
		(*of) = -2;
		return 0;
	} else {
		(*of) = 0;
		return (uint8_t)result;
	}
}