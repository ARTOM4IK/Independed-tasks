/* FILE NAME  : frag.glsl
 * PROGRAMMER : AA4
 * LAST UPDATE: 24.02.2025
 * PURPOSE    : 3D animation project.
 *              Texture vertex shader.
 */

layout(location = 0) out vec4 OutColor;

in vec4 DrawColor;
in vec3 DrawNormal;
in vec3 DrawPos;
in vec3 DrawWPos;
in vec2 DrawTexCoord;

//uniform sampler2D Tex;
layout(binding = 0) uniform sampler2D Tex;
/*
uniform float Time;
uniform vec3 CamLoc;
uniform vec3 Ka, Kd, Ks;
uniform float Ph;
*/
vec3 Shade( vec3 P, vec3 N )
{
  vec3 L = normalize(vec3(1, 2, 3));
  vec3 LC = vec3(1, 1, 1);
 
  vec3 color = vec3(0);
  vec3 V = normalize(P - CamLoc);
 
  // Ambient
  color = Ka;
 
  N = faceforward(N, V, N);
  // Diffuse
  color += max(0, dot(N, L)) * Kd * LC;
 
  // Specular
  vec3 R = reflect(V, N);
  color += pow(max(0, dot(R, L)), Ph) * Ks * LC;
 
  return color;
}

/* The main program function */
void main( void )
{
  vec4 tc = texture(Tex, DrawTexCoord); 
  //OutColor = vec4(1, 1, 0, 1);
  OutColor = DrawColor * tc;
  //OutColor = vec4(tc.rgb, tc.a);
} /* End of 'main' function */

/* END OF 'frag.glsl' FILE */
