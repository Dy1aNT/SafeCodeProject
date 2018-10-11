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
/* 功能：判断 name 字符串是否符合要求：name 只允许数字或字母，不小于 8 个字符，
不超过 16 个字符，且要求以字母开头。
参数 name：C 字符串。
返回值：符合要求返回 0，否则返回-1.
提示：可使用 isalnum，isalpha 等判断。 */
{
	if (name == NULL) return -1;
	int length;
	length = strlen(name);
	if (length < 8 || length > 16) { //不小于 8 个字符，不超过 16 个字符
		return -1;
	}
	if (!isalpha(name[0])) { //以字母开头
		return -1;
	}
	for (int i = 0; i < length; ++i) {
		if (!isalnum(name[i])) { //只允许数字或字母
			return -1;
		}
	}
	return 0;
}

int isPasswordOK(char* pwd)
/*功能：判断 pwd 字符串是否符合要求：允许数字或字母，不小于 8 个字符，不超过 16
个字符，至少包含一个数字和一个字母，且至少一个大写字母。
参数 pwd：C 字符串。
返回值：符合要求返回 0，否则返回-1.
提示：使用 isdigit，isupper，isalpha 等判断。*/
{
	if (pwd == NULL) return -1;
	int length;
	int upper_num = 0; 
	int digit_num = 0;
	int alpha_num = 0;
	length = strlen(pwd);
	if (length < 8 || length > 16) { //不小于 8 个字符，不超过 16个字符
		return -1;
	}
	for (int i = 0; i < length; ++i) {
		if (isalnum(pwd[i])) { // 允许数字或字母
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
	if (upper_num && digit_num && alpha_num) { //至少包含一个数字和一个字母，且至少一个大写字母
		return 0;
	} else {
		return -1;
	}
}

int gets_safe(char* str, rsize_t n)
/*功能：从 stdin 读入用户输入，直到用户敲入 Enter 终止。
（1）	如果用户输入的字符个数大于等于 n，则对输入字符串进行截断后保存前(n-1)个字符，最后一个位置置为空字符，以保证 str 指向的字符串符合 C 语言定义。同时，要求对 stdin 中缓冲的多余字符进行清空。
（2）	如果输入的字符个数小于 n，则保存 n 个字符，最后附加空字符，以保证 str 指向的字符串符合 C 语言定义。
（3）	本函数不保存回车换行符。
（4）	如果读取中出现错误，则 str[0] 置零，返回-1。
（5）	如果参数错误，则 str[0] 置零（如果确定 str 非空），返回-1.
参数 str：指向本地缓冲区的指针，用户输入的数据将被保存在该缓存区内。
参数 n：本地缓冲区的大小。
返回值：读入的字符个数，不包括空字符。出现读取错误，返回-2，参数错误返回-1.
提示：使用 getchar()获取用户输入的单个字符，ferror 函数测试读取错误。
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
			
			if (ferror(stdin)){	//如果读取中出现错误，则 str[0] 置零，返回-1。
				str[0] = NULL;
				return -1;
			}
			if (tmp == '\n') { //本函数不保存回车换行符
				for (rsize_t j = 0; j < n - i; ++j) {
					str[i + j] = '\0';
				}
				break;
			}
			if (tmp != ' ') ++count;
			str[i] = tmp;
		} else { //如果用户输入的字符个数大于等于 n，则对输入字符串进行截断后保存前(n - 1)个字符，最后一个位置置为空字符
			str[i] = '\0';
		}
	}
	return count;
}

int strcpy_safe(char*dest, rsize_t destsz, const char *src)
/*功能：复制源字符串 src 到目的缓冲区 dest。
（1）如果 src 字符串长度大于等于 destsz，则只复制前 (destsz-1) 个字符，目的缓冲区最后一个字符置零，保证 dest 字符串符合 C 语言对字符串的要求。
（2）如果 src 字符串长度小于 destsz，则复制整个源字符串，最后附加空字符，以保证dest 字符串符合 C 语言对字符串的要求。
（3）如果参数错误，则 dest[0] 置零（如果确定 dest 非空），返回-1.
参数 dest：指向目的缓冲区的指针。
参数 destsz：目的缓冲区的大小。
参数 src：指向源字符串的指针。
返回值：实际复制的字符个数，不包括空字符。出现错误返回-1.
提示：使用指针实现单个字符逐一复制。*/
{
	if (!dest) {
		return -1;
	}
	if (destsz <= 0 || !src) {
		dest[0] = NULL;
		return -1;
	}
	rsize_t srcsz = strlen(src);
	if (srcsz >= destsz) { //如果 src 字符串长度大于等于 destsz，则只复制前 (destsz-1) 个字符，目的缓冲区最后一个字符置零
		for (rsize_t i = 0; i < destsz - 1; ++i) {
			if (src[i] == '\0') {
				return -1;
			}
			dest[i] = src[i];
		}
		dest[destsz - 1] = '\0';
		return destsz - 1;
	} else if (srcsz < destsz) { //如果 src 字符串长度小于 destsz，则复制整个源字符串，最后附加空字符
		for (rsize_t i = 0; i < srcsz; ++i) {
			if (src[i] == '\0') {
				return -1;
			}
			dest[i] = src[i];
		}
		for (rsize_t i = srcsz; i < destsz; ++i) { //最后附加空字符
			dest[i] = '\0';
		}
		return srcsz;
	} else {
		return -1;
	}
}