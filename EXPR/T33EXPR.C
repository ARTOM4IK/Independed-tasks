/* Arsentev Artemy, 09-4, 06.12.2024 */

#include <stdio.h>

#include "expr.h"

STACK StackEval;

jmp_buf ExprJumpBuf;

VARTREE *VarTable;

VOID main( VOID )
{
  CHAR str[MAX];              /* string for input */
  QUEUE Q = {NULL, NULL};     /* queue */
  QUEUE QRes = {NULL, NULL};  /* queue result */

  SetDbgMemHooks();

  if (setjmp(ExprJumpBuf))
  {
    ClearStack(&StackEval);
    ClearQueue(&Q);
    ClearQueue(&Queue1);
    ClearStack(&Stack2);

    getchar();
    return;
  }
  printf("Expr:");
  GetStr(str, sizeof(str));
  Scanner(&Q, str);
  ParserExpr(&QRes, &Q);
  printf("Eval: %f\n", Eval(&QRes));
  DisplayVar();

  getchar();
} /* end of main function */

/* END OF 'T33EXPR.C' FILE*/