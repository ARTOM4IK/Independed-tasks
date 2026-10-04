/* Arsentev Artemy, 09-4, 28.10.2024 */

#define MAX 30

typedef struct
{
  int Day, Month, Year;
} DATE;

typedef struct
{
  char Name[30], Surname[30];
  DATE Birthday;
  char Sex;
  int Hours[7];
} WORKER;

void ReadWorker( WORKER *W );
int SaveDB( char *FileName, WORKER *Base, int N );
void GetStr( char *Str, int MaxLen );
int LoadDB( char *FileName, WORKER *Base, int MaxSize );
void DeleteWorker( WORKER *DB, int DBSize);
void SaveWorkers( char *fname, WORKER *DB, int DBSize );
void OutWorker( WORKER *DB, int DBSize );
void ReverseWorkers( WORKER *DB, int DBSize );
void LoadWorkers( char *fname, WORKER *DB, int DBSize );
void ChangeData( WORKER *DB );
void Sort( WORKER *A, int N, int (*IsLess)( WORKER A, WORKER B ) );
int IsNameLess( WORKER A, WORKER B );
int IsDateLess( WORKER A, WORKER B );
void Report( FILE *F, WORKER *DB, int DBSize );