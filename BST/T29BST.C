/* Arsetnev Artemy, 9-4, 22.11.2024 */

#include <stdio.h>
#include <conio.h>
#include <windows.h>

#include "BST.H"

/* The main program function */
VOID main( VOID )
{
  CHAR option;
  INT flag = 1,      /* flag for loop */
    key;             /* key for filling tree */
  TREE *Root = NULL; /* Root of the tree */

  PutTree(Root);
  printf("\n");
  PutTreeSorted(Root);
  printf("\n");
  printf("\n0 - exit\n"
    "1 - AccessTree\n"
    "2 - AccessTree1\n"
    "3 - DrawTree\n"
    "4 - ClearTree\n"
    "5 - Delete Key\n"
    "6 - BalanceTree\n"
    "7 - Clear window and Show Menu\n");

  SetDbgMemHooks();

  while(flag)
  {
    switch (option = _getch())
    {
    case '0':
      flag = 0;
      break;
    case '1':
      printf("number: ");
      scanf("%d", &key);
      AccessTree(&Root, key);
      break;
    case '2':           
      printf("number: ");
      scanf("%d", &key);
      AccessTree1(&Root, key);
      break;
    case '3':           
      DrawTree(Root);
    break;
    case '4':           
      ClearTree(&Root);
      printf("tree is cleared\n");
    break;
    case '5':
      printf("key: ");
      scanf("%d", &key);
      DeleteKey(&Root, key);
    break;
    case '6':           
      BalanceTree(&Root, Linearize(&Root));
    break;
    case '7':
      system("cls");
      PutTree(Root);
      printf("\n");
      PutTreeSorted(Root);
      printf("\n");
      printf("\n0 - exit\n"
        "1 - AccessTree\n"
        "2 - AccessTree1\n"
        "3 - DrawTree\n"
        "4 - ClearTree\n"
        "5 - Delete Key\n"
        "6 - BalanceTree\n"
        "7 - Clear window and Show Menu\n");
      break;
    }
  }
}  /* End of 'main' function */

/* END OF 'T29BST.C' FILE */