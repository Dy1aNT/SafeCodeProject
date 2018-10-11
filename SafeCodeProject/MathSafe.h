#pragma once
#include <stdint.h>
#define uint uint8_t

int8_t my_atoi8(char* str, int* of);
int iAdd_Safe(int8_t a, int8_t b, int* of);
int iSubtract_Safe(int8_t a, int8_t b, int* of);
int iMultiply_Safe(int8_t a, int8_t b, int* of);
int iDivide_Safe(int8_t a, int8_t b, int* of);
uint Add_Safe(uint8_t a, uint8_t b, int* of);
uint Subtract_Safe(uint8_t a, uint8_t b, int* of);
uint Multiply_Safe(uint8_t a, uint8_t b, int* of);
uint Divide_Safe(uint8_t a, uint8_t b, int* of);