/* Arsentev Artemy, 09-4, 27.10.2024 */
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "TXT.H"
#include <string.h>
#include <stdlib.h>
#include <ctype.h>


void GetStr( char *Str, int MaxLen )
{
  int i = 0;  
  char ch;   
  
  while ((ch = getchar()) != '\n')
    if (i < MaxLen - 1 && Str != NULL)
      Str[i++] = ch;
  if (i < MaxLen && Str != NULL)
    Str[i] = 0;
}


char *LoadText( char *FileName )
{
  char *s = NULL;
  FILE *F;
  int flen = 0, i = 0;
  int ch;

  if ((F = fopen(FileName, "r")) != NULL)
  {
    while (fgetc(F) != EOF)
      flen++;
    
    rewind(F);

    if ((s = malloc(flen + 1)) != NULL)
    {
      while ((ch = fgetc(F)) != EOF)
        s[i++] = ch;
      s[i] = 0;
    }
    fclose(F);
  }
  return s;
}

unsigned char Conv866( unsigned char Ch )
{
   if ((unsigned char)Ch >= 0x80 && (unsigned char)Ch <= 0xAF)
     Ch += 64;
   if ((unsigned char)Ch == 0xF0)
     Ch += 64;
   if ((unsigned char)Ch >= 0xE0 && (unsigned char)Ch <= 0xEF)
     Ch += 16;
   if ((unsigned char)Ch == 0xF1)
     Ch += 16;
  return Ch;
}

unsigned char Conv1251( unsigned char Ch )
{
  return Ch;
}

int CheckChar( unsigned char Ch, unsigned char *Fit )
{
  while (*Fit != 0)
    if (Ch == *Fit++)
      return 1;
  return 0;
}

void CountRussianLetters( char *Str, int *Counters )
{
  unsigned char *ptr = Str;
  int cnt866 = 0, cnt1251 = 0, i;
  unsigned char (*F)( unsigned char Ch );
  
  for (i = 0; i < 33; i++)
    Counters[i] = 0;

  i = 0;

  while (ptr[i] != 0)
  {
    if (CheckChar(ptr[i], "\xCE\xEE\xC5\xE5\xC0\xE0\xD2\xF2\xC8\xE8"))
      cnt1251++;
    if (CheckChar(ptr[i], "\x8E\xAE\x85\xA5\x80\xA0\x92\xE2\x88\xA8"))
      cnt866++;
    i++;
  }

  if (cnt866 > cnt1251)
    F = Conv866;
  else
    F = Conv1251;

  i = 0;

  while (Str[i] != 0)
  {
    if ((unsigned char)F(Str[i]) >= (unsigned char)'À' && (unsigned char)F(Str[i]) <= (unsigned char)'ß')
    {
      Counters[F(Str[i]) - 192]++;
    }
    else if ((unsigned char)F(Str[i]) >= (unsigned char)'à' && (unsigned char)F(Str[i]) <= (unsigned char)'ÿ')
    {
      Counters[(unsigned char)F(Str[i]) - 224]++;
    }

    i++;
  }
}

void GetLettersCounts( char *S, int *count )
{
  int i;
  
  for (i = 0; i < 26; i++)
    count[i] = 0;

  i = 0;

  while (S[i++] != 0)
  {
    if (isupper((unsigned char)S[i]))
      count[S[i] - 'A']++;
    else if (islower((unsigned char)S[i]))
      count[S[i] - 'à']++;
  }
}

int CntWord( char *S, int Start, int End )
{
  return 1;
}

int CntDigit( char *S, int Start, int End )
{
  int x = 0, i;

  for (i = Start; i <= End; i++)
    if (isdigit((unsigned char)S[i]))
      x = x * 10 + S[i] - '0';
  return x;
}

int CntSymWord( char *S, int Start, int End )
{
  while (Start < End)
    if (S[Start++] != S[End--])
      return 0;
  return 1;
}

int WordAnyCount( char *S, int (*F)( char *S, int Start, int End ) )
{
  char old = ' ';
  int i = 0, begin = 0, end = 0, cnt = 0;

  while (S[i++] != 0)
  {
    if (isspace((unsigned char)old) && !isspace((unsigned char)S[i]))
       begin = i;

    else if (!isspace((unsigned char)old) && isspace((unsigned char)S[i]))
    {
      end = i - 1;
      cnt += F(S, begin, end);
    }

    old = S[i];
  }

  return cnt;
}
