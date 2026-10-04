/* FILE NAME  : frag.glsl
 * PROGRAMMER : AA4
 * LAST UPDATE: 05.02.2025
 * PURPOSE    : 3D animation project.
 *              Default vertex shader.
 */

layout(location = 0) out vec4 OutColor;
layout(location = 1) out vec4 OutPosition;

in vec4 DrawColor;
in vec3 DrawNormal;
in vec3 DrawPos;
in vec3 DrawWPos;
/*
uniform float Time;
uniform vec3 CamLoc;
uniform vec3 Ka, Kd, Ks;
uniform float Ph;
*/

/* The main program function */
void main( void )
{
  vec3 N = normalize(DrawNormal);
  vec3 L = normalize(vec3(8 * sin(5 * Time), 1, 1));
  float nl = max(0.1, dot(N, L));
  /*
  if (DrawPos.y > 8 && DrawPos.x > 0)
    ;//discard;
  if (DrawPos.z > 0)
    discard;
  */
/*
  if (gl_FragCoord.x < 300)
  {
    OutColor = vec4(0.47, N.y, 0.30, 1);
    return;
    discard;
  }
*/
//  OutColor = sin(30 * Time);
//  OutColor = DrawColor;
//  OutColor = vec4(sin(Time * 4), sin(Time * 8), sin(Time * 16), 1);
//  OutColor = vec4(OutColor.x * nl, OutColor.y * nl, OutColor.z * nl,1);                              
//  OutColor = vec4(vec3(0.8, 0.47, 0.3)  * nl, 1);
  //OutColor = vec4(tc.rgb, tc.a);
  //OutColor = vec4(1, 1, 0, 1);
  OutColor = vec4(Shade(DrawWPos, normalize(DrawNormal)), 1);
/*  OutColor += vec4(vec3(0, 1, 0) *
    pow(abs(sin(DrawWPos.x * 15 * 1 + Time * 8)), 8 * 30) +
    pow(abs(sin(DrawWPos.z * 15 * 1 + Time * 8)), 8 * 30), 0);*/
} /* End of 'main' function */

/* END OF 'frag.glsl' FILE */
