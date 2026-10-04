/* Arsentev Artemy, 09-4, 28.10.2024 */
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <conio.h>
#include "WRK.H"

void main( void )
{
  char option, fname[MAX];
  int DBSize = 0;
  static WORKER DB[MAX];

  printf("0 - exit\n"
    "1 - insert new worker\n"
    "2 - output all workers\n"
    "3 - delete worker\n"
    "a - sort workers by names\n"
    "b - sort workers by dates\n"
    "5 - base reverse\n"
    "6 - save base\n"
    "7 - import base\n"
    "8 - change data\n"
    "9 - insert wages\n");
  while(1)
  {
    switch (option = _getch())
    {
    case '0':
      return;
      break;
    case '1':
      if (DBSize < MAX)
        ReadWorker(&DB[DBSize++]);
      else
        printf("Not enough room\n");
      break;
    case '2':
      OutWorker(DB, DBSize);
      break;
    case '3':
        DeleteWorker(DB, DBSize);
      break;
    case 'a':
      Sort(DB, DBSize, IsNameLess);
      break;
    case 'b':
      Sort(DB, DBSize, IsDateLess);
      break;
    case '5':
      ReverseWorkers(DB, DBSize);
      break;
    case '6':
      {
        SaveWorkers(fname, DB, DBSize);
      }
      break;
    case '7':
      {
        LoadWorkers(fname, DB, DBSize);
      }
      break;
    case '8':
      ChangeData(DB);
      break;
    case '9':
      {
        FILE *F;
                        
        printf("\nReports file name:");
        GetStr(fname, sizeof(fname));
        
        if ((F = fopen(fname, "wb")) == NULL)
          printf("\nerror");
        else
        {
        Report(F, DB, DBSize);
        printf("\nok");
        }
        fclose(F);
      }
      break;
    }
  }
  getchar();
}