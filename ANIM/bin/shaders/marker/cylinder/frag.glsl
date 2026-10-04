/* FILE NAME  : frag.glsl
 * PROGRAMMER : AA4
 * LAST UPDATE: 21.02.2025
 * PURPOSE    : 3D animation project.
 *              Cylinder marker shader.
 */

layout(location = 0) out vec4 OutColor;

in vec3 DrawNormal;
in vec2 DrawTexCoord;
/* The main program function */
void main( void )
{
  if (IsWireframe)
  {
    OutColor = vec4(1, 1, 1, 1);
    return;
  }
  float nl = max(0.1, dot(normalize(DrawNormal), -CamDir));
  float s = 1;

  if (((int(DrawTexCoord.x * 30) ^ int(DrawTexCoord.y * 18)) & 1) == 1)
    s = 0.8;

//  OutColor = vec4(AddonV[2].rgb * nl * s, 1);
  //OutColor = vec4(normalize(DrawNormal), 1);
  OutColor = vec4(DrawTexCoord.yyy, 1);
} /* End of 'main' function */

/* END OF 'frag.glsl' FILE */
