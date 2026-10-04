/* FILE NAME: globe.h
 * PROGRAMMER: AA4
 * DATE: 05.01.2025
 * PURPOSE: draw sphere
*/

#ifndef __globe_h_
#define __globe_h_

typedef double DBL;

#define GEOM_W 20  /* Grid width */
#define GEOM_H 20  /* Grid height */

/* Init sphere.
 * ARGUMENTS:
 *   - Number:
 *       DBL x;
 * RETURNS:
 *   Number in range from 0 to 255.
 */
VOID GLB_INIT( DBL R );
/* Get screen size function.
 * ARGUMENTS:
 *   - Number:
 *       INT Ws, INT Hs;
 * RETURNS:
 *   Nothing.
 */
VOID GLB_RESIZE( INT Ws, INT Hs );
/* Draw sphere function.
 * ARGUMENTS:
 *   - DC Handle:
 *       HDC hDC;
 * RETURNS:
 *   Nothing.
 */
VOID GLB_DRAW( HDC hDC );

#endif /*__globe_h_*/
                           
/* END OF 'globe.h' FILE */