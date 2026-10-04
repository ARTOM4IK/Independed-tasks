/*************************************************************
 * Copyright (C) 2025
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : t49lzw.h
 * PURPOSE     : LZW project.
 *               Header module.
 * PROGRAMMER  : AA4.
 *               
 * LAST UPDATE : 23.09.2025.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __t49lzw_h_
#define __t49lzw_h_

#include <cassert>
 
#ifndef WIN32
#define WIN32
#include <commondf.h>
#undef WIN32
#else
#include <commondf.h>
#endif /* WIN32 */
#define BOOL bool
#include <string>
#include <vector>
#include <fstream>
#include <exception>
#include <map> 
#include <wincodec.h>  
#include <functional>
 
#include <iostream>
#include <format>

enum struct type
{
  READ,
  WRITE
};

/* Read/Write class */
class rw
{
  private:
  public:

    std::map<std::pair<INT, INT>, INT> DictMap;
    std::fstream f, out;
    type Type;

    static const INT START_BITS = 8;
    static const INT MAX_BITS = 12;
    static const INT MAX_CODES = 1 << MAX_BITS;
    static const INT CODE_CLEAR = 1 << START_BITS;
    static const INT CODE_TERM = CODE_CLEAR + 1;
    INT WriteBitAccum, ReadBitAccum, WriteBitPos, ReadBitPos, BitAccum, BitPos, CodeSize = START_BITS + 1;                  /* byte accumulator and bit position */

    struct
    {
      INT Pref, Suf;
    }Dict[MAX_CODES];
    INT DictSize;

    /* Class constructor.
     * AGUMENTS: None.
     */
    rw( VOID )
    {
    } /* End of 'rw' function */

    /* Class constructor.
     * AGUMENTS: None.
     */
    rw( const std::string FileName )
    { 
      Open(FileName);
    } /* End of 'rw' function */

    /* Class destructor*/
    ~rw( VOID )
    {
    } /* End of '~rw' function */

    /* Open file function.
     * ARGUMENTS:
     *   - Filename:
     *       const std::string &FileName;
     *   (rw) Read/Write type.
     */
    VOID Open( const std::string &FileName, const type &Type = type::READ );

    /* Close file function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Close( VOID );

    /* Close file function.
     * ARGUMENTS:
     *   - Bit:
     *       Bit;
     * RETURNS: None.
     */
    VOID WriteBit( INT Bit );

    /* Close file function.
     * ARGUMENTS:
     *   - Bit:
     *       Bit;
     *   - Count of bits:
     *       BitsCount;
     * RETURNS: None.
     */
    VOID WriteBits( INT Bit, INT BitsCount );

    /* Read bit from file function.
     * ARGUMENTS: None
     * RETURNS:
     *   (INT) result.
     */
    INT ReadBit( VOID );

    /* Read bits from file function.
     * ARGUMENTS:
     *   - Count of bits:
     *       BitsCount;
     * RETURNS:
     *   (INT) result.
     */
    INT ReadBits( INT BitsCount );

    /* Check if current get is EOF function.
     * ARGUMENTS: None.
     * RETURNS:
     *   (BOOL) result.
     */
    BOOL is_eof( VOID );

    /* close write bit function
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID WriteBitClose( VOID );
    INT Decode( VOID );

}; /* End of 'rw' class */

/* Compress file function.
 * ARGUMENTS:
 *   - Filename:
 *       const std::string &FileName;
 * RETURNS: None.
 */
VOID Compress( const std::string &FileName );

/* Decompress file function.
 * ARGUMENTS:
 *   - Filename:
 *       const std::string &FileName;
 * RETURNS: None.
 */
VOID Decompress( const std::string &FileName );

#endif /* __t49lzw_h_ */

/* END OF 't49lzw.h' FILE */                                 
