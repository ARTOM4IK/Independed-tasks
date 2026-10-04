#version 460
layout(location = 0) in vec3 InPosition;
layout(location = 0) out vec3 OutPosition;

layout(location = 1) in vec2 InTexture;
layout(location = 1) out vec2 OutTexture;

layout(location = 2) in vec3 InNormal;
layout(location = 2) out vec3 OutNormal;

layout(location = 3) in vec4 InColor;
layout(location = 3) out vec4 OutColor;

layout(location = 4) in ivec4 InJoints;

layout(location = 5) in vec4 InWeight;

layout(std430, set = 0, binding = 0) buffer Sync
{
  vec4 SyncGlobalTimeGlobalDeltaTimeTimeDeltaTime;
  //vec4 SyncFPSIsPause;
};
#define Time SyncGlobalTimeGlobalDeltaTimeTimeDeltaTime.z
#define GlobalTime SyncGlobalTimeGlobalDeltaTimeTimeDeltaTime.x
layout(std430, binding = 1) buffer Camera
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

layout(std430, binding = 2) buffer World
{
  mat4 WVP;
  mat4 W;
  mat4 InvW;
  vec4 IsWire;
};
layout(std430, set = 1, binding = 5) buffer BoneMatrices 
{
    mat4 Bones[];
};
layout( push_constant ) uniform SM
{
  mat4 matrWVP;
  mat4 matrW;
  vec4 Ka;
  vec4 KdTrans;
  vec4 KsPh;
};

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

vec4 ApplySkinning(vec4 position, vec4 joints, vec4 weights)
{
    float totalWeight = weights.x + weights.y + weights.z + weights.w;
    //totalWeight = 0;
    if (totalWeight < 0.01) 
        return position;
    
    vec4 normalizedWeights = weights / totalWeight;
    
    mat4 skinMatrix = 
        Bones[int(joints.x + 0.001)] * normalizedWeights.x +
        Bones[int(joints.y + 0.001)] * normalizedWeights.y +
        Bones[int(joints.z + 0.001)] * normalizedWeights.z +
        Bones[int(joints.w + 0.001)] * normalizedWeights.w;
    
    return skinMatrix * position;
}

vec3 ApplySkinningToNormal(vec3 normal, vec4 joints, vec4 weights)
{
    float totalWeight = weights.x + weights.y + weights.z + weights.w;
    //totalWeight = 0;    
    if (totalWeight < 0.01)
        return normal;
    
    vec4 normalizedWeights = weights / totalWeight;
    
    mat4 skinMatrix = 
        Bones[int(joints.x)] * normalizedWeights.x +
        Bones[int(joints.y)] * normalizedWeights.y +
        Bones[int(joints.z)] * normalizedWeights.z +
        Bones[int(joints.w)] * normalizedWeights.w;
    
    return mat3(skinMatrix) * normal;
}

void main1( void )
{
  vec4 skinnedPosition = ApplySkinning(vec4(InPosition, 1.0), InJoints, InWeight);
  vec3 skinnedNormal = ApplySkinningToNormal(InNormal, InJoints, InWeight);
  gl_Position = matrWVP * skinnedPosition;
  OutPosition = vec3(matrW * skinnedPosition);
  OutNormal = normalize(mat3(transpose(inverse(matrW))) * skinnedNormal);

  //gl_Position = matrWVP * vec4(InPosition, 1);
  
  ////gl_Position = matrWVP * MatrRotateY(0 * Time) * vec4(InPosition + vec3(0, sin(InPosition.x + 5 * Time) + 10.30 * sin(3 * GlobalTime), 0), 1);
  //OutPosition = vec3(matrW * vec4(InPosition,1));
  OutTexture = InTexture;
  //OutNormal = normalize(mat3(transpose(inverse(matrW))) * InNormal);
  OutColor = InColor;
}

void main2( void )
{
  vec4 localPosition = vec4(InPosition, 1.0);
  
  vec4 skinnedLocalPosition = ApplySkinning(localPosition, InJoints, InWeight);
  
  vec4 worldPosition = matrW * skinnedLocalPosition;
  
  gl_Position = matrWVP * skinnedLocalPosition;
  
  OutPosition = worldPosition.xyz;
  
  vec3 skinnedNormal = ApplySkinningToNormal(InNormal, InJoints, InWeight);
  OutNormal = normalize(mat3(transpose(inverse(matrW))) * skinnedNormal);
  
  OutTexture = InTexture;
  OutColor = InColor;
}
 
void main( void )
{
  vec4 skinnedLocalPosition = ApplySkinning(vec4(InPosition, 1.0), InJoints, InWeight);
   
    float totalWeight = InWeight.x + InWeight.y + InWeight.z + InWeight.w;
    vec4 normalizedWeights = InWeight / totalWeight;
    
    mat4 skinMatrix = 
        Bones[InJoints.x] * normalizedWeights.x +
        Bones[InJoints.y] * normalizedWeights.y +
        Bones[InJoints.z] * normalizedWeights.z +
        Bones[InJoints.w] * normalizedWeights.w;
  gl_Position = (MatrVP * matrW * skinMatrix) * vec4(InPosition, 1);
   
  OutPosition = vec3(matrW * skinnedLocalPosition);
    
  vec3 skinnedNormal = ApplySkinningToNormal(InNormal, InJoints, InWeight);
  OutNormal = normalize(mat3(transpose(inverse(matrW))) * skinnedNormal);
  //OutNormal = vec3(0, 1, 0);
  OutTexture = InTexture;
  OutColor = InColor;
}