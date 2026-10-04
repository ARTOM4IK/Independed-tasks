/* FILE NAME  : frag.glsl
 * PROGRAMMER : AA4
 * LAST UPDATE: 24.01.2025
 * PURPOSE    : 3D animation project.
 *              Default vertex shader.
 */
/*
layout(location = 0) out vec4 OutColor;
*/
in vec4 DrawColor;
in vec3 DrawNormal;
in vec3 DrawPos;
in vec3 DrawWPos;
in vec2 DrawTexCoord;

/*
uniform float Time;

uniform vec3 CamLoc, Ka, Kd, Ks;
uniform float Ph, Trans;
uniform bool IsTexture0;
*/
layout(binding = 0) uniform sampler2D Tex;

/* The main program function */
void main( void )
{
  vec4 tc = texture(Tex, DrawTexCoord);

  //tc.rgba = vec4(1);
  if (tc.a < 0.18)
    discard;
  OutColor = vec4(tc.rgb, tc.a);
  OutColor = vec4(cos(Time), 1, sin(Time), sin(Time));

} /* End of 'main' function */

/* END OF 'frag.glsl' FILE */
