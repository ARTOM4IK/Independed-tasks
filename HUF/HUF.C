/* Arsentev Artemy, 9-4, 25.11.2024 */

#include <stdio.h>
#include <string.h>

#include "HUF.H"

long Freq[256];   /* frequency of occurrence array */
TREE *Nodes[256]; /* tree array */
INT NumOfNodes;   /* its size */

CODE NewCodes[256], CurCode = {{0}, 0}; /* new codes array */

/* save string into variable function */
VOID GetStr( CHAR *Str, INT MaxLen )
{
  INT i = 0;
  CHAR ch;     
  
  while ((ch = getchar()) != '\n')
    if (i < MaxLen - 1 && Str != NULL)
      Str[i++] = ch;
  if (i < MaxLen && Str != NULL)
    Str[i] = 0;
} /* end of 'GetStr' function */

/* count frequency of occurrence function */
static VOID CountFreq( FILE *F )
{
  INT i;

  memset(Freq, 0, sizeof(long) * 256);  /* reset the frequencies */
  while ((i = fgetc(F)) != EOF)
    Freq[i]++;                          /* collecting information about frequencies */
}  /* end of 'CountFreq' function */

/* output statistics function */
static VOID PrintStat( VOID )
{
  INT i;

  for (i = 0; i < 256; i++)
    printf("%c(%d[%02X]) - %d\n", i < 32 ? '.' : i, i, i, Freq[i]);
}  /* end of 'PrintStat' function */

/* place node function */
static VOID PlaceNode( CHAR Ch, long Freq, TREE *L, TREE *R )
{
  INT i;
  
  TREE *T = malloc(sizeof(TREE));

  if (T == NULL)
    return;

  T->Ch = Ch;
  T->Freq = Freq;
  T->Left = L;
  T->Right = R;

    /* putting the node in the array in its place – one
    step of the insertion sorting algorithm */

  i = NumOfNodes - 1;

  while (i >= 0 && Nodes[i]->Freq < T->Freq)
    Nodes[i + 1] = Nodes[i], i--;

  Nodes[i + 1] = T;
  NumOfNodes++;
}  /* end of 'PlaceNode' function */

/* output tree function */
static VOID DrawTree( TREE *T )
{
  static INT Level;

  Level++;
  if (T != NULL)                                        
  {
    DrawTree(T->Right);
    printf("%*c [%c->%d]\n", Level * 3, ' ', T->Ch, T->Freq);
    DrawTree(T->Left);
  }
  Level--;
}  /* end of 'DrawTree' function */

/* build forest function */
static VOID BuildForest( VOID )
{
  INT i;

  NumOfNodes = 0;
  for (i = 0; i < 256; i++)                  
    if (Freq[i] > 0)
      PlaceNode(i, Freq[i], NULL, NULL);
}  /* end of 'BuildForest' function */

/* convolution of forest function */
static VOID ConvolutionForest( VOID )
{
  while (NumOfNodes > 1)
  {
    TREE                                       
      *Last = Nodes[--NumOfNodes],
      *PreLast = Nodes[--NumOfNodes];

    PlaceNode(' ', Last->Freq + PreLast->Freq, PreLast, Last);
  }
}  /* end of 'ConvolutionForest' function */

/* clear tree function */
static VOID ClearTree( TREE **T )
{
  if (*T != NULL)
  {
    ClearTree(&(*T)->Left);           
    ClearTree(&(*T)->Right);
    free(*T);
  } 
}  /* end of 'ClearTree' function */

/* build codes function */
static VOID BuildCodes( TREE *T )
{
  if (T->Left == NULL)
  {
    /* we came across NULL in Left and Right (we found a leaf with a symbol) */
    /* CurCode – character code T->Ch ---> */
    NewCodes[(BYTE)T->Ch] = CurCode;
    return;
  }
  /* CurCode.Code add 0 to the end, CurCode.Len++; */
  CurCode.Code[CurCode.Len++] = 0;
  BuildCodes(T->Left);
  /* CurCode.We remove the code from the end - CurCode.Len--; */
  CurCode.Len--;

  /* CurCode.Add Code to the end 1, CurCode.Len++; */
  CurCode.Code[CurCode.Len++] = 1;
  BuildCodes(T->Right);
  /* CurCode.We remove the code from the end - CurCode.Len--; */
  CurCode.Len--;
}  /* end of 'BuildCodes' function */

