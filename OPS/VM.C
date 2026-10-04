/* Arsentev Artrmy, 09-4, 16.12.2024 */

#include <stdio.h>
#include <math.h>

#include "OPS.H"

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
}

/* function to count */
DBL Eval ( LIST *Q )
{
  TOK T;
  TOK res;
  STACK S = { NULL };

  while (Q != NULL)
  {
    T = Q->T;
    Q = Q->Next;

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

VOID DoCmd( CMD *C )
{
  while (C->Next != NULL)
  {
    /* interpritate current command */
    if (C->Id == CMD_EXPR)
      Eval(C->Expr);
    else if (C->Id == CMD_IF)
      if (Eval(C->Expr))
        DoCmd(C->C1);
      else
        DoCmd(C->C2);
    else if (C->Id == CMD_WHILE)
      while (Eval(C->Expr))
        DoCmd(C->C1);

    /* go to next command */
    C = C->Next;
  }
}

VOID CmdInit( CMD **C )
{
  if ((*C = malloc(sizeof(CMD))) == NULL)
    Error("No memory");
  (*C)->Id = CMD_EXPR;
  (*C)->Expr = NULL;
  (*C)->C1 = (*C)->C2 = (*C)->Next = NULL;
}

/* Clear tree function */
VOID CmdClear( CMD **C )
{
  if (*C != NULL)
  {
    CmdClear(&(*C)->Next);

    free(*C);
    *C = NULL;
  }
}  /* end of 'ClearTree' function */

/* END OF 'VM.C' FILE*/