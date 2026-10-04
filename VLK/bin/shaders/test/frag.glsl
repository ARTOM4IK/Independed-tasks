#version 460
layout(location = 0) out vec3 OutPosition;
layout(location = 0) in vec3 InPosition;
layout(location = 1) in vec2 InTexture;
layout(location = 1) out vec2 OutTexture;
layout(location = 2) in vec3 InNormal;
layout(location = 2) out vec3 OutNormal;
layout(location = 3) out vec4 OutColor;
layout(location = 3) in vec4 InColor;
layout( push_constant ) uniform SM
{
  mat4 matrWVP;
  mat4 matrW;
  vec4 Ka;
  vec4 KdTrans;
  vec4 KsPh;
};

layout(std140, set = 0, binding = 0) buffer Sync
{
  vec4 SyncGlobalTimeGlobalDeltaTimeTimeDeltaTime;
  //vec4 SyncFPSIsPause;
};
#define Time SyncGlobalTimeGlobalDeltaTimeTimeDeltaTime.z
layout(std140, binding = 1) buffer Camera
{
  mat4 MatrView;
  mat4 MatrProj;
  mat4 MatrVP;
  vec4 CamLocFrameW;
  vec4 CamDirProjDist;
  vec4 CamRightWp;
  vec4 CamUpHp;
  vec4 CamAtFrameH;
  vec4 CamWpHpSizeProjDist;
};

layout(set = 1, binding = 0) uniform sampler2D texDiffuse;
layout(set = 1, binding = 1) uniform sampler2D texNormal;
layout(set = 1, binding = 2) uniform sampler2D texSpecular;
layout(set = 1, binding = 3) uniform sampler2D texEmissive;
layout(set = 1, binding = 4) uniform sampler2D texAO;
  
/* Shade point function */
vec3 Shade( vec3 P, vec3 N, vec3 Kd, vec3 Ks, float Ph, vec3 LDir, vec3 LColor )
{
  N = normalize(N);
  vec3 color = vec3(0);
  vec3 V = normalize(CamLocFrameW.xyz - P);
  N = normalize(faceforward(N, V, N));
  // Diffuse
  color += max(0, dot(N, LDir)) * Kd * LColor;
  // Specular
  vec3 R = reflect(V, N);
  color += pow(max(0, dot(R, LDir)), Ph) * Ks * LColor;
  //return N;
  return color;
}

void main( void )
{
  OutColor = vec4(cos(Time.x * 5), sin(Time.x), 0, 1);
  OutColor = -vec4(normalize(InNormal.xyz), 1);
  vec4 texColor = texture(texDiffuse, InTexture);
  OutColor = texColor;
  OutColor = texColor * vec4(Shade(InPosition, InNormal.xyz, KdTrans.xyz, KsPh.xyz, KsPh.w, vec3(0, -0.8, -0.8), vec3(1, 1, 1)), 1);
}
