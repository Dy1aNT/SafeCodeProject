#pragma once

typedef rsize_t size_t;

int isUsernameOK(char* name);
int isPasswordOK(char* pwd);
int gets_safe(char *str, rsize_t n);
int strcpy_safe(char* dest, rsize_t destsz, const char* src);