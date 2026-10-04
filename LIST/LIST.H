/* Arsetnev Artemy, AA4, CGSG */

#define MAX_STR 30

#include "commondf.h"

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

typedef struct tagLIST LIST;

struct tagLIST
{
  CHAR Name[MAX_STR];
  INT D, M, Y;
  LIST *Next;
};

VOID GetStr( CHAR *Str, INT MaxLen );
INT ListAddToFront( LIST **L, CHAR *Name, INT D, INT M, INT Y );
INT ListDelFromFront( LIST **L, CHAR *Name, INT *D, INT *M, INT *Y );
VOID ListDisplay( LIST *L );
INT ListDelFromBack( LIST **L, CHAR *Name, INT *D, INT *M, INT *Y );
INT ListAddFromBack( LIST **L, CHAR *Name, INT D, INT M, INT Y );
INT ListAddLoc( LIST **L, INT pos, CHAR *Name, INT D, INT M, INT Y );
INT ListDelLoc( LIST **L, INT pos, CHAR *Name, INT *D, INT *M, INT *Y );