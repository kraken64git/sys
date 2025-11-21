#include "utils/strings.h"

int isAlpha(char ch)
{
    return (((ch >= 'A') && (ch <= 'Z')) || ((ch >= 'a') && (ch <= 'z')));
}

char upper(char ch)
{
    if ((ch >= 'a') && (ch <= 'z'))
        return (ch - 32);
    return ch;
}

char lower(char ch)
{
    if ((ch >= 'A') && (ch <= 'Z'))
        return (ch + 32);
    return ch;
}

int strlen(const char *str) {
    int len = 0;
    while (*str++)
        len++;
    return len;
}

int strcmp(const char *str1, char *str2) {
    int i = 0;
    while ((str1[i] == str2[i])) {
        if (str2[i++] == 0)
            return 0;
    }
    return 1;
}