/* output codes function */
static INT OutCodes( VOID )
{
  INT i, j, total;
  DBL ratio;

  for (total = 0, i = 0; i < 256; i++)
    if (Freq[i] > 0)
    {
      printf("%c (%3d) [%02X] freq: %8ld :", i < 32 ? '.' : i, i, i, Freq[i]);
      for (j = 0; j < NewCodes[i].Len; j++)
        printf("%d", NewCodes[i].Code[j]);
      printf("\n");
      total += Freq[i] * NewCodes[i].Len;
    }

  ratio = Nodes[0]->Freq * 8.0 / total;
  printf("ratio = %lf\n", ratio);
  return ratio;
}  /* end of 'OutCodes' function */

/* statistics function */
VOID Stat( CHAR *FileName )
{
  FILE *F;

  F = fopen(FileName, "rb");
  if (F == NULL)
    return;

  CountFreq(F);              
  PrintStat();
  BuildForest();
  ConvolutionForest();
  DrawTree(Nodes[0]);


  memset(NewCodes, 0, sizeof NewCodes);
  CurCode.Len = 0;

  if (Nodes[0] != NULL)
    BuildCodes(Nodes[0]);
  OutCodes();

  ClearTree(&Nodes[0]);

  fclose(F);
}  /* end of 'Stat' function */

/* compress file function */
VOID Compress( CHAR *FileNameIn, CHAR *FileNameOut )
{
  FILE *InF, *OutF;
  CHAR ch;
  INT i;

  if ((InF = fopen(FileNameIn, "rb")) == NULL)
    return;
  if ((OutF = fopen(FileNameOut, "wb")) == NULL)
  {
    fclose(InF);
    return;
  }

  CountFreq(InF);
  BuildForest();  /* building a Huffman tree */
  ConvolutionForest();

  BuildCodes(Nodes[0]);  /* building a codes tree */
  OutCodes();

  fwrite(Freq, 4, 256, OutF);
  rewind(InF);

  WriteBitInit(OutF);

  while ((ch = fgetc(InF)) != EOF)
  {
    for (i = 0; i < NewCodes[ch].Len; i++)
      WriteBit(NewCodes[ch].Code[i]);  /* fill file with codes */
  }

  WriteBitClose();
  ClearTree(&Nodes[0]);

  fclose(InF);
  fclose(OutF);
}  /* end of 'Compress' function */

/* decompress file function */
VOID Decompress( CHAR *FileNameIn, CHAR *FileNameOut )
{
  FILE *InF, *OutF;
  TREE *T;
  INT n;

  if ((InF = fopen(FileNameIn, "rb")) == NULL)
    return;
  if ((OutF = fopen(FileNameOut, "wb")) == NULL)
  {
    fclose(InF);
    return;
  }

  fread(Freq, 4, 256, InF);  /* loading the frequency array */

  BuildForest();  /* building a Huffman tree */
  ConvolutionForest();
  
  ReadBitInit(InF);  /* initializing bit reading */

  n = Nodes[0]->Freq;  /* number of characters per record */
  T = Nodes[0];  /* initially at the root of the tree */

  while (n > 0)
  {
    if (T->Left == NULL)  /* stumbled upon a leaf */
    {
      fputc(T->Ch, OutF);  /* char from node to file */
      n--;
      T = Nodes[0];  /* to the root of the tree for the next decoding */
    }
    else if (ReadBit() == 1)
      T = T->Right;
    else
      T = T->Left;
  }

  ClearTree(&Nodes[0]);

  fclose(InF);
  fclose(OutF);
}  /* end of 'Decompress' function */

/* END OF 'HUF.C' FILE */