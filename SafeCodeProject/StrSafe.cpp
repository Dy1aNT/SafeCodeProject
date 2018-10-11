#include "stdafx.h"
#include "StrSafe.h"
#include "malloc.h"
#include <stdio.h>
#include <ctype.h>
#include <iostream>
#define NULL 0

using namespace std;

typedef rsize_t size_t;

int isUsernameOK(char* name)
/* ���ܣ��ж� name �ַ����Ƿ����Ҫ��name ֻ�������ֻ���ĸ����С�� 8 ���ַ���
������ 16 ���ַ�����Ҫ������ĸ��ͷ��
���� name��C �ַ�����
����ֵ������Ҫ�󷵻� 0�����򷵻�-1.
��ʾ����ʹ�� isalnum��isalpha ���жϡ� */
{
	if (name == NULL) return -1;
	int length;
	length = strlen(name);
	if (length < 8 || length > 16) { //��С�� 8 ���ַ��������� 16 ���ַ�
		return -1;
	}
	if (!isalpha(name[0])) { //����ĸ��ͷ
		return -1;
	}
	for (int i = 0; i < length; ++i) {
		if (!isalnum(name[i])) { //ֻ�������ֻ���ĸ
			return -1;
		}
	}
	return 0;
}

int isPasswordOK(char* pwd)
/*���ܣ��ж� pwd �ַ����Ƿ����Ҫ���������ֻ���ĸ����С�� 8 ���ַ��������� 16
���ַ������ٰ���һ�����ֺ�һ����ĸ��������һ����д��ĸ��
���� pwd��C �ַ�����
����ֵ������Ҫ�󷵻� 0�����򷵻�-1.
��ʾ��ʹ�� isdigit��isupper��isalpha ���жϡ�*/
{
	if (pwd == NULL) return -1;
	int length;
	int upper_num = 0; 
	int digit_num = 0;
	int alpha_num = 0;
	length = strlen(pwd);
	if (length < 8 || length > 16) { //��С�� 8 ���ַ��������� 16���ַ�
		return -1;
	}
	for (int i = 0; i < length; ++i) {
		if (isalnum(pwd[i])) { // �������ֻ���ĸ
			if (isdigit(pwd[i])) {
				digit_num++;
			} else if (isalnum(pwd[i])) {
				if (isupper(pwd[i])) {
					upper_num++;
				}
				alpha_num++;
			}
		} else {
			return -1;
		}
	}
	if (upper_num && digit_num && alpha_num) { //���ٰ���һ�����ֺ�һ����ĸ��������һ����д��ĸ
		return 0;
	} else {
		return -1;
	}
}

int gets_safe(char* str, rsize_t n)
/*���ܣ��� stdin �����û����룬ֱ���û����� Enter ��ֹ��
��1��	����û�������ַ��������ڵ��� n����������ַ������нضϺ󱣴�ǰ(n-1)���ַ������һ��λ����Ϊ���ַ����Ա�֤ str ָ����ַ������� C ���Զ��塣ͬʱ��Ҫ��� stdin �л���Ķ����ַ�������ա�
��2��	���������ַ�����С�� n���򱣴� n ���ַ�����󸽼ӿ��ַ����Ա�֤ str ָ����ַ������� C ���Զ��塣
��3��	������������س����з���
��4��	�����ȡ�г��ִ����� str[0] ���㣬����-1��
��5��	������������� str[0] ���㣨���ȷ�� str �ǿգ�������-1.
���� str��ָ�򱾵ػ�������ָ�룬�û���������ݽ��������ڸû������ڡ�
���� n�����ػ������Ĵ�С��
����ֵ��������ַ����������������ַ������ֶ�ȡ���󣬷���-2���������󷵻�-1.
��ʾ��ʹ�� getchar()��ȡ�û�����ĵ����ַ���ferror �������Զ�ȡ����
*/
{
	if (!str) {
		return -1;
	}
	if (n <= 0) {
		str[0] = NULL;
		return -1;
	}
	int count = 0;
	char tmp = NULL;
	for (rsize_t i = 0; i < n; ++i) {
		if (i != n - 1) {
			tmp = getchar();
			
			if (ferror(stdin)){	//�����ȡ�г��ִ����� str[0] ���㣬����-1��
				str[0] = NULL;
				return -1;
			}
			if (tmp == '\n') { //������������س����з�
				for (rsize_t j = 0; j < n - i; ++j) {
					str[i + j] = '\0';
				}
				break;
			}
			if (tmp != ' ') ++count;
			str[i] = tmp;
		} else { //����û�������ַ��������ڵ��� n����������ַ������нضϺ󱣴�ǰ(n - 1)���ַ������һ��λ����Ϊ���ַ�
			str[i] = '\0';
		}
	}
	return count;
}

int strcpy_safe(char*dest, rsize_t destsz, const char *src)
/*���ܣ�����Դ�ַ��� src ��Ŀ�Ļ����� dest��
��1����� src �ַ������ȴ��ڵ��� destsz����ֻ����ǰ (destsz-1) ���ַ���Ŀ�Ļ��������һ���ַ����㣬��֤ dest �ַ������� C ���Զ��ַ�����Ҫ��
��2����� src �ַ�������С�� destsz����������Դ�ַ�������󸽼ӿ��ַ����Ա�֤dest �ַ������� C ���Զ��ַ�����Ҫ��
��3��������������� dest[0] ���㣨���ȷ�� dest �ǿգ�������-1.
���� dest��ָ��Ŀ�Ļ�������ָ�롣
���� destsz��Ŀ�Ļ������Ĵ�С��
���� src��ָ��Դ�ַ�����ָ�롣
����ֵ��ʵ�ʸ��Ƶ��ַ����������������ַ������ִ��󷵻�-1.
��ʾ��ʹ��ָ��ʵ�ֵ����ַ���һ���ơ�*/
{
	if (!dest) {
		return -1;
	}
	if (destsz <= 0 || !src) {
		dest[0] = NULL;
		return -1;
	}
	rsize_t srcsz = strlen(src);
	if (srcsz >= destsz) { //��� src �ַ������ȴ��ڵ��� destsz����ֻ����ǰ (destsz-1) ���ַ���Ŀ�Ļ��������һ���ַ�����
		for (rsize_t i = 0; i < destsz - 1; ++i) {
			if (src[i] == '\0') {
				return -1;
			}
			dest[i] = src[i];
		}
		dest[destsz - 1] = '\0';
		return destsz - 1;
	} else if (srcsz < destsz) { //��� src �ַ�������С�� destsz����������Դ�ַ�������󸽼ӿ��ַ�
		for (rsize_t i = 0; i < srcsz; ++i) {
			if (src[i] == '\0') {
				return -1;
			}
			dest[i] = src[i];
		}
		for (rsize_t i = srcsz; i < destsz; ++i) { //��󸽼ӿ��ַ�
			dest[i] = '\0';
		}
		return srcsz;
	} else {
		return -1;
	}
}