/*************************************************************
 * Copyright (C) 2025
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : t49lzw.cpp
 * PURPOSE     : LZW project.
 *               LZW module.
 * PROGRAMMER  : AA4.
 *               
 * LAST UPDATE : 23.09.2025.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#include "t49lzw.h"

/* Check if current get is EOF function.
 * ARGUMENTS: None.
 * RETURNS:
 *   (BOOL) result.
 */
BOOL rw::is_eof( VOID )
{
  if (f.get() != EOF)
  {
    f.unget();
    return TRUE;
  }
  else
    f.unget();
  return FALSE;
} /* End of 'is_eof' function */

/* Open file function.
 * ARGUMENTS:
 *   - Filename:
 *       const std::string &FileName;
 * RETURNS:
 *   (rw) Read/Write type.
 */
VOID rw::Open( const std::string &FileName, const type &Type)
{
  BitAccum = 0;
  BitPos = 0;
  if (Type == type::WRITE)
  {
    f = std::fstream(FileName, std::fstream::in | std::fstream::binary);
    out = std::fstream("out.txt", std::fstream::out | std::fstream::binary);
    WriteBitAccum = 0;
    WriteBitPos = 0;
  }
  else
  {
    f = std::fstream(FileName, std::fstream::in | std::fstream::binary);
    out = std::fstream("decompressed.txt", std::fstream::in | std::fstream::binary);
    WriteBitAccum = 0;
    WriteBitPos = 0;
    ReadBitAccum = 0;
    ReadBitPos = -1;
  }
} /* End of 'Open' function */

/* Close file function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID rw::Close( VOID )
{
  f.close();
  out.close();
} /* End of 'Close' function */

/* Close file function.
 * ARGUMENTS:
 *   - Bit:
 *       Bit;
 * RETURNS: None.
 */
VOID rw::WriteBit( INT Bit )
{
  WriteBitAccum |= Bit << WriteBitPos--; 
  if (WriteBitPos < 0)
  {
    out.put(WriteBitAccum);
    WriteBitAccum = 0;
    WriteBitPos = 0;
  }
} /* End of 'WriteBit' function */

/* Close file function.
 * ARGUMENTS:
 *   - Bit:
 *       Bit;
 *   - Count of bits:
 *       BitsCount;
 * RETURNS: None.
 */
VOID rw::WriteBits( INT Bit, INT BitsCount )
{
  INT Bits = 0, bit_pos = 0;
  while (BitsCount-- > 0)
  {
    INT Bit = (BitAccum >> BitPos++) & 1;
    Bits |= Bit << bit_pos++;
  }
  out.put(Bits);
} /* End of 'WriteBits' function */

/* close write bit function
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID rw::WriteBitClose( VOID )
{
  if (WriteBitPos < 7)
    out.put(WriteBitAccum);
}  /* end of 'WriteBitClose' function */

/* Read bit from file function.
 * ARGUMENTS: None
 *   (INT) result.
 */
INT rw::ReadBit( VOID )
{
  if (ReadBitPos < 0)
    ReadBitAccum = f.get(), ReadBitPos = 7;
  return (ReadBitAccum >> ReadBitPos--) & 1;
} /* End of 'ReadBit' function */

/* Read bits from file function.
 * ARGUMENTS:
 *   - Count of bits:
 *       BitsCount;
 * RETURNS:
 *   (INT) result.
 */
INT rw::ReadBits( INT BitsCount )
{
  //INT tmp = 0;

  //while (BitsCount > 0)
  //{
  //  if (ReadBitPos < 0)
  //    ReadBitAccum = f.get(), ReadBitPos = 7;
  //  tmp |= ((ReadBitAccum >> ReadBitPos--) & 1) << (BitsCount - 1);  
  //  BitsCount--;
  //}
  //return tmp;
  INT Bits = 0, bit_pos = 0;
  while (BitsCount-- > 0)
  {
    INT Bit = (BitAccum >> BitPos++) & 1;
    Bits |= Bit << bit_pos++;
  }
  return Bits;
} /* End of 'ReadBits' function */

/* Compress file function.
 * ARGUMENTS:
 *   - Filename:
 *       const std::string &FileName;
 * RETURNS: None.
 */
VOID Compress( const std::string &FileName )
{
  rw Dict(FileName);
  Dict.Open(FileName, type::WRITE);

  if (!Dict.f.is_open())
    return;

  INT Cur = Dict.f.get(), Next, Cnt = Dict.CODE_CLEAR;
  
  while (Dict.is_eof())
  {
    Next = Dict.f.get();
    if (auto it = Dict.DictMap.find({Cur, Next}); it != Dict.DictMap.end())
      Cur = Dict.DictMap[{Cur, Next}];
    else
    {
      //std::cout << CHAR(Cur);
      Dict.WriteBits(Cur, Dict.CodeSize);

      Dict.DictMap[{Cur, Next}] = Cnt++;
      Cur = Next;
    }
    if (Dict.DictMap.size() == (1 << Dict.CodeSize) && Dict.CodeSize < Dict.MAX_BITS)
      Dict.CodeSize++;
  }
  //std::cout << CHAR(Cur);
  Dict.WriteBits(Cur, 8);

  Dict.Close();
} /* End of 'Compress' function */

INT rw::Decode( VOID )
{
  BYTE stack[1 << MAX_BITS];
  INT stack_top = 0, code;

  code = ReadBits(8);
  while (code < 255)
  {
    //stack[stack_top++] = DictMap[code].s;
    //code = DictMap[code].p;
  }
  stack[stack_top++] = code;
  while (stack_top--)
    WriteBits(stack[stack_top], 8);
  return 30;  
} /* End of 'Decode' function */

/* Decompress file function.
 * ARGUMENTS:
 *   - Filename:
 *       const std::string &FileName;
 * RETURNS: None.
 */
VOID Decompress( const std::string &FileName )
{
  rw Dict(FileName);
  Dict.Open(FileName, type::READ);

  INT Cur = Dict.ReadBits(Dict.CodeSize), Next, code, Cnt = 0;

  while(Cur != Dict.CODE_CLEAR)
  {
    if (Cur == Dict.CODE_TERM)
      continue;
    std::cout << CHAR(Cur);
    while((Next = Dict.ReadBits(Dict.CodeSize)) != EOF && Next != Dict.CODE_TERM)
    {
      if (Next == Dict.CODE_CLEAR)
      {
        Dict.CodeSize = Dict.START_BITS + 1;
        Cur = Dict.ReadBits(Dict.CodeSize);
      }
      else
      {
        static BYTE DecodeStack[Dict.MAX_CODES];
        INT i = 0, Code = Next;
        
        if (Next == Dict.DictSize)
          i = 1, Code = Cur;
        while (Code >= Dict.CODE_CLEAR)
        {
          if (i < Dict.MAX_CODES)
            DecodeStack[i++] = Dict.Dict[Code].Suf;
          if (Dict.Dict[Code].Pref >= Code)
            break;
          Code = Dict.Dict[Code].Pref;
        }
        if (Next >= Dict.DictSize)
          DecodeStack[0] = DecodeStack[i - 1];
        while (i-- > 0)
          std::cout << CHAR(DecodeStack[i]);
        if (Dict.DictSize < Dict.MAX_CODES)
        {
          Dict.Dict[Dict.DictSize++] = {Cur, Code};
          if (Dict.DictSize == (1 << Dict.CodeSize) && Dict.CodeSize < Dict.MAX_BITS)
            Dict.CodeSize++;
        }
        Cur = Next;
      }
    }
  }
} /* End of 'Decompress' function */

/* END OF 't49lzw.cpp' FILE */                                 
    