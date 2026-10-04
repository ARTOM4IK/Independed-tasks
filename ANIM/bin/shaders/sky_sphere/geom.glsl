/* FILE NAME  : geom.glsl
 * PROGRAMMER : AA4
 * LAST UPDATE: 07.02.2025
 * PURPOSE    : 3D animation project.
 *              Default vertex shader.
 */

layout(points) in;
layout(triangle_strip, max_vertices = 3) out;

out vec4 DrawColor;

/* The main program function */
void main( void )
{
  DrawColor = vec4(1, 0, 0, 1);

  gl_Position = vec4(-1, 3, 0, 1);
  EmitVertex();
  gl_Position = vec4(-1, -1, 0, 1);
  EmitVertex();
  gl_Position = vec4(3, -1, 0, 1);
  EmitVertex();
  EndPrimitive();
} /* End of 'main' function */

/* END OF 'vert.glsl' FILE */
