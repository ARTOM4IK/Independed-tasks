/* FILE NAME  : vert.glsl
 * PROGRAMMER : AA4
 * LAST UPDATE: 19.02.2025
 * PURPOSE    : 3D animation project.
 *              Sphere marker shader.
 */

out vec4 DrawColor;

out vec3 A;

/* The main program function */
void main( void )
{
  gl_Position = MatrWVP * vec4(InPosition, 1);
  
  A = InPosition;
  DrawColor = InColor;
} /* End of 'main' function */

/* END OF 'vert.glsl' FILE */
