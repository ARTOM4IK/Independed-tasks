/* Arsentev Artemy, 09-4, 06.11.2024 */

#define MAX 10
#define INFINITY 10000

int Adj[MAX][MAX], PathLen, BestPathLen, Was[MAX], Path[MAX], BestPath[MAX], Len[MAX], From[MAX], NewLen[MAX];

void LabLoad( char *Filename );
void LabSet( int a, int b );
void GetStr( char *Str, int MaxLen );
int GoAny( int a, int b );
int GoAll( int a, int b );
int GoBest( int a, int b );
void Lload( char *Filename );
void BFS( int a, int b );