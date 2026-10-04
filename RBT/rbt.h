/*************************************************************
 * Copyright (C) 2025
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : rbt.h
 * PURPOSE     : Binary Search Tree project.
 *               Main tree type declaration module.
 * PROGRAMMER  : CGSG-SummerCamp'2025.
 *               Artemy V. Arsentev.
 * LAST UPDATE : 19.07.2025.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */
 
#ifndef __rbt_h_
#define __rbt_h_
 
#include <iostream>
#include <commondf.h>

typedef double DBL;
#define MAX 10000

/* Binary search tree representation type */
struct rbtree
{
  enum rbcolors
  {
    eRED, eBLACK
  };
  /* RbTree node representation type */
  struct node
  {
    INT Key;                 // Search key value
    std::string Data;        // Search data value
    node *Less, *More, *Parent;       // Subtree pointers
    rbcolors Color;          // Node color
    DBL X, Y, DestX, DestY;  // Coordinates
    /* Type constructor.
     * ARGUMENTS:
     *   - new key value:
     *       INT NewKey;
     *   - new subtree pointers:
     *       node *NewLess, *NewMore;
     */
     node( INT NewKey, std::string NewData = "", node *NewParent = nullptr, DBL NewX = 0, DBL NewY = 0, DBL NewDestX = 0, DBL NewDestY = 0, rbcolors NewColor = eRED, node *NewLess = nullptr, node *NewMore = nullptr ) :
       Key(NewKey), Data(NewData), Parent(NewParent), Color(NewColor), X(NewX), Y(NewY), DestX(NewDestX), DestY(NewDestY), Less(NewLess), More(NewMore)
     {
     } /* End of 'node' function */
 
     ~node( VOID )
     {
       delete Less;
       delete More;
     }
  }; /* End of 'node' structure */
 
  // Tree root pointer value
  node *Root {};
 
  /* Type destructor */
  ~rbtree( VOID )
  {
    Clear(&Root);
  } /* End of '~rbtree' function */
 
  /* Clear all tree nodes function.
   * ARGUMENTS:
   *   - address of tree node pointer to be deleted:
   *       node **T;
   * RETURNS: None.
   */
  VOID Clear( node **T = nullptr )
  {
    if (T == nullptr)
      T = &Root;
    if (*T == nullptr)
      return;
    Clear(&(*T)->Less);
    Clear(&(*T)->More);
    delete *T;
    *T = nullptr;
  } /* End of 'Clear' function */
 
  /* Output all tree nodes function.
   * ARGUMENTS: None.
   * RETURNS: None.
   */
  VOID Put( VOID )
  {
    Put(Root);
    std::cout << std::endl;
  } /* End of 'Put' function */
 
  /* Output tree node with subtrees function.
   * ARGUMENTS:
   *   - tree node pointer:
   *       node *T;
   * RETURNS: None.
   */
  VOID Put( node *T )
  {
    if (T == nullptr)
      std::cout << " * ";
    else
    {
      Put(T->Less);
      std::cout << T->Key;
      Put(T->More);
    }
  } /* End of 'Put' function */
 
  /* Access BST function.
   * ARGUMENTS:
   *   - search key value:
   *       INT Key;
   * RETURNS: None.
   */
  VOID Access( INT Key, std::string Data)
  {
    node **T = &Root;
 
    while (*T != nullptr && (*T)->Key != Key)
      T = (*T)->Key < Key ? &(*T)->More : &(*T)->Less;
    if (*T == nullptr)
      *T = new node(Key, Data);
  } /* End of 'Access' function */

  /* Recalc rbtree visualisation function.
   * ARGUMENTS:
   *   - tree node pointer:
   *       node *T;
   *   - node coordinate pointers:
   *       DBL *X, DBL *Y;
   * RETURNS: None.
   */
  VOID Recalc( node *T, DBL *X )
   {
    static INT n = 0;
    static DBL levels[MAX] { 0 };
    DBL xl, xr;
    DBL rowshift = 152, Hshift = 40;
    DBL xx, yy;

    if (T == nullptr)
      return;
    if (n >= MAX)
      return;

    xx = *X; 
    yy = n * rowshift;

    n++;
    xl = xx - Hshift;
    Recalc(T->Less, &xl);
    xr = xx + Hshift;
    Recalc(T->More, &xr);
    n--;

    if (T->Less != nullptr && T->More != nullptr)
      xx = (xr + xl) / 2;
    else if (T->Less != nullptr && T->More == nullptr)
      xx = xl - Hshift;
    else if (T->Less == nullptr && T->More != nullptr)
      xx = xr + Hshift;

    if (xx < levels[n])
      xx = levels[n] + Hshift + (T->Data.size() * 5);

    levels[n] = xx + Hshift + (T->Data.size() * 5);

    *X = xx;
    T->DestX = xx;
    T->DestY = yy;

    if (n <= 0)
      memset(levels, 0, MAX);
  } /* End of 'Recalc' function */

