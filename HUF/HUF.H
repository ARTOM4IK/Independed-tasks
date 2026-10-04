/* Arsentev Artemy, 9-4, 25.11.2024 */

#ifndef __HUF_H_
#define __HUF_H_

/* Debug memory allocation support */
#ifdef _DEBUG
#  define _CRTDBG_MAP_ALLOC
#  include <crtdbg.h>
#  define SetDbgMemHooks() \
     _CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_CHECK_ALWAYS_DF | \
       _CRTDBG_ALLOC_MEM_DF | _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG))
#else /* _DEBUG */
#  define SetDbgMemHooks() ((VOID)0)
#endif /* _DEBUG */
#include <stdlib.h>

#include "commondf.h"
#include "BITRW.H"

/* frequency tree */
typedef struct tagTREE TREE;
struct tagTREE
{
  char Ch;   /* code of a symbol */
  long Freq; /* the frequency of its occurrence */
  TREE *Left, *Right;
};

/* code tree */
typedef struct
{
  int Code[47], Len;  /* take it with a margin */
} CODE;

typedef double DBL;

#define MAX_LEN 35
/* Output addon function */
VOID GetStr( CHAR *Str, INT MaxLen );
/* Output statistics function */
VOID Stat( CHAR *FileName );
/* Output compress function */
VOID Compress( CHAR *FileNameIn, CHAR *FileNameOut );
/* Output decompress function */
VOID Decompress( CHAR *FileNameIn, CHAR *FileNameOut );

#endif /* __HUF_H_ */

/* END OF 'HUF.H' FILE */