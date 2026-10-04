/* Arsentev Artemy, 9-4, 29.11.2024 */

#include <stdio.h>
#include <string.h> 
#include <conio.h>

#include "FUR.H"

/* save string into variable function */
VOID GetStr( CHAR *Str, INT MaxLen )
{
  INT i = 0;
  CHAR ch;     
  
  while ((ch = getchar()) != '\n')
    if (i < MaxLen - 1 && Str != NULL)
      Str[i++] = ch;
  if (i < MaxLen && Str != NULL)
    Str[i] = 0;
}  /* end of 'GetStr' function */

/* initializating tree function */
TREE * Init( char *Text, TREE *N, TREE *Y )
{
  TREE *T = malloc(sizeof(TREE));

  if (T == NULL)
    return NULL;

  strncpy(T->Text, Text, MAX_LEN - 1);
  T->Yes = Y;
  T->No = N;

  return T;
}  /* end of 'Init' function */

/* session function */
VOID Session( TREE **T )
{
  CHAR Ans[MAX_LEN], /* answer for the question */
    Qst[MAX_LEN],    /* question */
    key;             /* key (yes or no) */
  
  if (*T == NULL)
    return;

  while (TRUE)  /* dialog loop */
  {
    printf("%s?\n", (*T)->Text);  /* questnion */
    key = _getch();               
    printf(key == 'Y' || key == 'y' ? " Yes\n" : " No\n"); /* yes or no */
    if ((*T)->Yes != NULL)
    {
      if (key == 'Y' || key == 'y')  /* if tree has leaf, continue */
        T = &(*T)->Yes;
      else
        T = &(*T)->No;
    }
    else
    {
      if (!(key == 'Y' || key == 'y'))  /* else create new leaf */
      {
        printf("then enter new definition: ");
        GetStr(Qst, MAX_LEN);           /* new question */
        printf("enter correct answer for definition: ");
        GetStr(Ans, MAX_LEN);           /* new answer */
        *T = Init(Qst, *T, Init(Ans, NULL, NULL)); /* record new leaf */
      }
      return;
    }
  } 
}  /* end of 'Session' function */

/* load tree from file function */
VOID LoadTreeRec( FILE *F, TREE **T )
{
  TREE Q;
  BOOL yes, no;

  if (fread(Q.Text, sizeof(CHAR), MAX_LEN, F) != MAX_LEN)
    return;
  *T = Init(Q.Text, NULL, NULL);
  no = fgetc(F);
  yes = fgetc(F);

  if (no)
    LoadTreeRec(F, &(*T)->No);
  if (yes)
    LoadTreeRec(F, &(*T)->Yes);
}  /* end of 'LoadTreeRec' function */

/* call load tree from file function */
VOID LoadTree( CHAR *FileName, TREE **T )
{
  FILE *F;

  if ((F = fopen(FileName, "rb")) == NULL)
    return;

  LoadTreeRec(F, T);

  fclose(F);
}  /* end of 'LoadTree' function */

/* draw tree function */
VOID DrawTree( TREE *T )
{
  static INT Level;

  Level++;
  if (T != NULL)
  {
    DrawTree(T->No);
    printf("%*c%s\n", Level * 3, ' ', T->Text);
    DrawTree(T->Yes);
  }
  Level--;
}  /* end of 'DrawTree' function */

/* save tree to file function */
VOID SaveTreeRec( FILE *F, TREE *T )
{
  if (T == NULL)
    return;
  fwrite(T->Text, sizeof(CHAR), MAX_LEN, F);
  fputc(T->No != NULL, F);
  fputc(T->Yes != NULL, F);
  SaveTreeRec(F, T->No);
  SaveTreeRec(F, T->Yes);
}  /* end of 'SaveTreeRec' function */

/* call save tree to file function */
VOID SaveTree( CHAR *FileName, TREE *T )
{
  FILE *F;
  if ((F = fopen(FileName, "wb")) == NULL)
    return;
  SaveTreeRec(F, T);
  fclose(F);
}  /* end of 'SaveTree' function */

/* END OF 'FUR.C' FILE */