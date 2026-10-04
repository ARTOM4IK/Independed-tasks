/* Arsentev Artemy, 09-4, 06.12.2024 */

#include <stdio.h>

#include "QUST.H"

/* function to push stack */
INT Push( STACK *A, INT NewEl )
{
  LIST *n;

  n = malloc(sizeof(LIST));
  if (n == NULL)
    return 0;

  n->data = NewEl;
  n->Next = A->Top;

  A->Top = n;

  return 1;
}  /* end of 'Push' function */

/* function to pop stack */
INT Pop( STACK *A, INT *data )
{
  LIST *old;

  if (A->Top == NULL)
    return 0;

  old = A->Top;

  if (data != NULL)
    *data = A->Top->data;

  A->Top = A->Top->Next;

  free(old);
  return 1;
}  /* end of 'Pop' function */

/* function to put queue */
INT Put( QUEUE *A, INT NewEl )
{
  LIST *n;

  n = malloc(sizeof(LIST));
  if (n == NULL)
    return 0;

  n->data = NewEl;
  n->Next = NULL;

  if (A->Head == NULL)
    A->Head = A->Tail = n;
  else
  {
    A->Tail->Next = n;
    A->Tail = n;
  }
  return 1;
}  /* end of 'Put' function */

/* function to get queue */
INT Get( QUEUE *A, INT *data )
{
  LIST *old;

  if (A->Head == NULL)
    return 0;

  old = A->Head;

  if (data != NULL)
    *data = A->Head->data;
  A->Head = A->Head->Next;

  free(old);

  return 1;

}  /* end of 'Get' function */

/* function to display list */
VOID Display( LIST *L )
{
  if (L == NULL)
    printf("Empty\n");
  else
    while (L != NULL)
      printf("%d", L->data), printf((L = L->Next) == NULL ? "\n" : ",");
}  /* end of 'Display' function */

/* function to call display for stack */
VOID DisplayStack( STACK *A )
{
  Display(A->Top);
}  /* end of 'DisplayStack' function */

/* function to call display for queue */
VOID DisplayQueue( QUEUE *A )
{
  Display(A->Head);
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

/* function to call clear for list */
VOID ClearList( LIST *Q )
{
  Clear(&Q);
}  /* end of 'ClearList' function */

/* function of gremlin test */
VOID GremlinTest( QUEUE Q, STACK S )
{
  int i, data;

  for (i = 0; i < 1000; i++)
  {
    data = rand();
    switch (rand() % 8)
    {
    case 1:
      Push(&S, data);
      break;
    case 2:
      Pop(&S, &data);
      printf("%d\n", data);
      break;
    case 3:
      Get(&Q, &data);
      printf("%d\n", data);
      break;
    case 4:
      Put(&Q, data);
      break;
    case 5:
      DisplayQueue(&Q);
      break;
    case 6:
      DisplayStack(&S);
      break;
    case 7:
      ClearQueue(&Q);
      printf("Queue is cleared\n");
      break;
    case 8:
      ClearStack(&S);
      printf("Stack is cleared\n");
      break;
    }
  }
}  /* end of 'GremlinTest' function */

/* END OF 'QUST.C' FILE */