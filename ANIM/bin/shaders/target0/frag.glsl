/* FILE NAME  : frag.glsl
 * PROGRAMMER : AA4
 * LAST UPDATE: 17.03.2025
 * PURPOSE    : 3D animation project.
 *              Target0 vertex shader.
 */

//layout(location = 0) out vec4 OutColor;

layout(binding = 0) uniform sampler2D Tex;

void main( void )
{
//  vec4 tc = texture(Tex, gl_FragCoord.xy / vec2(FrameW, FrameH));
  ivec2 sc = ivec2(gl_FragCoord.xy);
  vec4 tc = texelFetch(Tex, sc, 0);
  vec4 tc11 = texelFetch(Tex, sc + ivec2(1, 1), 0);
  vec4 tc01 = texelFetch(Tex, sc + ivec2(1, 0), 0);
  vec4 tc10 = texelFetch(Tex, sc + ivec2(0, 1), 0);
  vec3 roberts = 2 * (abs(tc.rgb - tc11.rgb) + abs(tc10.rgb - tc01.rgb));

  float ks = 4;
  if (gl_FragCoord.x < FrameW / ks)
    if (gl_FragCoord.y < FrameH / ks)
    {
      vec4 t1 = texelFetch(Tex, ivec2(sc * ks), 0);
      OutColor = vec4(t1.rgb, 1);  
      return;
    }
  vec3 cc = pow(tc.rgb, vec3(0.3 + 1));
  OutColor = vec4((vec3(1, 1, 1) - roberts * 8) * 0.3 + cc * 0.9, 1);                                
}
