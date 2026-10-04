/* FILE NAME  : frag.glsl
 * PROGRAMMER : AA4
 * LAST UPDATE: 24.01.2025
 * PURPOSE    : 3D animation project.
 *              Default vertex shader.
 */

in vec4 DrawColor;
/*
layout(location = 0) out vec4 OutColor;

uniform vec3 CamRight, CamDir, CamUp, CamLoc;
uniform float FrameW, FrameH, ProjDist, ProjSize, Time;
*/
layout(binding = 0) uniform sampler2D Tex[1];

/* The main program function */
void main( void )
{
  float Wp = ProjSize, Hp = ProjSize;

  /* Correct aspect ratio */
  if (FrameW > FrameH)
    Wp *= FrameW / FrameH;
  else
    Hp *= FrameH / FrameW;

  float xp = Wp * gl_FragCoord.x / FrameW - Wp / 2;
  float yp = Hp * gl_FragCoord.y / FrameH - Hp / 2;
  vec3 Dir = CamDir * ProjDist + CamRight * -xp + CamUp * -yp;
  Dir = normalize(Dir);
  float
    pi = acos(-1),
    theta = acos(Dir.y),
    phi = atan(Dir.x, Dir.z);
  vec2 texcoord = vec2(phi / 2 / pi, theta / pi);
  OutColor = vec4(Dir * 0.5 + 0.5, 1);
  int k = int(Time * 0.30) % 2;
  k = 1;                              
  vec4 tc = texture(Tex[0], texcoord);

//  OutColor = DrawColor;
  OutColor = vec4(tc.rgb, 1);
  OutPosId = vec4(0);
  OutNormalIsShade = vec4(0, 0, 0, 0);
  OutKa = vec4(0);
  OutKdTrans = vec4(0);
  OutKsPh = vec4(0);

} /* End of 'main' function */

/* END OF 'frag.glsl' FILE */
