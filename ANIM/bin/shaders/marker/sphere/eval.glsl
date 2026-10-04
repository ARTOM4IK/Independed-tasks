/* FILE NAME  : eval.glsl
 * PROGRAMMER : AA4
 * LAST UPDATE: 19.02.2025
 * PURPOSE    : 3D animation project.
 *              Sphere marker shader.
 */
/* ”казываем тип построени€ разбиени€ Ц ломана€ (изолини€) */
// equal_spacing  fractional_even_spacing

layout(quads, fractional_even_spacing) in;

out vec3 DrawNormal;
out vec2 DrawTexCoord;

void main( void )
{
  float
    t = gl_TessCoord.y * acos(-1),
    p = gl_TessCoord.x * 2 * acos(-1);
  vec3
    pnt = vec3(sin(t) * sin(p), cos(t), sin(t) * cos(p));

  //t = gl_TessCoord.y;
  //p = gl_TessCoord.x;
  //pnt = vec3(t, p, 0) * 0.8;


  DrawTexCoord = gl_TessCoord.xy;
//  DrawNormal = mat3(MatrWInv) * normalize(pnt / AddonV[1].xyz);
  // gl_in[0..3].gl_Position;
//  gl_Position = MatrWVP * vec4(AddonV[0].xyz + pnt * AddonV[1].xyz, 1);
  //gl_Position = vec4(pnt, 1);
}
