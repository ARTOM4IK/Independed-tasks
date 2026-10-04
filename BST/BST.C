/* Arsetnev Artemy, 9-4, 22.11.2024 */
                                     
#include <stdio.h>

#include "BST.H"
/* Add key to tree function with recursion */
INT AccessTree( TREE **T, INT Key )
{
  if (*T == NULL)
  {
    *T = malloc(sizeof(TREE));
    if (*T == NULL)
    {
      printf("Not enough memory\n");
      return 0;
    }

    (*T)->Key = Key;
    (*T)->Less = (*T)->More = NULL;
    printf("Add a new node\n");

    return 1;
  }

  if ((*T)->Key == Key)
  {
    printf("Key %i is found\n", Key);
    return 1;
  }

  if ((*T)->Key < Key)
    return AccessTree(&(*T)->More, Key);
  return AccessTree(&(*T)->Less, Key);
}  /* end of 'AccessTree' function */

/* Add key to tree function without recursion */
INT AccessTree1( TREE **T, INT Key )
{
  while (TRUE)
  {
    if (*T == NULL)
    {
      *T = malloc(sizeof(TREE));
      if (*T == NULL)
      {
        printf("Not enough memory\n");
        return 0;
      }

      (*T)->Key = Key;
      (*T)->Less = (*T)->More = NULL;
      printf("Add a new node\n");

      return 1;
    }

    if ((*T)->Key == Key)
    {
      printf("Key %i is found\n", Key);
      return 1;
    }

    if ((*T)->Key < Key)
      *T = (*T)->More;
    else
      *T = (*T)->Less;
  }
  return 1;
}  /* end of 'AccessTree1' function */
/* Output tree function */
VOID DrawTree( TREE *T )
{
  static INT Level;
 
  Level++;
  if (T != NULL)
  {
    DrawTree(T->More);
    printf("%*c%d\n", Level * 3, ' ', T->Key);
    DrawTree(T->Less);
  }
  Level--;
}  /* end of 'DrawTree' function */

/* Output tree function */
VOID DrawTree1( TREE *T, INT Level )
{
  if (T != NULL)
  {
    DrawTree1(T->More, Level + 1);
    printf("%*c%d", Level * 3, ' ', T->Key);
    DrawTree1(T->Less, Level + 1);
  }
}  /* end of 'DrawTree1' function */

/* Output tree function */
VOID PutTree( TREE *T )
{
  if (T == NULL)
    printf("*");
  else
  {
    printf("%d(", T->Key);
    PutTree(T->Less);
    printf(",");
    PutTree(T->More);
    printf(")");
  }
}  /* end of 'PutTree' function */

/* Output sorted tree function */
VOID PutTreeSorted( TREE *T )
{
  if (T == NULL)
    printf("* ");
  else
  {
    PutTreeSorted(T->Less);
    printf("%d ", T->Key);
    PutTreeSorted(T->More);
  }
}  /* end of 'PutTreeSorted' function */

/* Clear tree function */
VOID ClearTree( TREE **T )
{
  if (*T != NULL)
  {
    ClearTree(&(*T)->More);
    ClearTree(&(*T)->Less);

    free(*T);
    *T = NULL;
  }
}  /* end of 'ClearTree' function */

/* Linearize tree function */
INT Linearize( TREE **T )
{
  INT n = 0;

  while (*T != NULL)
  {
    while ((*T)->Less != NULL)
    {
      TREE **P = &(*T)->Less;

      while (*P != NULL)
        P = &(*P)->More;
      *P = *T;
      *T = (*T)->Less;
      (*P)->Less = NULL;
    }
    T = &(*T)->More;
    n++;
  }
  return n;
}  /* end of 'Linearize' function */

/* Delete key in tree function */
VOID DeleteKey( TREE **T, INT key )
{
  TREE **P;
  TREE *old;

  if (*T == NULL)
  {
    printf("key is not deleted\n");
    return;
  }

  /* find the key to be deleted */
  while ((*T)->Key != key)
    if ((*T)->Key > key)
      T = &(*T)->Less;
    else
      T = &(*T)->More;

  /* overhang of key */
  old = *T;

  if ((*T)->Less == NULL)
    *T = (*T)->More;  
  else
  {
    /* find the biggest vertex (root is (*T)->Less) */
    P = &(*T)->Less;
    while (*P != NULL)
      P = &(*P)->More;

    *P = (*T)->More;
    *T = (*T)->Less;
  }
  free(old);  /* delete old key */

  printf("%d is deleted\n", key);
}  /* end of 'DeleteKey' function */

/* Balance tree function */
VOID BalanceTree( TREE **T, INT N )
{
  TREE **P;
  INT i;

  if (*T == NULL)
  {
    printf("tree is not balanced\n");
    return;
  }

  P = T;

  for (i = 0; i < N / 2; i++)
    P = &(*P)->More;

  (*P)->Less = *T;
  *T = *P;
  *P = NULL;

  /* Balance 'left' part of tree*/
  if (N / 4 > 0)
    BalanceTree(&(*T)->Less, N / 2);

  /* Balance 'right' part of tree*/
  if ((N / 2 - 1) / 2 > 0)
    BalanceTree(&(*T)->More, N / 2 - 1);

  printf("tree is balanced\n");
}  /* end of 'BalanceTree' function */

/* END OF 'BST.C' FILE */