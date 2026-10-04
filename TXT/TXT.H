/* Arsentev Artemy, 09-4, 27.10.2024 */

char *LoadText( char *FileName );
void GetLettersCounts( char *S, int *count );
void GetStr( char *Str, int MaxLen );
void CountRussianLetters( char *Str, int *Counters );
int WordAnyCount( char *S, int (*F)( char *S, int Start, int End ) );
int CntSymWord( char *S, int Start, int End );
int CntDigit( char *S, int Start, int End );
int CntWord( char *S, int Start, int End );