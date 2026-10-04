/* Arsentev Artrmy, 09-4, 16.12.2024 */

#include <stdio.h>
#include <string.h>

#include "OPS.H"

VARTREE *VarTable = {0};  /* Tree with variables */

/* function to Access Tree */
VARTREE * AccessTree( CHAR *Name )
{
  VARTREE **T = &VarTable;
  int n;

  while (*T != NULL && (n = strcmp((*T)->Name, Name)) != 0)
    T = n > 0 ? &(*T)->Less : &(*T)->More;
  if (*T != NULL)
    return *T;
  if ((*T = malloc(sizeof(VARTREE))) == NULL)
    Error("Not enough memory");
  strncpy((*T)->Name, Name, 300);
  (*T)->VarNum = 0;
  (*T)->Less = (*T)->More = NULL;

  return *T;
}  /* End of 'AccessTree' function */

VOID SetValue( CHAR *Name, DBL Value )
{
  AccessTree(Name)->VarNum = Value;
}  /* End of 'SetValue' function */

DBL GetValue( CHAR *Name )
{
  return AccessTree(Name)->VarNum;
}  /* End of 'GetValue' function */

/* function to print tree */
VOID DisplayTree( VARTREE *T )
{
  if (T != NULL)
  {
    DisplayTree(T->Less);
    printf("[%s] = %lf\n", T->Name, T->VarNum);
    DisplayTree(T->More);
  }
}  /* End of 'DisplayTree' function */

/* function to print VarTable */
VOID DisplayVar( VOID )
{
  DisplayTree(VarTable);
} /* End of 'DisplayVar' function */

/* function to clear tree */
VOID ClearTree( VARTREE **T )
{
  if (T != NULL)
  {
    ClearTree(&(*T)->Less);

    /****************************************************************************
    *    NOTE:                                                                  *
    *       winuser.h - and macros                                              *
    *                                                                           *
    * Copyright (c) Microsoft Corporation. All rights reserved.                 *
    *                                                                           *
    ****************************************************************************/

    ClearTree (&(*T)->More);
    free(*T);
    *T = NULL;
  }
}  /* End of 'ClearTree' function */

/* function to clear VarTable */
VOID ClearVar( VOID )
{
  ClearTree(&VarTable);
}  /* End of 'ClearVar' function */

/* END OF 'VARS.C' FILE*/