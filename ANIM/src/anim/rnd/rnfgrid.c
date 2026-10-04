/* FILE NAME: rndgrid.c
 * PROGRAMMER: AA4
 * DATE: 12.02.2024
 * PURPOSE: 3D animation project.
 *          Grid module.
 */

#include "rnd.h"

/* Create grid function.
 * ARGUMENTS:
 *   - grid:
 *       aa4GRID *G;
 *   - grid size:
 *       INT W, INT H;
 * RETURNS: None.
 */
VOID AA4_RndGridCreate( aa4GRID *G, INT W, INT H )
{

} /* End of 'AA4_RndGridCreate' function */

/* Free grid function.
 * ARGUMENTS:
 *   - grid:
 *       aa4GRID *G;
 * RETURNS: None.
 */
VOID AA4_RndGridFree( aa4GRID *G )
{
  free(G);
  G = NULL;
} /* End of 'AA4_RndGridFree' function */

/* Eval auto normals in grid function.
 * ARGUMENTS:
 *   - grid:
 *       aa4GRID *G;
 * RETURNS: None.
 */
VOID AA4_RndGridAutoNormals( aa4GRID *G )
{
  AA4_RndPrimAutoNormals(G->V, G->W * G->H, NULL, 0);
} /* End of 'AA4_RndGridAutoNormals' function */

/* Make primitive from grid function.
 * ARGUMENTS:
 *   - primitive:
 *       aa4PRIM *Pr;
 *   - grid:
 *       aa4GRID *G;
 * RETURNS: None.
 */
VOID AA4_RndPrimFromGrid( aa4PRIM *Pr, aa4GRID *G )
{
  AA4_RndPrimCreate(Pr, AA4_RND_PRIM_TRISTRIP, G->V, G->H * G->W, NULL, 0);
} /* End of 'AA4_RndPrimFromGrid' function */

/* END OF 'rndgrid.c' FILE */
