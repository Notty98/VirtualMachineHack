// ARCH1718.stefano.notari.0000832003
#include <stdio.h>
#include <string.h>
#include "constants.h"
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>

void removeSpaces(char* line,int length);
int getInt(string line);
void myMemcpy(void *dest, void *src, size_t n);
int myStrCmp(const char *string1,const char *string2 );
bool myStrStr(const char *str,const char *sub);
void nextSpace(string line,string firstPart,string lastPart);
bool isDigit(const char c);
bool isAlpha(const char c);
bool isSpecialSymbol(const char c);
void myStrcpyat(string to,string append);