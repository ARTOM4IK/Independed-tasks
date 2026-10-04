/*************************************************************
 * Copyright (C) 2025
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : t50gif.cpp
 * PURPOSE     : Googling Information Forever project.
 *               Main module.
 * PROGRAMMER  : AA4.
 *               
 * LAST UPDATE : 21.10.2025.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#include "t50gif.h"
#include "glut.h"

static gif g;

/* Display function.
 * ARGUMENTS: None. 
 * RETURNS: None. 
 */
void Display( void )
{
  g.Open("s.gif");
} /* End of 'Display' function */

/* Keyboard function.
 * ARGUMENTS:
 *   - keyboard char and mouse position:
 *       unsigned char key, int x, int y;
 * RETURNS: None. 
 */
void Keyboard( unsigned char key, int x, int y )
{
  if (key == 27)
    exit(0);
  else if (key == 'f')
    glutFullScreen();
} /* End of 'Keyboard' function */

/* Main program function.
 * ARGUMENTS:
 *   - args:
 *       int argc, char *argv[];
 * RETURNS: 
 *   (INT) 0.
 */
int main( int argc, char *argv[] )
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

  glutInitWindowPosition(0, 0);
  glutInitWindowSize(FRAME_W, FRAME_H);
  glutCreateWindow("CGSG solo");

  glutDisplayFunc(Display);
  glutKeyboardFunc(Keyboard);
  glutMainLoop();
  glClearColor(0.30, 0.47, 0.8, 1);

  return 0;
} /* End of 'main' function */

/* END OF 't50gif.cpp' FILE */                                 
