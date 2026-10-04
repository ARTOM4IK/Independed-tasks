/* Arsentev Artemy, 09-4, 27.10.2024 */
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "TXT.H"


void main( void )
{
  char *txt, fn[200];
  int c, count[26], Rcount[34];

  setlocale(LC_ALL, "Russian");


   printf("File name: ");
  GetStr(fn, sizeof(fn));

  LoadText(fn);
 
  if((txt = LoadText(fn)) == NULL)
    return;

  GetLettersCounts(txt, count);

  for (c = 0; c < 26; c++)
    if (count[c] != 0)
      printf("%c occured %d times\n", c + 'A', count[c]);
 
  printf("Number of words: %d\n", WordAnyCount(txt, CntWord));
  printf("Sum of numbers in words: %d\n", WordAnyCount(txt, CntDigit));
  printf("Sum of symmetrical words: %d\n", WordAnyCount(txt, CntSymWord));


  CountRussianLetters(txt, Rcount);

  for (c = 0; c < 33; c++)
    if (Rcount[c] != 0)
      printf("%c occured %d times\n", c + 'À', Rcount[c]);

  free(txt);

  getchar();
}