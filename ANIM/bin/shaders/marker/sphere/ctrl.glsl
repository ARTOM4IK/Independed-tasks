/* FILE NAME  : ctrl.glsl
 * PROGRAMMER : AA4
 * LAST UPDATE: 19.02.2025
 * PURPOSE    : 3D animation project.
 *              Sphere marker shader.
 */
layout(vertices = 1) out; // Количество вершин в одном наборе

void main( void )
{
  float
    d = 0,//distance(CamLoc, vec3(MatrW * vec4(AddonV[0].xyz, 1))) - max(AddonV[1].x, max(AddonV[1].y, AddonV[1].z)),
    min_d = 2, max_d = 30,
    min_n = 5, max_n = 47,
    n = d > max_d ? min_n : d < min_d ? max_n : mix(max_n, min_n, (d - min_d) / (max_d - min_d));

  //gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;
  //B[gl_InvocationID] = A[gl_InvocationID];

  // n = 10 + 20 * abs(sin(Time * 0.30));

  //n = 30;

  gl_TessLevelOuter[0] = n;
  gl_TessLevelOuter[1] = n;
  gl_TessLevelOuter[2] = n;
  gl_TessLevelOuter[3] = n;

  gl_TessLevelInner[0] = n;  // Указываем количество изолиний
  gl_TessLevelInner[1] = n; // Указываем величину разбиения ломаной

  /*
  gl_TessLevelOuter[0] = 5;
  gl_TessLevelOuter[1] = 3;
  gl_TessLevelOuter[2] = 8;

  gl_TessLevelInner[0] = 4;  // Указываем количество изолиний
  */
}
