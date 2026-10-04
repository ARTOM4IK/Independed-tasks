/* FILE NAME: t45detg.c
 * PROGRAMMER: AA4
 * DATE: 05.01.2025   
 * PURPOSE: Determinating Matrix using Gauss Method
*/

#include <stdio.h>
#include <math.h>
#include <commondf.h>

typedef double DBL;
#define MAX 10  /* Max amount of rows and cols */

/* Loads matrix into array .
 * ARGUMENTS:
 *   - Array:
 *       INT *mas;
 *   - Counter:
 *       INT n;
 * RETURNS:
 *   Nothing.
 */

VOID LoadMatrix( DBL mas[MAX][MAX], INT *n )
{
  FILE *F;
  INT i, j;

  if ((F = fopen("IN.txt", "r")) == NULL)
    return;

  fscanf(F, "%d", n);

  if (*n < 0)
    *n = 0;
  else if (*n > MAX)
    *n = MAX;

  for (i = 0; i < *n; i++)
    for (j = 0; j < *n; j++)
      fscanf(F, "%lf", &mas[i][j]);
  fclose(F);
} /* End of 'LoadMatrix' function */ 

/* Swap two numbers function.
 * ARGUMENTS:
 *   - First pointer to element of array:
 *       INT *a;
 *   - Second pointer to element of array:
 *       INT *b;
 * RETURNS:
 *   Nothing.
 */

VOID Swap( DBL *a, DBL *b )
{
  DBL tmp = *b;

  *b = *a;
  *a = tmp;
} /* End of 'Swap' function */

/* Count determinant of matrix using Gauss method function.
 * ARGUMENTS:
 *   - Array:
 *       INT *mas;
 *   - Counter:
 *       INT n;
 * RETURNS:
 *   Determinant.
 */

DBL Determinator( DBL mas[MAX][MAX], INT N )
{
  INT i, max_row, max_col, y, x, j, k;
  DBL coef, det = 1;

  for (i = 0; i < N; i++)
  {
    max_row = max_col = i;
    for (y = i; y < N; y++)
      for (x = i; x < N; x++)
        if (fabs(mas[y][x]) > fabs(mas[max_row][max_col]))
          max_col = x, max_row = y;
    if (mas[max_row][max_col] == 0)
    {
      det = 0;
      break;
    }

    /* Replace cols or rows if nessesary */

    if (max_row != i)
    {
      for (x = 0; x < N; x++)
        Swap(&mas[i][x], &mas[max_row][x]);
      det = -det;
    }
    if (max_col != i)
    {
      for (x = 0; x < N; x++)
        Swap(&mas[x][i], &mas[x][max_col]);
      det = -det;
    }

    /* Substracting */

    for (j = i + 1; j < N; j++)
    {
      coef = mas[j][i] / mas[i][i];
      mas[j][i] = 0;
      for (k = i + 1; k < N; k++)
        mas[j][k] -= mas[i][k] * coef;
    }

    det *= mas[i][i];
  }
  return det;
} /* End of 'Determinator' function */

VOID main( VOID )
{
  DBL mas[MAX][MAX]; /* Array for matrix */
  INT n;             /* Counter variable */

  DBL CGSGFOREVER = 30.0; /* Variable to enable type double */

  LoadMatrix(mas, &n);

  printf("%lf", Determinator(mas, n));

  getchar();
} /* End of 'main' function */

/* END OF 't45detg.c' FILE */
