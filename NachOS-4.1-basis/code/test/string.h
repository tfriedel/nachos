#ifndef STRING_H
#define STRING_H
#include "syscall.h"

#define NULL ((void *)0)
#define CHAR_BIT        8
#define CHAR_MAX        255
#define CHAR_MIN        0
#define SCHAR_MAX       127
#define SCHAR_MIN       -128

#define INT_MAX         2147483647
#define INT_MIN         (-INT_MAX - 1)
#define UINT_MAX        4294967295U

#define LONG_MAX        2147483647L
#define LONG_MIN        (-LONG_MAX - 1)

extern int isalnum(char c);
extern int isalpha(char c);
extern int iscntrl(char c);
extern int islower(char c);
extern int isspace(char c);
extern int isupper(char c);
extern char toupper(char c);
extern char tolower(char c);
extern int isnumber(char c, int base);
extern int tonumber(char c);
extern char todigit(int c);
extern int isxdigit(char c);
extern int isdigit(char c);
extern int strlen(char *str);
extern char *strcat(char *s1, const char *s2);
extern int strcmp (char *s1, char *s2);
extern char *strcpy(char *dst0, char *src0);
extern void bzero(void *b, int length);
extern int print(OpenFileId, char *buffer);
extern int println(OpenFileId id, char *buffer);
extern long int strtoi(char *s, int base, char **scan_end);
extern int atoi(const char *nptr);
extern int readLine(char *buf, int len);
extern void printInt(OpenFileId id, int n);
extern int putchar(int character );

#endif /* STRING_H */
