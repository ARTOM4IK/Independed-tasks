/* Arsentev Artemy, 09-4, 06.12.2024 */

#include <stdio.h>
#include <conio.h>

#include <commondf.h>

#include "QUST.H"

VOID main( VOID )
{
  CHAR option;
  QUEUE Q = { NULL };  /* queue */
  STACK A = { NULL };  /* stack */
  INT data = 0;        /* data for input */

  printf("0 - exit\n"  /* menu */
    "1 - push\n"
    "2 - pop\n"
    "3 - get\n"
    "4 - put\n"
    "5 - display queue\n"
    "6 - display stack\n"
    "7 - clear queue\n"
    "8 - clear stack\n"
    "9 - gremlin test\n");

  SetDbgMemHooks();

  while(TRUE)
  {
    switch (option = _getch())
    {
    case '0':
      return;
      break;
    case '1':
      printf("push: ");
      scanf("%d", &data);
      Push(&A, data);
      break;
    case '2':
      Pop(&A, &data);
      printf("%d\n", data);
      break;
    case '3':
      Get(&Q, &data);
      printf("%d\n", data);
      break;
    case '4':
      printf("put: ");
      scanf("%d", &data);
      Put(&Q, data);
      break;
    case '5':
      DisplayQueue(&Q);
      break;
    case '6':
      DisplayStack(&A);
      break;
    case '7':
      ClearQueue(&Q);
      printf("Queue is cleared\n");
      break;
    case '8':
      ClearStack(&A);
      printf("Stack is cleared\n");
      break;
    case '9':
      GremlinTest(Q, A);
      printf("test is over\n");
      break;
    }
  }
}  /* end of main function */

/* END OF 'T32QUST.C' FILE */