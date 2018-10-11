#pragma once

int initPool(size_t size = 1000);
char* allocBlock();
int freeBlock(char* buf);
int freePool();
int freePoolForce();
int getBlockCount();
int getAvailableBlockCount();
