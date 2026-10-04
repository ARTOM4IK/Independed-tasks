/* Arsentev Artrmy, 09-4, 16.12.2024 */

#include <stdio.h>

#include "OPS.H"

CMD *Proga;
STACK StackEval;
//QUEUE TokList;

jmp_buf ExprJumpBuf;

VOID main( VOID )
{
  CHAR FileName[MAX_STR];
  FILE *F;

  QUEUE Q = {NULL, NULL};     /* queue */

  if (setjmp(ExprJumpBuf))
  {
    ClearStack(&StackEval);
    ClearQueue(&Q);
    ClearQueue(&Queue1);
    ClearStack(&Stack2);

    getchar();
    return;
  }

  printf("Input file name:");
  GetStr(FileName, sizeof(FileName));
  F = fopen(FileName, "r");
  if (F != NULL)
  {
    static CHAR Buf[10000];

    while (fgets(Buf, sizeof(Buf) - 1, F) != NULL)
      Scanner(&TokList, Buf);
    fclose(F);
  }
  DisplayQueue(&TokList);
  ParseProgram();

  DoCmd(Proga);
  DisplayVar();
  printf("ggeztop");
  getchar();
}  /* End of 'main' function */

/* END OF 'T34OPS.C' FILE*/