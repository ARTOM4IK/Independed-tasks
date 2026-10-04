/* Arsentev Artemy, 9-4, 25.11.2024 */

#ifndef __BITRW_H_
#define __BITRW_H_

#include "commondf.h"

/* Output write bit functions */
VOID WriteBitInit( FILE *F );
VOID WriteBit( INT Bit ); 
VOID WriteBitClose( VOID );
/* Output read bit functions */
VOID ReadBitInit( FILE *F );
INT ReadBit( VOID );

#endif /* __BITRW_H_ */

/* END OF 'BITRW.H' FILE */