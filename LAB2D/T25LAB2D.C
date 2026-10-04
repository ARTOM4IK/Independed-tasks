/* Arsentev Artemy, 09-4, 06.11.2024 */

#include <stdio.h>

#include <stdlib.h>
#include <string.h>

#include "LAB2D.H"

void main( void )
{
  int i, a, b;
  char FileName[1000];

  PathLen = 0;
  BestPathLen = 0;
  memset(From, -1, sizeof(From));

  for (i = 0; i < MAX; i++)
    Len[i] = INFINITY;  

  printf("File name: ");
  GetStr(FileName, 1000);

  Lload(FileName);

  printf("A: ");
  scanf("%d", &a);
  printf("B: ");
  scanf("%d", &b);

  Len[b] = 0;
  Was[a] = 1;
  Path[PathLen++] = a;

  printf("BFS:\n");
  BFS(a, b);

  memset(Was, 0, sizeof(Was));
  memset(Adj, 0, sizeof(Adj));
  LabLoad(FileName);


  printf("GoAny:\n");

  GoAny(a, b);
  for (i = 0; i < PathLen; i++)
    printf("%d%s", Path[i], i == PathLen - 1 ? "\n" : ",");

  LabSet(a, b);

  printf("GoAll:\n");

  GoAll(a, b);
  LabSet(a, b);

  printf("GoBest:\n");

  GoBest(a, b);
  for (i = 0; i < PathLen; i++)
    printf("%d%s", BestPath[i], i == BestPathLen - 1 ? "\n" : ",");

  getchar();
  getchar();

}