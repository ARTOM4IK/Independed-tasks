/* FILE NAME  : vert.glsl
 * PROGRAMMER : AA4
 * LAST UPDATE: 05.02.2025
 * PURPOSE    : 3D animation project.
 *              Default vertex shader.
 */
/*
layout(location = 0) in vec3 InPosition;
layout(location = 1) in vec2 InTexCoord;
layout(location = 2) in vec3 InNormal;
layout(location = 3) in vec4 InColor;
uniform mat4 MatrWVP;
uniform mat4 MatrW;
uniform vec3 CamLoc;
uniform vec3 CamPos;
uniform float Time;
*/
out vec4 DrawColor;
out vec3 DrawNormal;
out vec3 DrawPos;
out vec3 DrawWPos;

mat4 MatrRotateY( float AngleInDegree )
{
  float
    pi = acos(-1),
    a = AngleInDegree * pi / 180,
    si = sin(a), co = cos(a);
	 
  return
    mat4(vec4(co, 0, -si, 0),
         vec4(0, 1, 0, 0),
         vec4(si, 0, co, 0),
         vec4(0, 0, 0, 1));
} /* End of 'MatrRotateY' function */

/* The main program function */
void main( void )
{
  //gl_Position = MatrWVP * MatrRotateY(0 * Time) * vec4(InPosition + vec3(0, sin(InPosition.x + 30 * Time) + 10.30 * sin(3 * Time), 0), 1);
  gl_Position = MatrWVP * vec4(InPosition, 1);
/*  
  DrawColor = InColor;
  DrawNormal = mat3(transpose(inverse(MatrW))) * InNormal;
  DrawPos = InPosition;
  DrawWPos = (MatrW * vec4(InPosition, 1)).xyz;*/
} /* End of 'main' function */

/* END OF 'vert.glsl' FILE */
