/* Arsentev Artrmy, 09-4, 16.12.2024 */

#include <stdio.h>

#include "OPS.H"

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
}  /* End of 'GetStr' function */

/* function to print token */
VOID PrintTok( TOK T )
{
  if (T.Id == TOK_NUM)
    printf("num:%f\n", T.Num);
  else if (T.Id == TOK_OP)
    printf("op:%c\n", T.Op);
  else if (T.Id == TOK_NAME)
    printf("name:%s\n", T.Name);
  else if (T.Id == TOK_KEYW)
    printf("kw:%s\n", T.Name);
  else if (T.Id == TOK_SYMBOL)
    printf("symbol:%c\n", T.Op);
  else
    printf("<Unknown token>");
}  /* End of 'PrintTok' function */

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
}  /* End of 'Put' function */

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

}  /* End of 'Get' function */

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
}  /* End of 'Pop' function */

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

}  /* End of 'Push' function */

/* function to call display for queue */
VOID DisplayQueue( QUEUE *A )
{
  DisplayList(A->Head);
}  /* End of 'DisplayQueue' function */

/* function to clear */
VOID Clear( LIST **L)
{
  while (*L != NULL)
  {
    LIST *old = *L;
    *L = (*L)->Next;
    free(old);
  }
}  /* End of 'Clear' function */

/* function to call clear for queue */
VOID ClearQueue( QUEUE *Q )
{
  Clear(&Q->Head);
}  /* End of 'ClearQueue' function */

/* function to call clear for stack */
VOID ClearStack( STACK *Q )
{
  Clear(&Q->Top);
}  /* End of 'ClearStack' function */

INT ListAddToBack( LIST **L, TOK T )
{
  LIST *previous = NULL;

  while (*L != NULL)
  {
    previous = *L;
    L = &(*L)->Next;
  }

  if ((*L = malloc(sizeof(LIST))) == NULL)
    return 0;

  (*L)->Next = NULL;
  (*L)->T = T;

  return 1;
}

/* END OF 'LISTS.C' FILE*/