/* Arsentev Artemy, 09-4, 06.12.2024 */

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

#include <commondf.h>

typedef struct tagLIST LIST;
struct tagLIST
{
  INT data;
  LIST *Next;
};

typedef struct tagSTACK STACK;
struct tagSTACK
{
  LIST *Top;
};

typedef struct tagQUEUE QUEUE;
struct tagQUEUE
{
  LIST
    *Tail,
    *Head;
};

/* Output of push function */
INT Push( STACK *A, INT NewEl );
/* Output of pop function */
INT Pop( STACK *A, INT *data );
/* Output of put function */
INT Put( QUEUE *A, INT NewEl);
/* Output of get function */
INT Get( QUEUE *A, INT *data );
/* Output of display function */
VOID DisplayStack( STACK *A );
VOID DisplayQueue( QUEUE *A );
/* Output of clear function */
VOID ClearQueue( QUEUE *Q );
VOID ClearStack( STACK *Q );
VOID ClearList( LIST *Q );
VOID GremlinTest( QUEUE Q, STACK S );

/* END OF 'QUST.H' FILE */