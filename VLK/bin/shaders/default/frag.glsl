/* FILE NAME  : frag.glsl
 * PROGRAMMER : AA4
 * LAST UPDATE: 04.08.2025
 * PURPOSE    : 3D animation project.
 *              Texture vertex shader.
 */

//layout(location = 0) out vec4 OutColor;

in VS_OUT
{
  vec4 DrawColor;
  vec3 DrawNormal;
  vec3 DrawPos;
  vec2 DrawTexCoord;
} vs_out;

//layout(binding = 0) uniform sampler2D Texture0;
layout(binding = 0) uniform sampler2D Tex;

void main( void )
{
  vec4 tc = texture(InColor, vs_out.DrawTexCoord); 
  vec3 N = normalize(vs_out.DrawNormal);
  //vec3 L = normalize(vec3(3 * sin(Time / 0.3), 1, 3 * sin(1.2 * Time / 0.3)));
  //float tr = KdTrans.a;
  //if (TextureFlags[0])
  //  if (texture(Texture0, vs_out.DrawTexCoord).a < 0.01)
  //   discard;
  

  //vec4 tc1 = texture(InPosId, vs_out.DrawTexCoord);
  //OutPosId = vec4(vs_out.DrawPos, 1.0);
  //OutNormalIsShade = vec4(tc1.xyz, 1);
  //OutNormalIsShade = vec4(N, 1);
  //OutColor = tc;
  //OutColor = DrawColor;
  //OutColor = vec4(1, 1, 0, 1);
  //OutColor = vec4(cos(SyncGlobalTimeGlobalDeltaTimeTimeDeltaTime.z), sin(SyncGlobalTimeGlobalDeltaTimeTimeDeltaTime.z), 0, 1);

  //vec3 N = normalize(DrawNormal);
 
  //OutColor = vs_out.DrawColor;
  OutPosId = vec4(vs_out.DrawPos, 1);
  //OutPosId = vec4(0, 0, 0, 1);
  OutNormalIsShade = vec4(N, 1);
  vec3 Kdf = MtlKd;
  OutKdTrans = vec4(Kdf, Trans);
  OutKsPh = vec4(MtlKs, 1);
  //OutKsPh = vec4(MtlKs, 1);
  //OutKsPh = tc;
  //OutKsPh = vec4(1, 0, 1, 1);
  OutKa = vec4(MtlKa, 1);
  OutColor = tc;
}
                       
/* END OF 'frag.glsl' FILE */
