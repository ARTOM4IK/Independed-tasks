/* Arsentev Artrmy, 09-4, 16.12.2024 */

#include <stdio.h>

#include "OPS.H"

CMD *Proga;

QUEUE TokList;
TOK TokCurrent;
INT IsEOTL;  /* 1 to End of lexem (End-Of-Token-List) */

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
}  /* End of 'GetPrior' function */

/* function to drop operands */
VOID DropOpers( CHAR Op )
{
  while (Stack2.Top != NULL && GetPrior(Stack2.Top->T.Op) >= GetPrior(Op))
  {
    TOK T;

    Pop(&Stack2, &T);
    Put(&Queue1, T);
  }
}  /* End of 'DropOpers' function */

/* Parser function */
VOID ParserExpr( LIST **Expr )
{
  INT openflag = 0, closeflag = 0;
  enum
  {
    STATE_PREFIX, STATE_SUFFIX, STATE_DONE, STATE_END
  } state = STATE_PREFIX;

  while (state != STATE_END)
  {
    if (TokCurrent.Id == TOK_OP && TokCurrent.Op == ')')
      closeflag++;
    else if (TokCurrent.Id == TOK_OP && TokCurrent.Op == '(')
      openflag++;
    if (closeflag > openflag)
    {
      *Expr = Queue1.Head;
      return;
    }
    if (state <= STATE_SUFFIX)
      if (!Get(&TokList, &TokCurrent))
      {
        if (state == STATE_SUFFIX)
          state = STATE_DONE;
        else
          Error("Unexpected expression\n");
      }
    switch(state)
    {
    case STATE_PREFIX:
      if (IsTokAnyNum() || IsTokAnyName())
        Put(&Queue1, TokCurrent), state = STATE_SUFFIX, ParseAnyTok();
      else if (IsTokOp('('))
        Push(&Stack2, TokCurrent), openflag++, ParseAnyTok();
      break;
    case STATE_SUFFIX:
        if (IsTokAnyNum())
          Put(&Queue1, TokCurrent);
        else if (IsTokAnyOp())
        {
          DropOpers(TokCurrent.Op);
          if (!IsTokOp(')'))
            Push(&Stack2, TokCurrent), state = STATE_PREFIX;
/*         else
            if (!Pop(&Stack2, NULL))
              Error("Missing '('");*/
        }
        else
          state = STATE_DONE;
        break;
    case STATE_DONE:
      DropOpers(')');
      if (Stack2.Top != NULL)
        Error("Missing ')'\n");

      state = STATE_END;
      break;
    }
  }
  *Expr = Queue1.Head;
}  /* End of 'ParserExpr' function */

VOID ParseCmd( CMD **C )
{
  *C = NULL;
  if (IsTokKw(IF))
  {
    CmdInit(C);
    (*C)->Id = CMD_IF;
    ParseKw(IF);
    ParseOp('(');
    ParserExpr(&(*C)->Expr);
    ParseOp(')');
    ParseCmd(&(*C)->C1);
    if (IsTokKw(ELSE))
    {
      ParseKw(ELSE);
      ParseCmd(&(*C)->C2);
    }
  }
  else if (IsTokKw(WHILE))
  {
    CmdInit(C);
    (*C)->Id = CMD_WHILE;
    ParseKw(WHILE);
    ParseOp('(');
    ParserExpr(&(*C)->Expr);
    ParseOp(')');
    ParseCmd(&(*C)->C1);
  }
  else if (IsTokSym('{'))
  {
    ParseSym('{');
    while (!IsTokSym('}'))
    {
      ParseCmd(C);
      C = &(*C)->Next;
    }
    ParseSym('}');
  }
  else
  {
    CmdInit(C);
    (*C)->Id = CMD_EXPR;
    ParserExpr(&(*C)->Expr);
    ParseSym(';');
  }
}

VOID ParseProgram( VOID )
{
  CMD **cmd = &Proga;

  Proga = NULL;
  IsEOTL = 0;
  /* NextTok(); */
  while (!IsEOTL)
  {
    ParseCmd(cmd);
    cmd = &(*cmd)->Next;
  }
}

/* END OF 'PARSER.C' FILE*/