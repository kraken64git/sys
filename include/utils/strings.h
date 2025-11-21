#ifndef UTILS_STRINGS_H
#define UTILS_STRINGS_H

#include "stdint.h"

int isAlpha(char ch);
char upper(char ch);
char lower(char ch);

int strlen(const char *str);
int strcmp(const char *str1, char *str2);

#endif
