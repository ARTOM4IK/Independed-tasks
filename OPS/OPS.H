/* Arsentev Artrmy, 09-4, 16.12.2024 */

#ifndef __OPS_H_
#define __OPS_H_

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

#define TOK_OP_ADD_EQ 300
#define MAX_STR 300

typedef double DBL;

typedef enum
{
  KW_IF, KW_ELSE, KW_WHILE, KW_PRINT, KW_SCAN
} KEYWORDS;

typedef enum    /* token enum */
{
  TOK_OP,
  TOK_NUM,
  TOK_NAME,
  TOK_KEYW,
  TOK_SYMBOL       /* - for ';', '{', '}' */
} TOKID;

typedef enum
{
  OP_PLUS = '+',
  OP_MINUS = '-',
  OP_MULT = '*',
  OP_DIV = '/',
  OP_MOD = '%',
  OP_POW = '^',
  OP_LT = '<',                     /* less then */
  OP_GT = '>',                     /* Greater then */
  OP_EQ = '=' + TOK_OP_ADD_EQ,
  OP_NE = '!' + TOK_OP_ADD_EQ,
  OP_GE = '>' + TOK_OP_ADD_EQ,     /* greater or equal */
  OP_LE = '<' + TOK_OP_ADD_EQ,     /* less or equal */
  SYM_CMDEND = ';',
  SYM_RBEND = '}',
  SYM_LBEND = '{'
} OPERS;

typedef enum
{
  CMD_EXPR, CMD_IF, CMD_WHILE
} CMDID;
  
typedef struct
{
  TOKID Id;
  double Num;
  OPERS Op;
  char Name[MAX_STR];
  KEYWORDS KeyW;
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

typedef struct tagCMD CMD;
struct tagCMD
{
  CMDID Id;   /* command type */
  LIST *Expr; /* expression for CMD_EXPR, condotion for CMD_IF, CMD_WHILE */
  CMD
    *C1,      /* in CMD_IF 1-st command, command CMD_WHILE */
    *C2,      /* in CMD_IF 2-nd command, NULL if not 'else' */
    *Next;    /* pointer to next command */
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

extern QUEUE TokList;
extern TOK TokCurrent;
extern INT IsEOTL;  /* 1 to End of lexem (End-Of-Token-List) */
extern CMD *Proga;

  /* Transition to next lexem */
  #define NextTok() \
    (IsEOTL ?                                                      \
       Error("Unexpected End-of-data") :                           \
       Get(&TokList, &TokCurrent) ?  (void)0 : (void)(IsEOTL = 1))

/* Check current lexem */
#define IsTokAnyOp() \
  (!IsEOTL && TokCurrent.Id == TOK_OP)
#define IsTokAnySym() \
  (!IsEOTL && TokCurrent.Id == TOK_SYMBOL)
#define IsTokAnyNum() \
  (!IsEOTL && TokCurrent.Id == TOK_NUM)
#define IsTokAnyName() \
  (!IsEOTL && TokCurrent.Id == TOK_NAME)

#define IsTokOp(C) \
  (IsTokAnyOp() && TokCurrent.Op == (C))
#define IsTokSym(C) \
  (IsTokAnySym() && TokCurrent.Op == (C))
#define IsTokNum(C) \
  (IsTokAnyNum() && TokCurrent.oP == (C))
#define IsTokName(C) \
  (IsTokAnyName() && TokCurrent.Op == (C))

#define IsTokKw(Keyword) \
  (!IsEOTL && TokCurrent.Id == TOK_KEYW && TokCurrent.KeyW == KW_ ## Keyword)

/* disassemble lexem */
#define ParseAnyTok() \
  NextTok()
#define ParseAnyOp() \
  (IsTokAnyOp() ? NextTok() : Error("Expected any operator"))
#define ParseOp(C) \
  (IsTokOp(C) ? NextTok() : Error("Expected operator: %c", (C)))
#define ParseSym(C) \
  (IsTokSym(C) ? NextTok() : Error("Expected symbol: %c", (C)))
#define ParseNum(X) \
  (IsTokAnyNum() ? (*(X) = TokCurrent.Num, NextTok()) : Error("Expected number"))
#define ParseKw(Keyword) \
  (IsTokKw(Keyword) ? NextTok() : Error("Expected keyword: \"" #Keyword "\""))


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
/* Output of error function */
VOID Error( CHAR *Str, ... );
/* Output of var set function */
VOID SetValue( CHAR *Name, DBL Value );
/* Output of var output function */
DBL GetValue( CHAR *Name );
/* Output of vartable output function */
VOID DisplayVar( VOID );
/* Output of vartable clear function */
VOID ClearVar( VOID );
/* Output of parser function */
VOID ParserExpr( LIST **Q );
VOID CmdInit( CMD **C );
VOID ParseCmd( CMD **C );
INT ListAddToBack( LIST **L, TOK T );
VOID ParseProgram( VOID );
VOID DoCmd( CMD *C );

#endif /* __OPS_H_ */

/* END OF 'OPS.H' FILE*/