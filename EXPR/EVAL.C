/* Arsentev Artemy, 09-4, 06.12.2024 */

#include <stdio.h>
#include <math.h>

#include "expr.h"

STACK StackEval;

jmp_buf ExprJumpBuf;

/* function to print errors */
VOID Error( CHAR *Str, ... )   /* elipsys */
{
  va_list ap;          /* variable for acccess to arg in '...' */

  printf("ERROR: ");
  va_start(ap, Str);   /* 'Str' - arg towards '...' */
  vprintf(Str, ap);
  va_end(ap);

  printf("\n");
  longjmp(ExprJumpBuf, 1);
}  /* end of 'Error' function */

/* function to count */
DBL Eval ( QUEUE *Q )
{
  TOK T;
  TOK res;
  STACK S = { NULL };

  while (Get(Q, &T))
  {
    if (T.Id == TOK_NAME || T.Id == TOK_NUM)
      Push(&S, T);

    else
    {
      TOK A = {0}, B = {0};

      if (T.Op != '@')
      {
        Pop(&S, &B);
        Pop(&S, &A);
      }

      else
        Pop(&S, &B);

      switch (T.Op)
      {
      case '+':
        A.Num += B.Num;
        break;
      case '/':
        if (B.Num == 0)
          Error("divide by zero");
        else
          A.Num /= B.Num;
        break;
      case '-':
        A.Num -= B.Num;
        break;
      case '*':
        A.Num *= B.Num;
        break;
      case '%':
        fmod(A.Num, B.Num);
        break;
      case '@':
        A.Num = -B.Num;
        break;
      case '^':
        if (A.Num == 0)
          Error("incorrect operation with zero");
        A.Num = pow(A.Num, B.Num);
        break;
      case '=':
        if (A.Id != TOK_NAME)
          Error("Error");
        SetValue(A.Name, B.Num);
        A.Num = B.Num;
        break;
      case ',':
        A.Num = B.Num;
        break;
      }
      Push(&S, A);
    }
  }
  Pop(&S, &res);
  return res.Num;
}  /* end of 'Eval' function */

/* END OF 'EVAL.C' FILE*/