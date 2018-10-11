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
/*���ܣ��� str ָ��������ַ���ת��Ϊһ���������͡�������ֻ���[-128,127]��Χ�ڵ�����ִ��ת����
���� str��C �ַ�����
���� of������ָ�룬����ת���еĴ��������Str �Ϲ���ת���ɹ���(*of) = 0��str ��ָ�����ֻ���Ϊ�գ�(*of) = -1��str ָ������ֲ��Ϸ���(*of) = -2.
����ֵ������ת������������������ str ����ȷ����ָ�������Խ�磬�򷵻� 0.
��ʾ��p164 ���̸���*/
{
	long long result = 0; //8���ֽڳ���  
	int flag = 1;
	if (str == NULL || strlen(str) == 0) {
		(*of) = -1;
		return 0;
	}
	while (isspace(*str)) {	//����ǰ��Ŀհ��ַ�  
		++str;
	}
	if (*str == '-') {
		flag = -1;
		++str;
	} else if (*str == '+') {
		++str;
	}
	//�������ַ����ת������������У�����,�������0  
	while (*str != '\0') {
		if (*str <= '9' && *str >= '0') {
			result = result * 10 + *str - '0';
			if (flag == 1) { //У���Ƿ������  
				if (result > myINT8_MAX) {
					(*of) = -2;
					return 0;
				}
			} else if (flag == -1) { //У�鸺���  
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

/*���� of������ָ�룬���ؼ����еĴ��������(*of) = 0 ����ɹ���(*of) = -1 ��ʾ�����
(*of) = -2 ��ʾ�����
����ֵ������ɹ����ؼ����������򷵻� 0*/

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