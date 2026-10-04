/* Arsentev Artemy, 09-4, 11.10.2024 */

typedef unsigned long long UINT64;

UINT64 randu64( void );
void FillIncr( UINT64 *a, int size );
void FillRand( UINT64 *a, int size );
void FillDecr( UINT64 *a, int size );
void FillEq( UINT64 *a, int size );
void FillLevels( UINT64 *a, int size );
void FillRandAdv( UINT64 *a, int size );
int CheckSort( UINT64 *a, int size );
void Swap( UINT64 *a, UINT64 *b );
void FillMostly( UINT64 *a, int size );
void OutMas( UINT64 *a, int size );
void MergeSort( UINT64 *a, int size );
void DigitalSort( UINT64 *a, int size );
void QuickSort( UINT64 *a, int n );
void HeapSort( UINT64 *a, int n );