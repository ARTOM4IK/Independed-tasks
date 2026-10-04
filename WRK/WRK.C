/* Arsentev Artemy, 09-4, 28.10.2024 */
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include "WRK.H"

/* utils */

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

void Swap ( WORKER *A, WORKER *B )
{
  WORKER tmp = *A;

  *A = *B;
  *B = tmp;
}

/* base */

int SaveDB( char *FileName, WORKER *Base, int N )
{
  FILE *F;
 
  if ((F = fopen(FileName, "wb")) == NULL)
    return 0;
  fwrite(Base, sizeof(WORKER), N, F);
  fclose(F);
  return 1;
}

int LoadDB( char *FileName, WORKER *Base, int MaxSize )
{
  FILE *F;
  int N;

  if ((F = fopen(FileName, "rb")) == NULL)
    return 0;
  N = fread(Base, sizeof(WORKER), MaxSize, F);
  fclose(F);
  return N;
}

/* funcs */

void ReadWorker( WORKER *W )
{
  printf("Name:");
  GetStr(W->Name, sizeof W->Name);
  
  printf("Surname:");
  GetStr(W->Surname, sizeof W->Surname);
  
  printf("Birthday:\nDay:");
  scanf("%i", &W->Birthday.Day);
  GetStr(NULL, 0);
  printf("Month:");
  scanf("%i", &W->Birthday.Month);
  GetStr(NULL, 0);
  printf("Year:");
  scanf("%i", &W->Birthday.Year);
  GetStr(NULL, 0);
  
  printf("Gender (m/f):");
  if (getchar() == 'm')
    W->Sex = 'm';
  else
    W->Sex = 'f';
  GetStr(NULL, 0);
}

void OutWorker( WORKER *DB, int DBSize )
{
  int i;

  for (i = 0; i < DBSize; i++)
    printf("\n%s %s %d.%d.%d %c", DB[i].Name, DB[i].Surname, DB[i].Birthday.Day, DB[i].Birthday.Month, DB[i].Birthday.Year, DB[i].Sex);
}

void SaveWorkers( char *fname, WORKER *DB, int DBSize )
{
  printf("Save file name:");
  GetStr(fname, sizeof(fname));
  if (SaveDB(fname, DB, DBSize))
    printf("Ok\n");
  else
    printf("Error\n");
}
void DeleteWorker( WORKER *DB, int DBSize)
{
  int i, k;

  printf("Worker to delete:");
  scanf("%d", &i);
  GetStr(NULL, 0);
  for (k = i; k < DBSize; k++)
    DB[k] = DB[k + 1];
  DBSize--;
}
int IsNameLess( WORKER A, WORKER B )
{
  int n = strcmp(A.Surname, B.Surname);

  if (n == 0)
    return strcmp(A.Name, B.Name) < 0;
  return n < 0;
}
 
int IsDateLess( WORKER A, WORKER B )
{
 
  if (A.Birthday.Year == B.Birthday.Year)
    if (A.Birthday.Month == B.Birthday.Month)
      return A.Birthday.Day < B.Birthday.Day;
    else
      return A.Birthday.Month < B.Birthday.Month;
  else
    return A.Birthday.Year < B.Birthday.Year;
}
 
void Sort( WORKER *A, int N, int (*IsLess)( WORKER A, WORKER B ) )
{
  int k, i;
  for (k = 0; k < N - 1; k++)
    for (i = 0; i < N - 1 - k; i++)
      if (IsLess(A[i], A[i + 1]))
        Swap(&A[i], &A[i + 1]);
}

void LoadWorkers( char *fname, WORKER *DB, int DBSize )
{
  printf("Load file name:");
  GetStr(fname, sizeof(fname));
  DBSize = LoadDB(fname, DB, MAX);
  DBSize += LoadDB(fname, DB + DBSize, MAX - DBSize);
  printf("Read %d records\n", DBSize);
}

void ReverseWorkers( WORKER *DB, int DBSize )
{
  int i;
  WORKER tmp;
  DBSize -= 1;
  for (i = 0; i < DBSize; i++, DBSize--)
  {
    tmp = DB[DBSize];
    DB[DBSize] = DB[i];
    DB[i] = tmp;
  }
}

void ChangeData( WORKER *DB )
{
  int i;

  printf("Number of worker: ");
  scanf("%d", &i);
  
  GetStr(NULL, 0);

  printf("Name:");
  GetStr(DB[i].Name, sizeof DB[i].Name);
  
  printf("Surname:");
  GetStr(DB[i].Surname, sizeof DB[i].Surname);
  
  printf("Birthday:\nDay:");
  scanf("%i", &DB[i].Birthday.Day);
  GetStr(NULL, 0);
  printf("Month:");
  scanf("%i", &DB[i].Birthday.Month);
  GetStr(NULL, 0);
  printf("Year:");
  scanf("%i", &DB[i].Birthday.Year);
  GetStr(NULL, 0);
  
  printf("Gender (m/f):");
  if (getchar() == 'm')
    DB[i].Sex = 'm';
  else
    DB[i].Sex = 'f';
  GetStr(NULL, 0);
}

void Report( FILE *F, WORKER *DB, int DBSize )
{
  int i, w, Cost, salary;

  char *WeekDays[] = {"Monday", "Tuesday", "Wednesday", "Thisday", "Friday", "Saturday", "Sunday"};

  printf("\nCost of hour: ");
  scanf("%d", &Cost);
  GetStr(NULL, 0);

  for (i = 0; i < DBSize; i++)
  {
    salary = 0;
    
    for (w = 0; w < 7; w++)
    {
      printf("\n%s: ", WeekDays[w]);
      scanf("%i", &DB[i].Hours[w]);
      GetStr(NULL, 0);
      salary += DB[i].Hours[w];
    }

    salary *= Cost;
    fprintf(F, "%i) %s %s: $%d\n", i, DB[i].Surname, DB[i].Name, salary);
  }
}