/* Arsentev Artemy, 09-4, 06.12.2024 */

#include <stdio.h>

#include "expr.h"

/* function to get string */
VOID GetStr( CHAR *Str, INT MaxLen )
{
  INT i = 0;
  CHAR ch;
  
  while ((ch = getchar()) != '\n')
    if (i < MaxLen - 1 && Str != NULL)
      Str[i++] = ch;
  if (i < MaxLen && Str != NULL)
    Str[i] = 0;
}  /* end of 'GetStr' function */

/* function to print token */
VOID PrintTok( TOK T )
{
  if (T.Id == TOK_NUM)
    printf("num:%f", T.Num);
  else if (T.Id == TOK_OP)
    printf("op:%c", T.Op);
  else
    printf("<Unknown token>");
}  /* end of 'PrintTok' function */

/* Output list function */
void DisplayList( LIST *L )
{
  if (L == NULL)
    printf("Empty\n");
  else
    while (L != NULL)
    {
      PrintTok(L->T), ((L = L->Next) == NULL ? "\n" : ",");
    }
} /* End of 'DisplayList' function */

/* function to put queue */
VOID Put( QUEUE *A, TOK NewEl )
{
  LIST *n;

  n = malloc(sizeof(LIST));
  if (n == NULL)
    Error("no memory");

  n->T = NewEl;
  n->Next = NULL;

  if (A->Head == NULL)
    A->Head = A->Tail = n;
  else
  {
    A->Tail->Next = n;
    A->Tail = n;
  }
}  /* end of 'Put' function */

/* function to get queue */
INT Get( QUEUE *A, TOK *data )
{
  LIST *old;

  if (A->Head == NULL)
    return 0;

  old = A->Head;

  if (data != NULL)
    *data = A->Head->T;
  A->Head = A->Head->Next;

  free(old);

  return 1;

}  /* end of 'Get' function */

/* function to pop stack */
INT Pop( STACK *A, TOK *data )
{
  LIST *old;

  if (A->Top == NULL)
    return 0;

  old = A->Top;

  if (data != NULL)
    *data = A->Top->T;

  A->Top = A->Top->Next;

  free(old);
  return 1;
}  /* end of 'Pop' function */

/* function to push stack */
VOID Push( STACK *A, TOK NewEl )
{
  LIST *n;

  n = malloc(sizeof(LIST));
  if (n == NULL)
    Error("no memory");

  n->T = NewEl;
  n->Next = A->Top;

  A->Top = n;

}  /* end of 'Push' function */

/* function to call display for queue */
VOID DisplayQueue( QUEUE *A )
{
  DisplayList(A->Head);
}  /* end of 'DisplayQueue' function */

/* function to clear */
VOID Clear( LIST **L)
{
  while (*L != NULL)
  {
    LIST *old = *L;
    *L = (*L)->Next;
    free(old);
  }
}  /* end of 'Clear' function */

/* function to call clear for queue */
VOID ClearQueue( QUEUE *Q )
{
  Clear(&Q->Head);
}  /* end of 'ClearQueue' function */

/* function to call clear for stack */
VOID ClearStack( STACK *Q )
{
  Clear(&Q->Top);
}  /* end of 'ClearStack' function */

/* END OF 'LISTS.C' FILE*/