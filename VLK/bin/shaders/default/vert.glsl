/* FILE NAME  : vert.glsl
 * PROGRAMMER : AA4
 * LAST UPDATE: 05.08.2025
 * PURPOSE    : 3D animation project.
 *              Default vertex shader.
 */

out VS_OUT
{
  vec4 DrawColor;
  vec3 DrawNormal;
  vec3 DrawPos;
  vec2 DrawTexCoord;
} vs_out;


void main( void )
{
  vec3 tmp = InPosition;
  
  gl_Position = MatrWVP * vec4(InPosition, 1);
  vs_out.DrawColor = InColor;
  vs_out.DrawNormal = mat3(MatrWInvTrans) * InNormal;
  vs_out.DrawPos = vec3(MatrW * vec4(InPosition, 1));
  //vs_out.DrawTexCoord = vec2(-InPosition.x, -InPosition.y);
  vs_out.DrawTexCoord = InTexCoord;
}

/* END OF 'vert.glsl' FILE */
