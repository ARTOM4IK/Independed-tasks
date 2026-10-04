/* Arsentev Artrmy, 09-4, 16.12.2024 */

#include <stdio.h>

#include <string.h>
#include <ctype.h>

#include "OPS.H"

VOID UpdateKeyword( TOK *T )
{
  INT i;

  struct
  {
    CHAR *Name;  /* keyword string value */
    KEYWORDS KeyW; /* keyword constant value */
  } Kws[] =
  {
    {"if", KW_IF},
    {"else", KW_ELSE},
    {"while", KW_WHILE},
    {"print", KW_PRINT},
    {"scan", KW_SCAN}
  };
 
  for (i = 0; i < sizeof(Kws) / sizeof(Kws[0]); i++)
    if (strcmp(Kws[i].Name, T->Name) == 0)
    {
      T->Id = TOK_KEYW;
      T->KeyW = Kws[i].KeyW; 
      return;
    }
}

/* function for scanning inputed string */
VOID Scanner( QUEUE *Q, CHAR *S )
{
  TOK T = {0};

  /* go through all symbols */
  while (*S != 10 && *S != 0)
  {
    while (isspace(*S))
      S++;
    if (*S == '+' || *S == '-' || *S ==  '/' || *S == '*' || *S == '(' || *S == ')' || *S == '^' || *S == '%' || *S == '=' || *S == ',' || *S == '>' || *S == '<')
    {
      T.Id = TOK_OP;
      T.Op = *S++;

    if (*S == '=' && (T.Op == '<' || T.Op == '>' || T.Op == '!' || T.Op == '='))
      T.Op += TOK_OP_ADD_EQ, S++;
    }
    else if (isdigit((UCHAR)*S))
    {
      /* DBL */
      T.Id = TOK_NUM;
      T.Num = 0;
      /* integer */
      while (isdigit(*S))
        T.Num = T.Num * 10 + *S++ - '0';
      /* DBL part */
      if (*S == '.')
      {
        DBL denum = 1;
        S++; /* go from point to digit */
        while (isdigit((UCHAR)*S))
          T.Num += (*S++ - '0') / (denum *= 10);
      }
    }
    else if (isalpha((UCHAR)*S))
    {
      int i = 0;
      /* VAR */
      T.Id = TOK_NAME;
      memset(T.Name, 0, MAX_STR);
      while (islower((UCHAR)*S) || isupper((UCHAR)*S))
        T.Name[i++] = (UCHAR)*S++;
      UpdateKeyword(&T);
    }
    else if (*S == ';' || *S == '{' || *S == '}')
    {
      T.Id = TOK_SYMBOL;
      T.Op = *S++;
    }
    else
        Error("Unrecognized character '%c'\n", *S);
    /* adds lexem into queue */
    Put(Q, T);
  }
}

/* END OF 'SCANNER.C' FILE*/