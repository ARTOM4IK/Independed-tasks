/* FILE NAME  : commondf.glsl
 * PROGRAMMER : AA4
 * LAST UPDATE: 24.02.2025
 * PURPOSE    : GLSL shader text.
 *              Common includes.
 */
 
/* Camera UBO data UBO representation trype (update once per camera/frame change) */
layout(std140, binding = 0) uniform UBO_CAMERA
{
  mat4 MatrVP;              /* Premultiplied 'view' and 'projection' matrixes */
  mat4 MatrV;               /* Matrix 'view' */
  mat4 MatrP;               /* Matrix 'projection' */
 
  vec4 CamLoc4;              /* Camera location */
  vec4 CamRight4;            /* Camera right direction */
  vec4 CamUp4;               /* Camera up direction */
  vec4 CamDir4;              /* Camera forward direction */
  vec4 CamAt4;               /* Camera at position */
  vec4 FrameWHProjSizeDist; /* Camera frame size, projection size and distance */
};
#define CamAt CamAt4.xyz
#define CamLoc CamLoc4.xyz
#define CamRight CamRight4.xyz
#define CamUp CamUp4.xyz
#define CamDir CamDir4.xyz
 
#define FrameW FrameWHProjSizeDist.x
#define FrameH FrameWHProjSizeDist.y
#define ProjSize FrameWHProjSizeDist.z
#define ProjDist FrameWHProjSizeDist.w
 
/* Synchronization data UBO representation trype (update every frame) */
layout(std140, binding = 1) uniform UBO_SYNC
{
  vec4 TimeDeltaTimeGlobalTimeDeltaTime; /* Time parameters */
  vec4 IsWireFrameIsPauseFPS;            /* Wireframe and pause flags and FPS value */
};
#define Time TimeDeltaTimeGlobalTimeDeltaTime.x
#define DeltaTime TimeDeltaTimeGlobalTimeDeltaTime.y
#define GlobalTime TimeDeltaTimeGlobalTimeDeltaTime.z
#define GlobalDeltaTime TimeDeltaTimeGlobalTimeDeltaTime.w
#define IsWireframe bool(IsWireFrameIsPauseFPS.x)
#define IsPause bool(IsWireFrameIsPauseFPS.y)
#define FPS IsWireFrameIsPauseFPS.z
 
/* Material data UBO representation trype (update at material creation) */
layout(std140, binding = 2) uniform UBO_MTL
{
  vec4 MtlKa4;           /* Ambient Time parameters */
  vec4 MtlKdTrans;       /* Diffuse coefficient and transparency */
  vec4 MtlKsPh;          /* Specular coefficient and Phong power value */
  ivec4 TextureFlags[2]; /* Material texture flags */
};
#define MtlKa MtlKa4.xyz
#define MtlKd MtlKdTrans.xyz
#define MtlKs MtlKsPh.xyz
#define MtlPh MtlKsPh.w
#define MtlTrans MtlKdTrans.w
#define IsTexture0 bool(TextureFlags[0][0])
#define IsTexture1 bool(TextureFlags[0][1])
 
/* Primitive draw parameters data UBO representation trype (update before primitive drawing) */
layout(std140, binding = 3) uniform UBO_PRIM
{
  mat4 MatrWVP;    /* Premultiplyed 'world' - 'view' - 'projection' matrixes */
  mat4 MatrW;      /* World primitive matrix */
  mat4 MatrWInv;   /* Inverse transposed world matrix (for normals) */
};

layout(std140, binding = 4) uniform UBO_LIGHT
{
  vec4 PosCutOffAngle1;  /* Point and spot */
  vec4 PosCutOffAngle2;  /* Directional and */
  vec4 ColorCutOffDist1; /* Light source color */
  vec4 AttCutOffDist2;   /* Attenuation by */
};
#define LightPos PosCutOffAngle1.xyz
#define LightDir PosCutOffAngle2.xyz
#define LightColor ColorCutOffDist1.xyz
#define LightAtt AttCutOffDist2.xyz
#define LightCutDist1 ColorCutOffDist1.w
#define LightCutDist2 AttCutOffDist2.w
#define LightCutA1 PosCutOffAngle1.w
#define LightCutA2 PosCutOffAngle2.w

/**/
#ifdef VERTEX_SHADER
layout(location = 0) in vec3 InPosition;
layout(location = 1) in vec2 InTexCoord;
layout(location = 2) in vec3 InNormal;
layout(location = 3) in vec4 InColor;
#endif // VERTEX_SHADER

#ifdef FRAGMENT_SHADER
layout(location = 0) out vec4 OutColor;
layout(location = 1) out vec4 OutPosId;
layout(location = 2) out vec4 OutNormalIsShade;
layout(location = 3) out vec4 OutKa;
layout(location = 4) out vec4 OutKdTrans;
layout(location = 5) out vec4 OutKsPh;

layout(location = 0) uniform sampler2D InColor;
layout(location = 1) uniform sampler2D InPosId;
layout(location = 2) uniform sampler2D InNormalIsShade;
layout(location = 3) uniform sampler2D InKa;
layout(location = 4) uniform sampler2D InKdTrans;
layout(location = 5) uniform sampler2D InKsPh;
                  
layout(binding = 0) uniform sampler2D GBuffs[6];
#endif // FRAGMENT_SHADER
 
/* Light point function */

vec3 Shade( vec3 P, vec3 N, vec3 Kd, vec3 Ks, float Ph, vec3 LDir, vec3 LColor )
{
  vec3 color = vec3(0);
  vec3 V = normalize(P - CamLoc);
 
  N = faceforward(N, V, N);
  // Diffuse
  color += max(0, dot(N, LDir)) * Kd * LColor;
 
  // Specular
  vec3 R = reflect(V, N);
  color += pow(max(0, dot(R, LDir)), Ph) * Ks * vec3(1, 1, 1);
 
  return color;
} 

uniform mat4 MySuperM;

/* Math functions */

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

mat4 MatrRotateX( float AngleInDegree )
{
  float
    pi = acos(-1),
    a = AngleInDegree * pi / 180,
    si = sin(a), co = cos(a);
	 
  return
    mat4(vec4(1, 0, 0, 0),
         vec4(0, co, si, 0),
         vec4(0, -si, co, 0),
         vec4(0, 0, 0, 1));
} /* End of 'MatrRotateX' function */

mat4 MatrRotateZ( float AngleInDegree )
{
  float
    pi = acos(-1),
    a = AngleInDegree * pi / 180,
    si = sin(a), co = cos(a);
	 
  return
    mat4(vec4(co, si, 0, 0),
         vec4(-si, co, 0, 0),
         vec4(0, 0, 1, 0),
         vec4(0, 0, 0, 1));
} /* End of 'MatrRotateZ' function */

