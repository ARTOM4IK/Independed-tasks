/* Arsetnev Artemy, AA4, 18.11.2024 */

#include <stdio.h>
#include <conio.h>

#include "LIST2.H"

void main( void )
{
  int flag = 1, testflag = 0;
  char option, name[STR_MAX];
  LIST *Start = NULL;
  
  printf("0 - exit\n"
    "1 - add to begin\n"
    "2 - del from begin\n"
    "3 - add to end\n"
    "4 - del from end\n"
    "5 - nothing yet\n"
    "6 - nothing yet\n"
    "7 - shift prev\n"
    "8 - shift next\n"
    "9 - clear list\n"
    "g - gremlin test\n");

  SetDbgMemHooks();

  while(flag)
  {
    switch (option = _getch())
    {
    case '0':
      flag = 0;
      break;
    case '1':
      GetStr(name, STR_MAX - 1);
      ListAddToFront(&Start, name);
      DisplayList(Start);
      break;
    case '2':
      ListDelToFront(&Start);       
      DisplayList(Start);
      break;
    case '3':                   
      GetStr(name, STR_MAX - 1);
      ListAddToBack(&Start, name);    
      DisplayList(Start);
      break;
    case '4':
      ListDelToBack(&Start);          
      DisplayList(Start);
      break;
    case '5':
      break;
    case '6':
      break;
    case '7':
      ShiftPrev(&Start);
      DisplayList(Start);
      break;
    case '8':
      ShiftNext(&Start);
      DisplayList(Start);
      break;
    case '9':
      ListClear(&Start); 
      DisplayList(Start);
      break;
    case 'g':
      GremlinTest(Start);
      break;
    }
    }
}