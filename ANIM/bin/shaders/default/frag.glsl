/* FILE NAME  : frag.glsl
 * PROGRAMMER : AA4
 * LAST UPDATE: 05.02.2025
 * PURPOSE    : 3D animation project.
 *              Texture vertex shader.
 */
/*
layout(location = 0) out vec4 OutColor;
uniform sampler2D Tex;

uniform float Time;
uniform vec3 CamLoc;
uniform vec3 Ka, Kd, Ks;
uniform float Ph;
*/

in vec4 DrawColor;
in vec3 DrawNormal;
in vec3 DrawPos;
in vec3 DrawWPos;
in vec2 DrawTexCoord;

layout(binding = 0) uniform sampler2D Tex;

/* The main program function */
void main( void )
{
  vec4 tc = texture(Tex, DrawTexCoord); 
  //OutColor = vec4(1, 1, 0, 1);
  vec3 N = normalize(DrawNormal);
  OutColor = DrawColor;
  OutPosId = vec4(DrawPos, 0);
  OutNormalIsShade = vec4(N, 1);
  vec3 KdF = MtlKd;
//  if (isTexture0)
  KdF *= tc.xyz;
	
  OutKa = vec4(MtlKa, 0);
  OutKdTrans = vec4(KdF, MtlTrans);
  OutKsPh = vec4(MtlKs, MtlPh);
  OutColor = tc;
  //OutColor = vec4(tc.rgb, tc.a);
} /* End of 'main' function */

/* END OF 'frag.glsl' FILE */
