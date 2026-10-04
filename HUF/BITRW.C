/* Arsentev Artemy, 9-4, 25.11.2024 */

#include <stdio.h>

#include "BITRW.H"

static FILE *BitF;           /* variable to work with files */
static INT BitAccum, BitPos; /* byte accumulator and bit position */

/* initialization of write bit function */
VOID WriteBitInit( FILE *F )
{
  BitF = F;
  BitAccum = 0;
  BitPos = 7;
}  /* end of 'WriteBitInit' function */

/* write bit function */
VOID WriteBit( INT Bit )
{
  BitAccum |= Bit << BitPos--; 
  if (BitPos < 0)
  {
    fputc(BitAccum, BitF);
    BitAccum = 0;
    BitPos = 7;
  }
}  /* end of 'WriteBit' function */

/* close write bit function */
VOID WriteBitClose( VOID )
{
  if (BitPos < 7)
    fputc(BitAccum, BitF);
}  /* end of 'WriteBitClose' function */

/* initialization of read bit function */
VOID ReadBitInit( FILE *F )
{
  BitF = F;
  BitPos = -1;
}  /* end of 'ReadBitInit' function */

/* read bit function */
INT ReadBit( VOID )
{
  if (BitPos < 0)
    BitAccum = fgetc(BitF), BitPos = 7;
  return (BitAccum >> BitPos--) & 1;
}  /* end of 'ReadBit' function */

/* END OF 'BITRW.C' FILE */