/* FILE NAME  : ctrl.glsl
 * PROGRAMMER : AA4
 * LAST UPDATE: 21.02.2025
 * PURPOSE    : 3D animation project.
 *              Cylinder marker shader.
 */
layout(vertices = 1) out;

void main( void )
{
  int n1 = 5, n2 = 47;

  gl_TessLevelOuter[0] = n1;
  gl_TessLevelOuter[1] = n2;
  gl_TessLevelOuter[2] = n1;
  gl_TessLevelOuter[3] = n2;

  gl_TessLevelInner[0] = n2;
  gl_TessLevelInner[1] = n1;
}
