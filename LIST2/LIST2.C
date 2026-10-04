/* Arsetnev Artemy, AA4, 18.11.2024 */

#include <stdio.h>   
#include <string.h>
#include <time.h>

#include "LIST2.H"

void GetStr( CHAR *Str, INT MaxLen )
{
  INT i = 0;
  CHAR ch;     
  
  while ((ch = getchar()) != '\n')
    if (i < MaxLen - 1 && Str != NULL)
      Str[i++] = ch;
  if (i < MaxLen && Str != NULL)
    Str[i] = 0;
}

void ShiftNext( LIST **L )
{
  if (*L != NULL && (*L)->Next != NULL)
    *L = (*L)->Next;
}

void ShiftPrev( LIST **L )
{
  if (*L != NULL && (*L)->Prev != NULL)
    *L = (*L)->Prev;
}

void DisplayList( LIST *L )
{
  if (L == NULL)
    printf("\n");
  else
  {
    LIST *save = L; 

    while (L->Prev != NULL)
      L = L->Prev;

    while (L != NULL)
    {
      printf("%s%s", L->Str, L == save ? "(*)" : "");
      printf((L = L->Next) == NULL ? "\n" : ",");
    }
  }
}

INT ListAddToFront( LIST **L, CHAR *NewStr )
{
  LIST *next = NULL;

  while (*L != NULL)
  {
    next = *L;
    L = &(*L)->Prev;
  }

  if ((*L = malloc(sizeof(LIST))) == NULL)
    return 0;
 
  (*L)->Prev = NULL;
  (*L)->Next = next;
  strncpy((*L)->Str, NewStr, STR_MAX - 1);

  return 1;
}


INT ListDelToFront( LIST **L )
{
  if (*L == NULL)
    return 0;

  if ((*L)->Next == NULL)
    if ((*L)->Prev != NULL)
      *L = (*L)->Prev;

  while ((*L)->Prev != NULL)
  {
    L = &(*L)->Prev;
  }

  printf("%s is deleted\n", (*L)->Str);

  while ((*L)->Next != NULL)
  {
    strncpy((*L)->Str, (*L)->Next->Str, STR_MAX - 1);
    L = &(*L)->Next;
  }

  free(*L);
  *L = NULL;

  return 1;
}

INT ListAddToBack( LIST **L, CHAR *str )
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
  (*L)->Prev = previous;       
  strncpy((*L)->Str, str, STR_MAX - 1);

  return 1;
}

INT ListDelToBack( LIST **L )
{
  if (*L == NULL)
    return 0;

  if ((*L)->Next == NULL)
    if ((*L)->Prev != NULL)
      *L = (*L)->Prev;

  while ((*L)->Next != NULL)
  {
    L = &(*L)->Next;
  }

  printf("%s is deleted\n", (*L)->Str);

  free(*L);
  *L = NULL;

  return 1;
}

void ListClear( LIST **L )
{

  while (*L != NULL && (*L)->Prev != NULL)
    *L = (*L)->Prev;

  while (*L != NULL)
  {
    LIST *old = *L;

    *L = (*L)->Next;

    free(old);
  }
}

VOID GremlinTest( LIST *Start )
{
  UINT64 i = 0;
  INT option, j;
  CHAR name[STR_MAX];
  while (i++ < 1549)
  {
    srand(time(NULL));

    switch (option = rand() % 4 + 1)
    {
      case 1:
        for (j = 0; j < rand() % STR_MAX - 1 + 1; j++)
          name[j] = rand() % 26 + 'a';
        name[j] = 0;

        ListAddToFront(&Start, name);
        DisplayList(Start);
        break;
      case 2: 
        ListDelToFront(&Start);       
        DisplayList(Start);
        break;
      case 3:     
        for (j = 0; j < rand() % STR_MAX - 1 + 1; j++)
          name[j] = rand() % 26 + 'a';
        name[j] = 0;

        ListAddToBack(&Start, name);    
        DisplayList(Start);
        break;
      case 4:  
        ListDelToBack(&Start);          
        DisplayList(Start);
        break;
    }
  }
}