#include <locale.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFF_SIZE 128
#define MBUFF_SIZE BUFF_SIZE / 2 + 1

#define separators " \t"
#define filename "calc.dat"

//typedef int bool;
#define false 0
#define true 1


bool getLine(FILE *fp, char *src) 
{
  char ch;
  int i = 0;
  while (i < BUFF_SIZE - 1) {
    ch = getc(fp);
    if (ch == '\n' || ch == EOF)
      break;
    *src++ = ch;
  }
  *src = '\0';
  if (ch == '\n')
    return true;
  return false;
}

bool haschar(const char *str, char ch) 
{
  while (*str != '\0') {
    if (*(str++) == ch)
      return true;
  }
  return false;
}



