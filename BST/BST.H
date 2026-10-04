/* Arsetnev Artemy, 9-4, 22.11.2024 */

#ifndef __BST_H_
#define __BST_H_

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

struct tagTREE
{
  TREE *Less, *More;
  INT Key;
};
/* Output access tree functions */
INT AccessTree( TREE **T, INT Key );
INT AccessTree1( TREE **T, INT Key );
/* Output functions of outputting tree */
VOID DrawTree( TREE *T );
VOID DrawTree1( TREE *T, INT Level );
VOID PutTreeSorted( TREE *T );
VOID PutTree( TREE *T );
/* Output clear tree function */
VOID ClearTree( TREE **T );
/* Output balance tree functions */
INT Linearize( TREE **T );
VOID BalanceTree( TREE **T, INT N );
/* Output deleting key in the tree function */
VOID DeleteKey( TREE **T, INT POS );

#endif /* __BST_H_ */

/* END OF 'BST.H' FILE */