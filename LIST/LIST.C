/* Arsetnev Artemy, AA4, CGSG */

#include <stdio.h>   
#include <string.h>

#include "LIST.H"

VOID GetStr( CHAR *Str, INT MaxLen )
{
  INT i = 0;
  CHAR ch;     
  
  while ((ch = getchar()) != '\n')
    if (i < MaxLen - 1 && Str != NULL)
      Str[i++] = ch;
  if (i < MaxLen && Str != NULL)
    Str[i] = 0;
}

VOID ListDisplay( LIST *L )
{
  if (L == NULL)
    printf("\n");
  else
    while (L != NULL)
      printf("%s (%02d.%02d.%d)", L->Name, L->D, L->M, L->Y), printf((L = L->Next) == NULL ? "\n" : ",");
}

INT ListAddToFront( LIST **L, CHAR *Name, INT D, INT M, INT Y )
{
  LIST *NewElement;

  NewElement = malloc(sizeof(LIST));

  if (NewElement == NULL)
    return 0;

  strncpy(NewElement->Name, Name, MAX_STR - 1);

  NewElement->D = D;
  NewElement->M = M;
  NewElement->Y = Y;
  NewElement->Next = *L;
  *L = NewElement;

  return 1;
}

INT ListDelFromFront( LIST **L, CHAR *Name, INT *D, INT *M, INT *Y )
{
  LIST *Old;

  if (*L == NULL)
    return 0;

  Old = *L;

  if (Name != NULL)
    strncpy(Name, Old->Name, MAX_STR - 1);
  if (D != NULL)
    *D = Old->D;
  if (M != NULL)
    *M = Old->M;
  if (Y != NULL)
    *Y = Old->Y;
  *L = (*L)->Next;

  free(Old);

  return 1;
}

INT ListDelFromBack( LIST **L, CHAR *Name, INT *D, INT *M, INT *Y )
{
  if (*L == NULL)
    return 0;

  while ((*L)->Next != NULL)
    L = &(*L)->Next;

  if (Name != NULL)
    strncpy(Name, (*L)->Name, MAX_STR - 1);

  if (D != NULL)
    *D = (*L)->D;
  if (M != NULL)
    *M = (*L)->M;
  if (Y != NULL)
    *Y = (*L)->Y;

  free(*L);

  *L = NULL;

  return 1;
}

INT ListAddFromBack( LIST **L, CHAR *Name, INT D, INT M, INT Y )
{
  LIST *NewElement;

  if (*L == NULL)
    return 0;

  while ((*L)->Next != NULL)
    L = &(*L)->Next;

  NewElement = malloc(sizeof(LIST));
  

  strncpy(NewElement->Name, Name, MAX_STR - 1);

  NewElement->D = D;
  NewElement->M = M;
  NewElement->Y = Y;
  NewElement->Next = *L;
  *L = NewElement;

  return 1;
}

INT ListAddLoc( LIST **L, INT pos, CHAR *Name, INT D, INT M, INT Y )
{
  LIST *NewElement;

  while (pos-- > 0 && *L != NULL)
    L = &(*L)->Next;

  if ((NewElement = malloc(sizeof(LIST))) == NULL)
    return 0;

  strncpy(NewElement->Name, Name, MAX_STR - 1);

  NewElement->D = D;
  NewElement->M = M;
  NewElement->Y = Y;
  NewElement->Next = *L;
  *L = NewElement;

  return 1;
}

INT ListDelLoc( LIST **L, INT pos, CHAR *Name, INT *D, INT *M, INT *Y )
{
  while (pos-- > 0 && *L != NULL)
    L = &(*L)->Next;

  while ((*L)->Next != NULL)
  {
    if (Name != NULL)
      strncpy((*L)->Name, (*L)->Next->Name, MAX_STR - 1);

    (*L)->D = (*L)->Next->D;
    (*L)->M = (*L)->Next->M;
    (*L)->Y = (*L)->Next->Y;

    L = &(*L)->Next;
  }

  free(*L);

  *L = NULL;

  return 1;
}