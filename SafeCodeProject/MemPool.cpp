#include "stdafx.h"
#include "MemPool.h"
#include <stdio.h>
#include <stdlib.h>
#define NULL 0
using namespace std;

struct block{
	int flag = 0;
	char buf[256];
	block* next = NULL;
};

block* start = new block;

int initPool(size_t size)
/*���ܣ������ʼ�ڴ�أ��ڴ�س�ʼ��СĬ��Ϊ 1000 ���飬�� 256 x 1000 �ֽڡ�
���� size���ڴ�س�ʼ��ʱ������ڴ�������Ĭ��Ϊ 1000 �顣
����ֵ���ɹ���� 1000 ���ڴ�������򷵻� 0�����򷵻�-1.
��ʾ����ʹ�� malloc��calloc �Ⱥ�������ڴ��ʼ����*/
{
	block* pool = start;
	for (size_t i = 0; i < size; ++i) {
		block* L = new block;
		if (!L) {
			return -1;
		}
		L->next = NULL;
		pool->next = L;
		pool = pool->next;
	}
	return 0;
}


char* allocBlock()
/*���ܣ����ڴ�����ҵ�һ������ڴ����з��䡣������ڴ汻��ʼ��Ϊ 0������ڴ���ڴ��ѷ����꣬��������ڴ�ؽ������䡣
����ֵ�����ط�����ڴ���׵�ַ��������ִ����򷵻ؿ�ָ�롣
��ʾ����ʹ�� malloc��calloc ������memset ������ע�����ʹ�� realloc �����ڴ棬ͨ�� allocBlock �Ѿ������ȥ���ڴ���ַ���ܻ���Ч��*/
{
	block* pool = start;
	while (pool->next) {
		pool = pool->next;
		if (pool->flag == 0) {
			pool->flag = 1;
			memset(pool->buf, NULL, 256 * sizeof(char));
			return (pool->buf);
		}
	}
	block* L = new block;
	if (!L) {
		return NULL; //������ִ����򷵻ؿ�ָ��
	}
	memset(L->buf, NULL, 256 * sizeof(char));
	L->flag = 1;
	L->next = NULL;
	pool->next = L;
	return (L->buf);
}

int freeBlock(char* buf)
/*���ܣ��� buf ָ����ڴ���ͷţ����ڴ�鲢��ִ�ж��ڴ���ͷŲ�����ֻ�ǷŻ��ڴ�ع��´η���ʹ�á��ͷ�ʱ����� buf ָ����ڴ�����������������
���� buf��ָ��Ҫ�Ż��ڴ���е��ڴ�顣
����ֵ��ִ�гɹ����� 0��buf ָ��������Ϲ淵��-1��δ�ҵ���Ӧ�Ŀ鷵��-2.
��ʾ����ʹ�� memset ���������� Windows API SecureZeroMemory �������㡣*/
{
	if (!buf) {
		return -1;
	}
	block* pool = start;
	while (pool->next) {
		pool = pool->next;
		if (pool->buf == buf) {
			pool->flag = 0;
			memset(pool->buf, NULL, 256 * sizeof(char));
			return 0;
		}
	}
	return -2;
}

int freePool()
/*���ܣ��������ڴ�ص��ڴ�ȫ���ͷţ������ж��Ƿ����δ���յ��ڴ�飬��������践��-1�����û������ڴ�������ڴ��������㣬Ȼ��ִ�� free ������.
����ֵ��ִ�гɹ����� 0���������δ���յ��ڴ�飬���践��-1.
��ʾ����ʹ�� free��memset ������*/
{
	block* pool = start;
	while (pool->next) {
		pool = pool->next;
		if (pool->flag == 1) {
			return -1;
		}
	}
	block* head = start;
	block* tmp = NULL;
	while (head->next) {
		tmp = head->next;
		head->next = tmp->next;
		memset(tmp, NULL, sizeof(block));
		free(tmp);
		tmp = NULL;
	}
	return 0;
}

int freePoolForce()
/*���ܣ������Ƿ����δ���յ��ڴ�飬���������ڴ�ص��ڴ��������㣬Ȼ��ִ��free ������.
����ֵ��ִ�гɹ����� 0�����ִ����򷵻�-1.
��ʾ����ʹ�� free��memset ������*/
{
	block* head = start;
	block* tmp = NULL;
	while (head->next) {
		tmp = head->next;
		head->next = tmp->next;
		memset(tmp, NULL, sizeof(block));
		free(tmp);
		tmp = NULL;
	}
	return 0;
}

int getBlockCount()
/*���ܣ������ڴ�������е��ڴ�������*/
{
	size_t BlockCount = 0;
	block* pool = start;
	while (pool->next) {
		pool = pool->next;
		BlockCount++;
	}
	return BlockCount;
}

int getAvailableBlockCount()
/*���ܣ������ڴ���п��пɷ�����ڴ�������*/
{
	size_t AvailableBlockCount = 0;
	block* pool = start;
	while (pool->next) {
		pool = pool->next;
		if (pool->flag == 0) {
			AvailableBlockCount++;
		}
	}
	return AvailableBlockCount;
}