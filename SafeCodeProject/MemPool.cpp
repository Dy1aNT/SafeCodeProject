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
/*功能：分配初始内存池，内存池初始大小默认为 1000 个块，即 256 x 1000 字节。
参数 size：内存池初始化时分配的内存块个数，默认为 1000 块。
返回值：成功完成 1000 块内存的申请则返回 0，否则返回-1.
提示：可使用 malloc、calloc 等函数完成内存初始化。*/
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
/*功能：从内存池中找到一块空闲内存块进行分配。分配的内存被初始化为 0。如果内存池内存已分配完，需对现有内存池进行扩充。
返回值：返回分配的内存块首地址，如果出现错误则返回空指针。
提示：可使用 malloc、calloc 函数、memset 函数。注意如果使用 realloc 扩充内存，通过 allocBlock 已经分配出去的内存块地址可能会无效。*/
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
		return NULL; //如果出现错误则返回空指针
	}
	memset(L->buf, NULL, 256 * sizeof(char));
	L->flag = 1;
	L->next = NULL;
	pool->next = L;
	return (L->buf);
}

int freeBlock(char* buf)
/*功能：将 buf 指向的内存块释放，该内存块并不执行堆内存的释放操作，只是放回内存池供下次分配使用。释放时，需对 buf 指向的内存区域进行清零操作。
参数 buf：指向要放回内存池中的内存块。
返回值：执行成功返回 0，buf 指针参数不合规返回-1，未找到对应的块返回-2.
提示：可使用 memset 函数，或者 Windows API SecureZeroMemory 函数清零。*/
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
/*功能：将整个内存池的内存全部释放，首先判断是否存在未回收的内存块，如果有则需返回-1，如果没有则对内存池所有内存块进行清零，然后执行 free 操作。.
返回值：执行成功返回 0，如果存在未回收的内存块，则需返回-1.
提示：可使用 free、memset 函数。*/
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
/*功能：无论是否存在未回收的内存块，都将整个内存池的内存块进行清零，然后执行free 操作。.
返回值：执行成功返回 0，出现错误，则返回-1.
提示：可使用 free、memset 函数。*/
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
/*功能：返回内存池中所有的内存块个数。*/
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
/*功能：返回内存池中空闲可分配的内存块个数。*/
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