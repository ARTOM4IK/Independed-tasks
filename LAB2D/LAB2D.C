/*a Arsentev Artemy, 09-4, 06.11.2024 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "LAB2D.H"

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

void LabLoad( char *Filename )
{
  FILE *F;
  int a, b;

  if ((F = fopen(Filename, "r")) != NULL)
  {
    while (fscanf(F, "%d%d", &a, &b) == 2)
    {
      if (a <= MAX && a >= 1 && b >= 1 && b <= MAX)
        Adj[a][b] = 1, Adj[b][a] = 1;
    }
  fclose(F);
  }
}

void LabSet( int a, int b )
{
  PathLen = 0;
  memset(Was, 0, sizeof(Was));
  memset(Was, 0, sizeof(Path));
  Was[a] = 1;
  Path[PathLen++] = a;

}

int GoAny( int a, int b )
{
  int i;

  if (Adj[a][b] == 1)
  {
    Path[PathLen++] = b;
    return 1;
  }
  for (i = 0; i < MAX; i++)
    if (i != a && i != b && Was[i] == 0 && Adj[a][i] != 0)
    {
      Was[i] = 1;
      Path[PathLen++] = i;
      if (GoAny(i, b))
        return 1;
      PathLen--;
    }
  return 0;
}

int GoAll( int a, int b )
{
  int i;

  if (Adj[a][b] == 1 || Adj[a][b] == 1)
  {
    Path[PathLen++] = b;
    for (i = 0; i < PathLen; i++)
          printf("%d%s", Path[i], i == PathLen - 1 ? "\n" : ",");
    PathLen--;
  }
  for (i = 0; i < MAX; i++)
    if (i != a && i != b && Was[i] == 0 && Adj[a][i] != 0)
    {
      Was[i] = 1;
      Path[PathLen++] = i;
      if (GoAll(i, b))
        for (i = 0; i < PathLen; i++)
          printf("%d%s", Path[i], i == PathLen - 1 ? "\n" : ",");
      PathLen--;
      Was[i] = 0;
    }
    return 0;
}


int GoBest( int a, int b )
{
  int i;

  if (Adj[a][b] == 1)
  {

    Path[PathLen++] = b;

    if (BestPathLen == 0 || PathLen < BestPathLen)
    {
      BestPathLen = PathLen;
      memcpy(BestPath, Path, sizeof(int) * PathLen);
      return 1;
    }
    return 0;
  }
  else
  {
    for (i = 0; i < MAX; i++)
      if (i != a && i != b && Was[i] == 0 && Adj[a][i] != 0)
      {
        Was[i] = 1;
        Path[PathLen++] = i;
        GoBest(i, b);
        PathLen--;
        Was[i] = 0;
      }
    return 0;
  }
}

void Lload( char *Filename )
{
  int i, j, n, a, b, len;
  static char Buf[1000];

  FILE *F;

  for (i = 0; i < MAX; i++)
    for (j = 0; j < MAX; j++)
      Adj[i][j] = INFINITY;

  if ((F = fopen(Filename, "r")) != NULL)
  {
    while (fgets(Buf, sizeof(Buf) - 1, F) != NULL)
    {
      n = sscanf(Buf, "%d%d%d", &a, &b, &len);
      if (n == 2)
        len = 1;
      if (n > 1)
        Adj[a][b] = Adj[b][a] = len;
    }

    fclose(F);
  }
}

void BFS( int a, int b )
{
  int i, j, Flag;
  
  do
  {
    Flag = 0;
    for (i = 0; i < MAX; i++)
    {
      NewLen[i] = Len[i];
      for (j = 0; j < MAX; j++)
        if (i != j && Len[i] > NewLen[j] + Adj[i][j])
        {
          NewLen[i] = Len[j] + Adj[i][j];
          From[i] = j;
          Flag = 1;
        }
    }
    if (Flag)
      memcpy(Len, NewLen, sizeof(Len));
  } while (Flag);


  if (From[a] == -1)
    printf("nothing\n");
  else
  {
    do
    {
      printf("%i ", a);
      a = From[a];
    } while (a != -1);
    printf("\n");
  }
}