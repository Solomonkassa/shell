#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

extern char **environ;
char *_strtok(char *str, const char *delim);
char *_getline();
int _strncmp(const char *str1, const char *str2, size_t n);
char* _getenv(const char* name);
int _strcmp(const char* str1, const char* str2);

#endif
