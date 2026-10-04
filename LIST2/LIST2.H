/* Arsetnev Artemy, AA4, 18.11.2024 */

#define STR_MAX 30

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

typedef struct tagLIST LIST;
struct tagLIST
{
  CHAR Str[STR_MAX];
  LIST *Next, *Prev;
};

VOID GetStr( CHAR *Str, INT MaxLen );
INT ListAddToFront( LIST **L, CHAR *NewStr );
VOID DisplayList( LIST *L );
INT ListDelToFront( LIST **L );
VOID ShiftNext( LIST **L );
VOID ShiftPrev( LIST **L );
INT ListAddToBack( LIST **L, CHAR *str );      
INT ListDelToBack( LIST **L );
VOID ListClear( LIST **L );
VOID GremlinTest( LIST *Start );