  /* Draw tree function.
   * ARGUMENTS:
   *   - tree node pointer:
   *       node *T;
   * RETURNS: None.
   */
  VOID Draw( HDC hDC, HFONT hFnt, node *T, DBL StartX, DBL StartY )
  {
    static char buf[MAX];

    if (T == nullptr)
      return;

    SelectObject(hDC, GetStockObject(DC_PEN));
    SetDCPenColor(hDC, RGB(0, 150, 150));

    SelectObject(hDC, GetStockObject(DC_BRUSH));

    SelectObject(hDC, hFnt);
    SetTextColor(hDC, RGB(255, 255, 255));
    SetBkColor(hDC, RGB(0, 255, 0));
    SetBkMode(hDC, TRANSPARENT);

    Draw(hDC, hFnt, T->Less, StartX, StartY);
    if (T->Less != nullptr)
    {
      MoveToEx(hDC, StartX + T->X, StartY + T->Y, nullptr);
      LineTo(hDC, StartX + T->Less->X, StartY + T->Less->Y);
    }
    if (T->More != nullptr)
    {
      MoveToEx(hDC, StartX + T->X, StartY + T->Y, nullptr);
      LineTo(hDC, StartX + T->More->X, StartY + T->More->Y);
    }
    if (T->Color == eBLACK)
      SetDCBrushColor(hDC, RGB(0, 0, 0));
    else
      SetDCBrushColor(hDC, RGB(255, 0, 0));
    RoundRect(hDC, StartX + T->X - (T->Data.size() * 5), StartY + T->Y - 10, StartX + T->X + (T->Data.size() * 5), StartY + T->Y + 10,5, 5);

    TextOut(hDC, StartX + T->X - (T->Data.size() * 5) + 2, StartY + T->Y - 5, T->Data.c_str(), T->Data.size());

    T->X += (T->DestX - T->X) * 0.030;
    T->Y += (T->DestY - T->Y) * 0.030;
    Draw(hDC, hFnt, T->More,StartX, StartY);
  } /* End of 'Draw' function */                                                                  

  /* Insert in RB tree a new node function.
   * ARGUMENTS:
   *   - new node key:
   *       INT key;
   *   - new node data:
   *       std::string Data;
   * RETURNS: None.
   */
  VOID Insert( INT Key, std::string Data )
  {
    node **T = &Root;
    node *OldT = nullptr;

    if (*T == nullptr)
    {
      *T = new node(Key, Data);
      return;
    }
    while (*T != nullptr && (*T)->Key != Key)
    {
      if ((*T)->Key < Key && (*T)->More != nullptr)
      {
        T = &(*T)->More;
      }
      else if ((*T)->Key > Key && (*T)->Less != nullptr)
      {
        T = &(*T)->Less;
      }
      if ((*T)->Key < Key && (*T)->More == nullptr)
      {
        (*T)->More = new node(Key, Data);
        (*T)->More->Parent = *T;
        T = &(*T)->More;
      }
      else if ((*T)->Key > Key && (*T)->Less == nullptr)
      {
        (*T)->Less = new node(Key, Data);
        (*T)->Less->Parent = *T;      
        T = &(*T)->Less;
      }
    }
  } /* End of 'Insert' function */

  /* Insert in RB tree a new node function.
   * ARGUMENTS:
   *   - new node key:
   *       INT key;
   *   - new node data:
   *       std::string Data;
   * RETURNS: None.
   */
  VOID Insert1( INT Key, std::string Data )
  {
    node **T = &Root;
    node *OldT = nullptr;

   while (*T != nullptr && (*T)->Key != Key)
   {
     OldT = *T;
      T = (*T)->Key < Key ? &(*T)->More : &(*T)->Less;
   }
    if (*T == nullptr)
      *T = new node(Key, Data, OldT);
    InsertCorrection(*T);
   } /* End of 'Insert1' function */

  /* Identify if node is black or not function.
   * ARGUMENTS:
   *   - node pointer:
   *       node *n;
   * RETURNS: None.
   */
  BOOL Is_BLACK( node *n )
  {
    if (n == nullptr || n->Color == eBLACK)
      return TRUE;
    return FALSE;
  } /* End of 'Is_BLACK' function */

