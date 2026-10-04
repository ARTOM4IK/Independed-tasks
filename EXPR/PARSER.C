/* Arsentev Artemy, 09-4, 06.12.2024 */

#include <stdio.h>

#include "EXPR.H"

QUEUE Queue1;
STACK Stack2;

/* function to set priority */
INT GetPrior( CHAR Op )
{
  switch(Op)
  {
  case '(':
    return 0;
    break;
  case ')':
    return 1;
    break;
  case ',':
    return 2;
    break;
  case '=':
    return 3;
    break;
  case '+':
  case '-':
    return 4;
    break;
  case '*':
  case '/':
  case '%':
    return 5;
    break;
  case '^':
    return 6;
    break;
  case '@':
    return 7;
    break;
  }

  Error("Unrecognised character '%c'\n", Op);

  return -1;
}  /* end of 'GetPrior' function */

/* function to drop operands */
VOID DropOpers( CHAR Op )
{
  while (Stack2.Top != NULL && GetPrior(Stack2.Top->T.Op) >= GetPrior(Op))
  {
    TOK T;

    Pop(&Stack2, &T);
    Put(&Queue1, T);
  }
}  /* end of 'DropOpers' function */

/* parser function */
VOID ParserExpr( QUEUE *QRes, QUEUE *Q )
{
  TOK T = {0};
  enum
  {
    STATE_PREFIX, STATE_SUFFIX, STATE_DONE, STATE_END
  } state = STATE_PREFIX;

  while (state != STATE_END)
  {
    if (state <= STATE_SUFFIX)
      if (!Get(Q, &T))
      {
        if (state == STATE_SUFFIX)
          state = STATE_DONE;
        else
          Error("Unexpected expression\n");
      }
    switch(state)
    {
    case STATE_PREFIX:
        if (T.Id == TOK_NAME)
        {
          state = STATE_SUFFIX;
          Put(&Queue1, T);
        }
        else if (T.Id == TOK_NUM)
          Put(&Queue1, T), state = STATE_SUFFIX;
        else if (T.Id == TOK_OP && T.Op == '-')
        {
          T.Op = '@';
          DropOpers('@');
          Push(&Stack2, T);
        }
        else if (T.Id == TOK_OP && T.Op == '(')
          Push(&Stack2, T);
        else
          Error("Expected number or ')'");
        break;
    case STATE_SUFFIX:
        if (T.Id == TOK_NUM)
          Put(&Queue1, T);
        else if (T.Id == TOK_OP)
        {
          DropOpers(T.Op);
          if (T.Op != ')')
            Push(&Stack2, T), state = STATE_PREFIX;
         else
            if (!Pop(&Stack2, NULL))
              Error("Missing '('");
        }
        else
          Error("Expected number or ')'");
        break;
    case STATE_DONE:
      DropOpers(')');
      if (Stack2.Top != NULL)
        Error("Missing ')'\n");
      *QRes = Queue1;
      Queue1.Head = NULL;
      state = STATE_END;
      break;
    }
  }
}  /* end of 'ParserExpr' function */

/* END OF 'EVAL.C' FILE*/