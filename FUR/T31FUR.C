/* Arsentev Artemy, 9-4, 29.11.2024 */

#include <stdio.h>
#include <conio.h>
#include <windows.h>

#include "commondf.h"

#include "FUR.H"

VOID main( VOID )
{
  CHAR option;
  INT flag = 1;                            /* flag for loop */
  TREE *Root = Init("pig", NULL, NULL);    /* Root of the tree */

  printf("0 - exit\n" /* menu */
    "1 - Session\n"
    "2 - DrawTree\n"
    "3 - Save\n"
    "4 - Load\n");

  SetDbgMemHooks();

  while(flag)
  {
    switch (option = _getch())
    {
    case '0':
      flag = 0;
     break;
    case '1':
      Session(&Root);
     break;
    case '2':
      DrawTree(Root);
     break;
    case '3':
      SaveTree("AA4.db", Root);
      printf("tree is saved\n");
     break;
    case '4':
      LoadTree("AA4.db", &Root);
      printf("tree is loaded\n");
     break;
    }
  }
}  /* End of 'main' function */

/* END OF 'T31FUR.C' FILE */