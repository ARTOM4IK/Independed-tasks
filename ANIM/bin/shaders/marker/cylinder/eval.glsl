/* FILE NAME  : eval.glsl
 * PROGRAMMER : AA4
 * LAST UPDATE: 21.02.2025
 * PURPOSE    : 3D animation project.
 *              Cylinder marker shader.
 */

layout(quads, equal_spacing) in;

out vec3 DrawNormal;
out vec2 DrawTexCoord;

void main( void )
{
  float Radius0 = 0/*AddonF[0]*/, Radius1 = 0/*AddonF[1]*/;
  vec3
    P0 = vec3(0,0,0),//AddonV[0].xyz,
    P1 = vec3(0,0,0),//AddonV[1].xyz,
    Dir = P1 - P0,
    P, N;
  float
    DirLen = length(Dir);
  Dir /= DirLen;

  if (gl_TessCoord.y == 1)
    P = P1, N = Dir;
  else if (gl_TessCoord.y == 0)
    P = P0, N = -Dir;
  else
  {
    vec3
      U = cross(Dir, vec3(1, 0, 0)) + cross(Dir, vec3(0, 1, 0)),
      R = normalize(cross(U, Dir));
    U = cross(Dir, R);
    float
      phi = gl_TessCoord.x * 2 * acos(-1),
      sp = sin(phi), cp = cos(phi),
      radius = mix(Radius0, Radius1, gl_TessCoord.y >= 0.5);

    P = mix(P0, P1, gl_TessCoord.y >= 0.5) + (R * cp + U * sp) * radius;
    if (gl_TessCoord.y > 0.7)
      N = Dir;
    else if (gl_TessCoord.y < 0.30)
      N = -Dir;
    else
      N = Dir * (Radius0 - Radius1) + (R * cp + U * sp) * DirLen;
  }
  DrawTexCoord = gl_TessCoord.xy;
  DrawNormal = mat3(MatrWInv) * normalize(N);
  gl_Position = MatrWVP * vec4(P, 1);
}