  /* Identify if node is red or not function.
   * ARGUMENTS:
   *   - node pointer:
   *       node *n;
   * RETURNS: None.
   */
  BOOL Is_RED( node *n )
  {
    if (n == nullptr)
      return FALSE;
    if (n->Color == eRED)
      return TRUE;
    return FALSE;
  } /* End of 'Is_RED' function */

  /* Correct Insert in RB tree function.
   * ARGUMENTS:
   *   - node pointer:
   *       node *n;
   * RETURNS: None.
   */
  VOID InsertCorrection( node *n )
  {
    if (Root == n)
    {
      Root->Color = eBLACK;
      return;
    }
    if (Is_RED(n) && Is_RED(n->Parent) && Is_RED(n->Parent->Parent->Less) && (n->Parent->Parent != nullptr) && (n->Parent->Parent->Less != n->Parent))
    {
      n->Parent->Color = eBLACK;
      n->Parent->Parent->Color = eRED;
      n->Parent->Parent->Less->Color = eBLACK;
      Root->Color = eBLACK;
      InsertCorrection(n);
      InsertCorrection(n->Parent->Parent);
    }
    else if (Is_RED(n) && Is_RED(n->Parent) && Is_RED(n->Parent->Parent->More) && (n->Parent->Parent->More != nullptr) && (n->Parent->Parent->More != n->Parent))
    {
      n->Parent->Color = eBLACK;
      n->Parent->Parent->Color = eRED;
      n->Parent->Parent->More->Color = eBLACK;
      Root->Color = eBLACK;
      InsertCorrection(n);
      InsertCorrection(n->Parent->Parent);
    }
    else if (Is_RED(n) && Is_RED(n->Parent) && Is_BLACK(n->Parent->Parent->Less) && Is_RED(n->Parent->Parent->More) && n == n->Parent->Less)
    {
      RotateRight(n);
      n->Parent->Color = eBLACK;
      n->Parent->Parent->Color = eRED;
      RotateLeft(n);
      InsertCorrection(n);
    }
    else if (Is_RED(n) && Is_RED(n->Parent) && Is_BLACK(n->Parent->Parent) && Is_BLACK(n->Parent->Parent->More) && Is_RED(n->Parent->Parent->Less) && n == n->Parent->More)
    {
      RotateLeft(n);
      n->Parent->Color = eBLACK;
      n->Parent->Parent->Color = eRED;
      RotateRight(n);
      InsertCorrection(n);
    }
    else if (Is_RED(n) && Is_RED(n->Parent) && Is_BLACK(n->Parent->Parent->More))
    {
      n->Parent->Color = eBLACK;
      n->Parent->Parent->Color = eRED;
      RotateRight(n->Parent);
      InsertCorrection(n);
    }
    else if (Is_RED(n) && Is_RED(n->Parent) && Is_BLACK(n->Parent->Parent->Less))
    {
      n->Parent->Color = eBLACK;
      n->Parent->Parent->Color = eRED;
      RotateLeft(n->Parent);
      InsertCorrection(n);
    }
    Root->Color = eBLACK;
  } /* End of 'InsertCorrection' function */

  /* Rotate node to right (clock wise) function.
   * ARGUMENTS:
   * - node to be rotated:
   * node *n;
   * RETURNS: None.
   */
  VOID RotateRight( node *n )                       
  {
    node *tmp = n->Parent->Parent;

    if (n->More != nullptr)
      n->Parent->Less = n->More;
    else
      n->Parent->Less = nullptr;
    n->More = n->Parent;

    n->Parent->Parent = n;
    if (tmp != nullptr)
    {
      if (tmp->Key > n->Key)
        tmp->Less = n;
      else
        tmp->More = n;
      n->Parent = tmp;
    }
    else
    {
      Root->Color = eRED;
      Root = n;
      n->Parent = tmp;
    }
  } /* End of 'RotateRight' function */

  /* Rotate node to left (counter clock wise) function.
   * ARGUMENTS:
   * - node to be rotated:
   * node *n;
   * RETURNS: None.
   */
  VOID RotateLeft( node *n )
  {
    node *tmp = n->Parent->Parent;

    if (n->Less != nullptr)
      n->Parent->More = n->Less;
    else
      n->Parent->More = nullptr;
    n->Less = n->Parent;

     n->Parent->Parent = n;
    if (tmp != nullptr)
    {
      if (tmp->Key > n->Key)
        tmp->Less = n;
      else
        tmp->More = n;
      n->Parent = tmp;
    }
    else
    {
      Root->Color = eRED;
      Root = n;
      n->Parent = tmp;
    }
  } /* End of 'RotateLeft' function */
}; /* End of 'rbtree' structure */
 
#endif /* __rbt_h_ */
 
/* END OF 'rbt.h' FILE */