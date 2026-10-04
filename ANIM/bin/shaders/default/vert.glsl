/* FILE NAME  : vert.glsl
 * PROGRAMMER : AA4
 * LAST UPDATE: 05.02.2025
 * PURPOSE    : 3D animation project.
 *              Default vertex shader.
 */

out vec4 DrawColor;
out vec3 DrawNormal;
out vec3 DrawPos;
out vec3 DrawWPos;
out vec2 DrawTexCoord;

/* The main program function */
void main( void )
{
  vec3 p;

  gl_Position = MatrWVP * MatrRotateX(270) * MatrRotateZ(180) * vec4(InPosition, 1);
  //gl_Position = MatrWVP * MatrRotateY(0 * Time) * vec4(InPosition + vec3(0, sin(InPosition.x + 30 * Time) + 10.30 * sin(3 * GlobalTime), 0), 1);

  DrawColor = InColor;
  DrawNormal = mat3(transpose(inverse(MatrW))) * InNormal;
  DrawPos = InPosition;
  DrawWPos = (MatrW * vec4(InPosition, 1)).xyz;
  DrawTexCoord = InTexCoord;	
} /* End of 'main' function */

/* END OF 'vert.glsl' FILE */
