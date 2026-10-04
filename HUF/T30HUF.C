/* Arsentev Artemy, 9-4, 25.11.2024 */

#include <stdio.h>
#include <conio.h>

#include "HUF.H"

#include "commondf.h"

/* The main program function */
VOID main( VOID )
{
  CHAR option;
  INT flag = 1;         /* flag for loop */
  TREE *Root = NULL;    /* Root of the tree */

  printf("0 - exit\n"   /* menu */
    "1 - Compress\n"
    "2 - Decompress\n"
    "3 - Stat\n");

  SetDbgMemHooks();     /* check memory leak */

  while(flag)
  {
    switch (option = _getch())
    {
    case '0':
      flag = 0;
      break;
    case '1':  /* compress file */
      Compress("orwell.txt", "Compressed.txt");
      printf("compressed\n");                           
      break;
    case '2':  /* decompress file */
      Decompress("Compressed.txt", "Decompressed.txt");
      printf("decompressed\n");
      break;
    case '3':  /* output statistics */
      Stat("orwell.txt");     
      break;
    }
  }
}  /* End of 'main' function */

/* END OF 'T30HUF.C' FILE */