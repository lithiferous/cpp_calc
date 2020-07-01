#include <iostream>
#include <locale.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mystring.h"

#define BUFF_SIZE 128
#define MBUFF_SIZE BUFF_SIZE / 2 + 1

#define separators " \t"
#define filename "calc.dat"

//typedef int bool;
#define false 0
#define true 1


void xassert(bool trueCondition, const char *s1, const char *s2, const char *s3)
{
  if (!trueCondition) {
    printf("Error:%s%s%s\n", s1, s2, s3);
    exit(3);
  }
}

void mvPtrFwd(const char *&src, const char *str)
{
  while (haschar(str, *src))
    src++;
}

float getPow(float x, unsigned int n)
{
  if (n == 0)
    return 1;
  else if (n == 1)
    return x;
  else if (n % 2 == 0)
    return getPow(x * x, n / 2);
  else
    return getPow(x * x, n / 2) * x;
}

class expressionLine{
private:
  int m_lineNo;
  const char *curSrc;
  const char *m_src;
public:
  expressionLine(const char *Src,
                 int lineNo):
                 curSrc(Src),
                 m_src(Src),
                 m_lineNo(lineNo)

  {
  }
public:
  void syntaxCheck(bool trueCondition,
                  const char *errorText1,
                  const char *errorText2,
                  const char *errorText3)
  {
    if (!trueCondition) {
      printf("Syntax error: %s%s%s in line %d at position %d\n", errorText1,
              errorText2, errorText3, m_lineNo, curSrc - m_src + 1);
      exit(3);
    }
  }

  bool isNeg(const char *&src)
  {
    mvPtrFwd(src, separators);
    if (*src == '-') {
      src++;
      return true;
    }
    return false;
  }

  float getNum()
  {
    mvPtrFwd(curSrc, separators);
    float num = 0;
    bool wasDigit = isdigit(*curSrc);
    while (isdigit(*curSrc)) {
      num = num * 10 + *curSrc++ - '0';
    }
    bool wasFraction = false;
    float divisor = 10;
    if (haschar(".,", *curSrc)) {
      *curSrc++;
      wasFraction = isdigit(*curSrc);
      while (isdigit(*curSrc)) {
        num += (*curSrc++ - '0') / divisor;
        divisor *= 10;
      }
    }
    syntaxCheck(wasDigit || wasFraction, "Expected number", "", "");
    return num;
  }

  float getArg()
  {
    float res;
    mvPtrFwd(curSrc, separators);
    if (*curSrc == '(') {
      curSrc++;
      res = getSum();
      mvPtrFwd(curSrc, separators);
      syntaxCheck(*curSrc == ')', "Expected \")\"", "", "");
      curSrc++;
    } else {
      syntaxCheck(*curSrc == '.' || isdigit(*curSrc), "Incorrect number", "", "");
      res = getNum();
    }
    return res;
  }

  float getPower()
  {
    float num1 = getArg();
    for (;;) {
      mvPtrFwd(curSrc, separators);
      if (*curSrc != '^') {
        break;
      }
      char op = *curSrc++;
      float num2 = getArg();
      num1 = getPow(num1, (int)num2);
    }
    return num1;
  }

  float getMul()
  {
    float num1 = getPower();
    for (;;) {
      mvPtrFwd(curSrc, separators);
      if (*curSrc != '*' && *curSrc != '/') {
        break;
      }
      char op = *curSrc++;
      float num2 = getPower();
      if (op == '*') {
        num1 *= num2;
      } else {
        num1 /= num2;
      }
    }
    return num1;
  }

  float getSum()
  {
    bool neg = isNeg(curSrc);
    mvPtrFwd(curSrc, separators);
    float num1 = getMul();
    if(neg)
      num1=-num1;
    for (;;) {
      mvPtrFwd(curSrc, separators);
      if (*curSrc != '+' && *curSrc != '-') {
        break;
      }
      char op = *curSrc++;
      float num2 = getMul();
      if (op == '+') {
        num1 += num2;
      } else {
        num1 -= num2;
      }
    }
    return num1;
  }

   void getExpression()
  {
    mvPtrFwd(curSrc, separators);
    if (*curSrc != '"' && *curSrc != '\0') {
      printf("-> %s\n", curSrc);
      float res = getSum();
      if (*curSrc != '\0') {
          char ss[2];
          ss[0] = *curSrc;
          ss[1] = '\0';
          syntaxCheck(false, "Unexpected symbol \"", ss, "\"");
      }
      printf("Your result: %.6f\n", res);
      //return res;
    }
  }
};


int main()
{
  setlocale(0, "Rus");
  FILE *fp = fopen(filename, "r");
  //fp = fopen(filename, "r");
  //xassert(fp != NULL, "File ", filename, " is not opened");
  printf("Hello, welcome to c-calculator\n");
  char Src[BUFF_SIZE];
  int lineNo = 0;
  while (getLine(fp, Src)) {
    expressionLine(Src, lineNo++).getExpression();
  }
  return 0;
}
