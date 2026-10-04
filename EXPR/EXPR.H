/* Arsentev Artemy, 09-4, 06.12.2024 */

#ifndef __EXPR_H_
#define __EXPR_H_

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

#include <setjmp.h>
#include <stdarg.h>

#define MAX 30  /* max length of string*/

typedef double DBL;

typedef enum    /* token enum */
{
  TOK_OP,
  TOK_NUM,
  TOK_NAME
} TOKID;

typedef struct  /* Token struct */
{
  TOKID Id;
  CHAR Op;
  DBL Num;
  CHAR Name[300];

} TOK;

typedef struct tagLIST LIST;
struct tagLIST  /* List struct */
{
  TOK T;
  LIST *Next;
};

typedef struct tagSTACK STACK;
struct tagSTACK /* stack struct */
{
  LIST *Top;
};

typedef struct tagQUEUE QUEUE;
struct tagQUEUE /* queue struct */
{
  LIST
    *Tail,
    *Head;
};

typedef struct tagVARTREE VARTREE;
struct tagVARTREE    /* Variable struct */
{
  CHAR Name[300];    /* name of a variable  */
  DBL VarNum;    /* value of a variable */
  VARTREE *Less; /* less variable value */
  VARTREE *More; /* more variable value */
} *VarTable;

extern jmp_buf JBuf;
extern jmp_buf ExprJumpBuf;

extern STACK Stack2;
extern QUEUE Queue1;

extern VARTREE *VarTable;

/* Output of addon function */
VOID GetStr( CHAR *Str, INT MaxLen );
/* Output of Put function */
VOID Put( QUEUE *A, TOK NewEl );
/* Output of Get function */
INT Get( QUEUE *A, TOK *data );
/* Output of Push function */
VOID Push( STACK *A, TOK NewEl );
/* Output of Pop function */
INT Pop( STACK *A, TOK *data );
/* Output of scanner function */
VOID Scanner( QUEUE *Q, CHAR *S );
/* Output of print queue function */
VOID DisplayQueue( QUEUE *A );
/* Output of clear queue function */
VOID ClearQueue( QUEUE *Q );
/* Output of clear stack function */
VOID ClearStack( STACK *Q );
/* Output of eval function */
DBL Eval ( QUEUE *Q );
/* Output of error function */
VOID Error( CHAR *Str, ... );
/* Output of parser function */
VOID ParserExpr( QUEUE *QRes, QUEUE *Q );
/* Output of var input function */
VOID SetValue( CHAR *Name, DBL Value );
/* Output of var output function */
DBL GetValue( CHAR *Name );
/* Output of vartable output function */
VOID DisplayVar( VOID );
/* Output of vartable clear function */
VOID ClearVar( VOID );

#endif /* __EXPR_H_ */

/* END OF 'EXPR.H' FILE */