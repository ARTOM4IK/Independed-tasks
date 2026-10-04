/* FILE NAME  : frag.glsl
 * PROGRAMMER : AA4
 * LAST UPDATE: 19.03.2025
 * PURPOSE    : 3D animation project.
 *              Ambient light fragment shader.
 */

void main( void )
{
  ivec2 sc = ivec2(gl_FragCoord.xy);
  
  int s = 5;
/*  if (gl_FragCoord.y < 20)
    if (int(gl_FragCoord.x) % s == 0)
    {
      OutColor = vec4(1, 1, 1, 1);
      return;
    }
  if (gl_FragCoord.y < 50)
    if (int(gl_FragCoord.x) % (s * 10) == 0)
    {
      OutColor = vec4(1, 1, 1, 1);
      return;
    }
  if (gl_FragCoord.y < 80)
    if (int(gl_FragCoord.x) % (s * 100) == 0)
    {
      OutColor = vec4(1, 1, 1, 1);
      return;
    }
  if (gl_FragCoord.y < 10)
    if (gl_FragCoord.x / s < FPS / 10)
    {
      OutColor = vec4(1, 1, 0, 1);
      return;
    }*/
  float ks = 4.2;
  if (gl_FragCoord.x < FrameW / ks)
  {
    for (int i = 0; i < 5; i++)
    {
      if (gl_FragCoord.y < (i + 1) * FrameH / ks)
      {
        ivec2 sc1 = sc;
        sc1.y -= i * int(FrameH / ks);
        vec4 tc1 = texelFetch(GBuffs[i + 4], ivec2(sc1 * ks), 0);
        OutColor = vec4(tc1.rgb, 1);
        return;
      }
    }
  }

  vec4 Color = texelFetch(InColor, sc, 0);        
  vec4 PosId = texelFetch(InPosId, sc, 0);        
  vec4 NormalIsShade = texelFetch(InNormalIsShade, sc, 0);
  vec4 Ka = texelFetch(InKa, sc, 0);           
  vec4 Kd = texelFetch(InKdTrans, sc, 0);           
  vec4 KsPh = texelFetch(InKsPh, sc, 0);         
/*
  if (DNormalIsShade.w == 0)
  {
    vec4 Color = texelFetch(InColor, sc, 0);
    OutColor = Color;
  }
  else
  {
    vec4 Ka = texelFetch(InKa, sc, 0);
    vec4 KdTrans = texelFetch(InKdTrans, sc, 0);

    float s = 0.1;
    if (KdTrans.w != 1 && ((int(gl_FragCoord.x) ^ int(gl_FragCoord.y)) & 1) == 1)
      discard;
    //25m:40s
    OutColor = vec4(min(Ka.rgb, vec3(0.2)), 1);	
*/

  if (NormalIsShade.w == 0)
  {
    OutColor = vec4(0);
  }
  else
  {
    vec4 KsPh = texelFetch(InKsPh, sc, 0);
    vec4 PosId = texelFetch(InPosId, sc, 0);
    vec4 KdTrans = texelFetch(InKdTrans, sc, 0);

    float s = 1;
/*    if (KdTrans.w != 1 && ((int(gl_FragCoord.x * s) ^ int(gl_FragCoord.y * s)) & 1) == 1)
      discard;*/
    vec3 sh = Shade(PosId.xyz, NormalIsShade.xyz, KdTrans.rgb, KsPh.rgb, KsPh.a, normalize(LightPos - PosId.xyz), LightColor);
   OutColor = vec4(min(Ka.rgb, vec3(1)), 1);	
   //OutColor = vec4(1, 0, 0, 1);
//   OutColor = vec4(KdTrans.www, 1);
//   OutColor = vec4(sh, 1);
  }


    //OutColor = vec4(mix(DKd.rgb, DPosId.rgb, pow(1 - abs(sin(Time), 8)), 1));
//  OutColor = vec4(1, 0, 1, 1);
}