/* Arsentev Artemy, 9-4, 29.11.2024 */

#ifndef __FUR_H_
#define __FUR_H_

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

typedef struct tagTREE TREE;

#define MAX_LEN 102 /* max length of name */

/* session tree */
struct tagTREE
{
  CHAR Text[MAX_LEN];
  TREE *No, *Yes;
};

/* Output addon function */
VOID GetStr( CHAR *Str, INT MaxLen );
/* Output initialization tree function */
TREE *Init( CHAR *txt, TREE *l, TREE *r );
/* Output session function */
VOID Session( TREE **T );
/* Output save tree function */
VOID SaveTree( CHAR *FileName, TREE *T );
/* Output draw tree function */
VOID DrawTree( TREE *T );
/* Output load tree function */
VOID LoadTree( CHAR *FileName, TREE **T );

#endif /* __FUR_H_ */

/* END OF 'FUR.H' FILE */