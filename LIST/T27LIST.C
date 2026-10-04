/* Arsetnev Artemy, AA4, CGSG */

#include <stdio.h>
#include <conio.h>

#include "LIST.H"

void main( void )
{
  CHAR option, name[MAX_STR];
  INT d, m, y, pos, flag = 1;
  LIST *Start = NULL;
  
  printf("0 - exit\n"
    "1 - add to list front\n"
    "2 - del from list front\n"
    "3 - add to list back\n"
    "4 - del from list back\n"
    "5 - add to list arbitrary location\n"
    "6 - del from list arbitrary location\n"
    "7 - list clear\n");

  SetDbgMemHooks();

  while(flag)
  {
    switch (option = _getch())
    {
    case '0':
      flag = 0;
      break;
    case '1':
      GetStr(NULL, 0);
      printf("Name: ");
      GetStr(name, MAX_STR);   
      printf("Day: ");
      scanf("%d", &d);
      printf("Month: ");
      scanf("%d", &m);
      printf("Year: ");
      scanf("%d", &y);
      printf("\n");
      ListAddToFront(&Start, name, d, m, y);
      ListDisplay(Start);
      break;
    case '2':
      ListDelFromFront(&Start, name, &d, &m, &y);
      printf("%s (%02d.%02d.%d)\n", name, d, m, y);
      break;
    case '3':
      GetStr(NULL, 0);
      printf("Name: ");
      GetStr(name, MAX_STR);  
      printf("Day: ");
      scanf("%d", &d);
      GetStr(NULL, 0);
      printf("Month: ");
      scanf("%d", &m);
      GetStr(NULL, 0);
      printf("Year: ");
      scanf("%d", &y);
      printf("\n");
      ListAddFromBack(&Start, name, d, m, y);
      ListDisplay(Start);
      break;
    case '4':
      ListDelFromBack(&Start, name, &d, &m, &y);
        printf("%s (%02d.%02d.%d)\n", name, d, m, y);
      break;
    case '5':
      GetStr(NULL, 0);
      printf("Name: ");
      GetStr(name, MAX_STR);  
      printf("Day: ");
      scanf("%d", &d);
      GetStr(NULL, 0);
      printf("Month: ");
      scanf("%d", &m);
      GetStr(NULL, 0);
      printf("Year: ");
      scanf("%d", &y);
      printf("\n");
      printf("Position: ");
      scanf("%d", &pos);
      ListAddLoc(&Start, pos, name, d, m, y);
      ListDisplay(Start);
      break;
    case '6':
      printf("Position: ");
      scanf("%d", &pos);
      ListDelLoc(&Start, pos, name, &d, &m, &y); 
      printf("%s (%02d.%02d.%d)\n", name, d, m, y);
      break;
    case '7':
      while (ListDelFromFront(&Start, NULL, NULL, NULL, NULL));
      break;
    }
  }
}