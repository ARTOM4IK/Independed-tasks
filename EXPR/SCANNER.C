/* Arsentev Artemy, 09-4, 06.12.2024 */

#include <stdio.h>

#include <ctype.h>

#include "expr.h"

/* function for scanning inputed string */
VOID Scanner( QUEUE *Q, CHAR *S )
{
  TOK T = {0};

  /* go through all symbols */
  while (*S != 0)
  {
    if (isspace(*S))
      S++;
    if (*S == '+' || *S == '-' || *S ==  '/' || *S == '*' || *S == '(' || *S == ')' || *S == '^' || *S == '%' || *S == '=' || *S == ',')
    {
      T.Id = TOK_OP;
      T.Op = *S++;
    }
    else if (isdigit((UCHAR)*S))
    {
      /* DBL */
      T.Id = TOK_NUM;
      T.Num = 0;
      /* integer */
      while (isdigit(*S))
        T.Num = T.Num * 10 + *S++ - '0';
      /* DBL part */
      if (*S == '.')
      {
        DBL denum = 1;
        S++; /* go from point to digit */
        while (isdigit((UCHAR)*S))
          T.Num += (*S++ - '0') / (denum *= 10);
      }
    }
    else if (islower((UCHAR)*S) || isupper((UCHAR)*S))
    {
      int i = 0;
      /* VAR */
      T.Id = TOK_NAME;
      while (islower((UCHAR)*S) || isupper((UCHAR)*S))
        T.Name[i++] = (UCHAR)*S++;
    }
    else
      Error("Unrecognized character '%c'\n", *S);
    /* adds lexem into queue */
    Put(Q, T);
  }
}

/* END OF 'SCANNER.C' FILE*/