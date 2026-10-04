/*************************************************************
 * Copyright (C) 2025
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : shd.cpp
 * PURPOSE     : Ray Tracing project.
 *               Precompiled header definition module.
 * PROGRAMMER  : CGSG-SummerCamp'2025.
 *               Artmey V. Arsentev.
 * LAST UPDATE : 23.07.2025.
 * NOTE        : Module namespace 'virt'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#include "arvk.h"

extern const CHAR CommonShaderIncludes[];

arvk::shader::shader( const std::string &FileNamePrefix, render &rnd ): Name(FileNamePrefix)
{
  Rnd = &rnd;
  Watcher.StopWatch();
  Watcher.StartWatch(/*anim::Path + */"bin/shaders/" + Name);
} /* End of 'shader' function */

arvk::shader_manager::shader_manager( render &Rnd ) : resource_manager(Rnd)
{
  Watcher.StartWatch(/*anim::Path + */"bin/shaders");
} /* End of 'shader_manager' function */

/* Save text to log file function.
 * ARGUMENTS:
 *   - text 1 to save:
 *       const std::string &Stage;
 *   - text 2 to save:
 *       const std::string &Text;
 * RETURNS: None.
 */
VOID arvk::shader::Log( const std::string &Stage, const std::string &Text )
{
 std::ofstream(/* anim::Path + */ "bin/shaders/~SHD{AA4}30.LOG", std::ios_base::app) << Name << "\n" << Stage << ":\n" << Text << "\n";
} /* End of 'vigl::shader::Log' function */
 
 
/* Text file load to memory function.
 * ARGUMENTS:
 *   - file name:
 *       const std::string &FileName;
 * RETURNS:
 *   (std::string) load text.
 */
std::string arvk::shader::LoadTextFile( const std::string &FileName )
{
  std::ifstream f(/*anim::Path + */FileName);
 
  return std::string((std::istreambuf_iterator<char>(f)),
                     std::istreambuf_iterator<char>());
} /* End of 'vigl::shader::LoadTextFile' function */
 
/* Binary SPIR-V file load to memory function.
 * ARGUMENTS:
 *   - SPIR-V file name:
 *       const std::string &FileName;
 * RETURNS:
 *   (VkShaderModule) load shader module.
 */
VkShaderModule arvk::shader::LoadSPIRVFile( const std::string &FileName )
{
  std::ifstream f(/* anim::Path + */ FileName, std::ios::binary | std::ios::in);

  if (!f.is_open())
    return VK_NULL_HANDLE;
  f.seekg(0, std::ios::end);
  UINT flen = static_cast<UINT>(f.tellg());
  f.seekg(0, std::ios::beg);
  std::vector<UINT32> code;
  code.resize(flen / 4);
  f.read((CHAR *)code.data(), flen);
  f.close();
  static const UINT32 SPIRV_MAGIC = 0x07230203;
  if (code.size() == 0 || code[0] != SPIRV_MAGIC || flen % 4 != 0)
    return VK_NULL_HANDLE;
  VkShaderModuleCreateInfo ShaderModuleCreateInfo
  {
    .sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO,
    .codeSize = flen,
    .pCode = code.data(),
  };
  VkShaderModule ShaderModule {};
  vkCreateShaderModule(Rnd->Device, &ShaderModuleCreateInfo, nullptr, &ShaderModule);
  return ShaderModule;
} /* End of 'LoadSPIRVFile' function */

static const CHAR CommonShaderIncludes[] =
R"separator(

#version 460

layout(std140, binding = 0) buffer Camera
{
  mat4 MatrView;
  mat4 MatrProj;
  mat4 MatrVP;
  vec4 CamLocFrameW;
  vec4 CamDirProjDist;
  vec4 CamRightWp;
  vec4 CamUpHp;
  vec4 CamAtFrameH;
};

layout(std140, binding = 1) buffer Syncronization
{
  vec4 SyncGlobalTimeGlobalDeltaTimeTimeDeltaTime;
  vec4 SyncFPSIsPause;
};
#define Time SyncGlobalTimeGlobalDeltaTimeTimeDeltaTime.z

layout(std140, binding = 2) buffer Primitive
{
  mat4 MatrWVP;
  mat4 MatrW;
  mat4 MatrWInvTrans;
  vec4 RndIsWireIsAny;
  bool TextureFlags[8];
};

layout(std140, binding = 3) buffer Material
{
  vec4 Ka;
  vec4 KdTrans;
  vec4 KsPh;
};

layout(std140, binding = 5) buffer Noise
{
  mat4 Tab[1024];
};

)separator";

/* Load shader function.
 * ARGUMENTS: None.
 * RETURNS:
 *   (shader &) self reference.
 */
arvk::shader & arvk::shader::Load( VOID )
{
  struct
  {
    std::string Suff; // Shader file name
    VkShaderModule &Module;
    std::string CompilerParam; // Shader file name
  } shdr[] =
  {
    {"vert", ShaderModuleVert, "vert"},
    {"ctrl", ShaderModuleCtrl, "tesc"},
    {"eval", ShaderModuleEval, "tese"},
    {"geom", ShaderModuleGeom, "geom"},
    {"frag", ShaderModuleFrag, "frag"},
  };
  BOOL isok = TRUE;

  /* Load shaders */
  for (auto &s : shdr)
  {
    std::string fn = "bin/shaders/" + Name + "/" + s.Suff; // + ".glsl";
    std::fstream f(fn + ".glsl");
    /* Check for text file presence */
    if (!f.is_open())
      if (s.Suff != "vert" && s.Suff != "frag")
        continue;
      else
      {
        Log(s.Suff, "No file");
        isok = FALSE;
        break;
      }
    f.close();

    // Compile shader
    std::string cmd = "glslc -Ibin/shaders/include -fshader-stage=" + s.CompilerParam + " -o " + fn + ".spv " + fn + ".glsl 2> compile.log";
    std::system(cmd.c_str());

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x1E); 
    std::cout << "Recompile shader:";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07); 
    std::cout << " Shader: ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0E); 
    std::cout << "[" + Name + "] ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0B); 
    std::cout << s.Suff + "\n";


    // Check for errors
    std::string err = LoadTextFile("compile.log");
    std::remove("compile.log");
    if (err != "")
    {
      Log(s.Suff, "Compile errors:\n" + err);
      isok = FALSE;
      SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x4E); 
      std::cout << "Compile errors:";
      SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07); 
      std::cout << " Shader: ";
      SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0E); 
      std::cout << "[" + Name + "] ";
      SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0B); 
      std::cout << s.Suff + "\n";
      SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0F); 
      std::cout << err << std::endl;
      //break;
    }

    // Load shader copiled SPIR-V byte code
    if ((s.Module = LoadSPIRVFile(fn + ".spv")) == VK_NULL_HANDLE)
      if (s.Suff != "vert" && s.Suff != "frag")
        continue;
      else
      {
        Log(s.Suff, "SPIR-V load error");
        isok = FALSE;
        break;
      }
  }

  IsReload = TRUE;

  if (!isok)
    for (auto s : shdr)
      if (s.Module != VK_NULL_HANDLE)
        vkDestroyShaderModule(Rnd->Device, s.Module, nullptr), s.Module = VK_NULL_HANDLE;
  return *this;
} /* End of 'arvk::shader & arvk::shader::Load' function */

/* Update shader function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID arvk::shader::Update( VOID )
{
  if (Watcher.IsChanged())
  {
    Free();
    Load();
    Watcher.StartWatch("bin/shaders/" + Name);
  }
} /* End of 'arvk::shader::Update' function */

/* Apply shader function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
UINT arvk::shader::Apply( VOID )
{
  //glUseProgram(ProgId);
  //return ProgId;
  return 0;
} /* End of 'Apply' function */

/* Create shader function.
 * ARGUMENTS:
 *   - shader file name prefix:
 *       const std::string &FileNamePrefix;
 * RETURNS:
 *   (shader *) created primitive interface.
 */
arvk::shader * arvk::shader_manager::ShdCreate( const std::string &FileNamePrefix )
{
  return resource_manager::Add(shader(FileNamePrefix, RndRef).Load());
} /* End of 'ShdCreate' function */

/* Update all shaders in stock function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID arvk::shader_manager::Update( VOID )
{
  if (Watcher.IsChanged())
  {
    for (auto &shd : Stock)
      shd.second.Update();
    Watcher.StartWatch(anim::Path + "bin/shaders/");

    shader *Shd = Find("test");
    RndRef.DestroyPipeline(RndRef.Device);    
    RndRef.CreatePipeline(RndRef.Device, RndRef.RenderPass, Shd, RndRef.ClampedW, RndRef.ClampedH);
  }
} /* End of 'Update' function */

/* Update shader information function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID arvk::shader::UpdateInfo( VOID )
{
  // Map of OpenGL attribute types
  static std::map<INT, std::tuple<std::string, INT, BOOL, INT>> attr_types
  {
    //{GL_BOOL, {"bool", 1, FALSE, 0}},
    //{GL_BOOL_VEC2, {"bvec2", 1, FALSE, 0}},
    //{GL_BOOL_VEC3, {"bvec3", 1, FALSE, 0}},
    //{GL_BOOL_VEC4, {"bvec4", 1, FALSE, 0}},
    //{GL_SAMPLER_1D, {"sampler1D", 1, FALSE, 0}},
    //{GL_SAMPLER_2D, {"sampler2D", 1, FALSE, 0}},
    //{GL_SAMPLER_3D, {"sampler3D", 1, FALSE, 0}},
    //{GL_SAMPLER_CUBE, {"samplerCube", 1, FALSE, 0}},
    //{GL_SAMPLER_1D_SHADOW, {"sampler1dShadow", 1, FALSE, 0}},
    //{GL_SAMPLER_2D_SHADOW, {"sampler1dShadow", 1, FALSE, 0}},
    //{GL_FLOAT, {"float", 1, TRUE, 0}},
    //{GL_FLOAT_VEC2, {"vec2", 2, TRUE, 0}},
    //{GL_FLOAT_VEC3, {"vec3", 3, TRUE, 0}},
    //{GL_FLOAT_VEC4, {"vec4", 4, TRUE, 0}},
    //{GL_FLOAT_MAT2, {"mat2", 4, TRUE, 2}},
    //{GL_FLOAT_MAT3, {"mat3", 9, TRUE, 3}},
    //{GL_FLOAT_MAT4, {"mat4", 16, TRUE, 4}},
    //{GL_FLOAT_MAT2x3, {"mat2x3", 6, TRUE, 2}},
    //{GL_FLOAT_MAT2x4, {"mat2x4", 8, TRUE, 2}},
    //{GL_FLOAT_MAT3x2, {"mat3x2", 6, TRUE, 3}},
    //{GL_FLOAT_MAT3x4, {"mat3x4", 12, TRUE, 3}},
    //{GL_FLOAT_MAT4x2, {"mat4x2", 8, TRUE, 4}},
    //{GL_FLOAT_MAT4x3, {"mat4x3", 12, TRUE, 4}},
    //{GL_INT, {"int", 1, FALSE, 0}},
    //{GL_INT_VEC2, {"ivec2", 2, FALSE, 0}},
    //{GL_INT_VEC3, {"ivec3", 3, FALSE, 0}},
    //{GL_INT_VEC4, {"ivec4", 4, FALSE, 0}},
    //{GL_UNSIGNED_INT, {"uint", 1, FALSE, 0}},
    //{GL_UNSIGNED_INT_VEC2, {"uvec2", 2, FALSE, 0}},
    //{GL_UNSIGNED_INT_VEC3, {"uvec3", 3, FALSE, 0}},
    //{GL_UNSIGNED_INT_VEC4, {"uvec4", 4, FALSE, 0}},
  };
 
  // <functional>
  //std::vector<std::tuple<INT,
  //                       std::function<INT( INT, const CHAR * )>,
  //                       std::function<VOID( UINT, UINT, INT, INT *, INT *,
  //                                           GLenum *, CHAR * )>,
  //                       std::map<std::string, ATTR_INFO>&>> attr_data
  //{
  //  {GL_ACTIVE_ATTRIBUTES, glGetAttribLocation, glGetActiveAttrib, Attributes},
  //  {GL_ACTIVE_UNIFORMS, glGetUniformLocation, glGetActiveUniform, Uniforms},
  //};
  // Fill shader attributes/uniforms info
  //for (auto d : attr_data)
  //{
  //  INT Count;
  //  glGetProgramiv(ProgId, std::get<0>(d), &Count);
 
  //  std::get<3>(d).clear();
  //  for (INT i = 0; i < Count; i++)
  //  {
  //    CHAR name[300];
  //    INT size;
  //    GLenum type;
  //    std::get<2>(d)(ProgId, i, sizeof(name), nullptr, &size, &type, name);
  //    auto attr_info = attr_types[type];
  //    INT loc = std::get<1>(d)(ProgId, name);
 
  //    std::get<3>(d)[name] =
  //    {
  //      std::get<0>(attr_info),
  //      std::get<1>(attr_info),
  //      std::get<2>(attr_info),
  //      std::get<3>(attr_info),
  //      loc
  //    };
  //  }
  //}
  //INT CountSSBO;
  //glGetProgramInterfaceiv(ProgId, GL_SHADER_STORAGE_BLOCK, GL_ACTIVE_RESOURCES,
  //                        &CountSSBO);
  //SSBOBuffers.clear();
  //for (INT i = 0; i < CountSSBO; i++)
  //{
  //  CHAR name[300];
  //  glGetProgramResourceName(ProgId, GL_SHADER_STORAGE_BLOCK, i, sizeof(name),
  //                           nullptr, name);
  //  INT idx = glGetProgramResourceIndex(ProgId, GL_SHADER_STORAGE_BLOCK, name);
  //  GLenum prop[] {GL_BUFFER_BINDING};
  //  INT bind;
  //  glGetProgramResourceiv(ProgId, GL_SHADER_STORAGE_BLOCK, idx,
  //    1, prop, 1, nullptr, &bind);
  //  SSBOBuffers[name] = {name, idx, bind};
  //}
} /* End of 'arvk::shader::UpdateInfo' function */

/* Start directory watching function.
  * ARGUMENTS:
  *   - directory path:
  *       const std::string &DirPath;
  * RETURNS: None.
  */
VOID arvk::dir_watcher::StartWatch( const std::string &DirPath )
{
  StopWatch();
  ZeroMemory(&Ovr, sizeof(OVERLAPPED));
  Path = DirPath;
 
  // Open directory
  hDir =
    CreateFile(DirPath.c_str(),
      FILE_LIST_DIRECTORY,
      FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
      nullptr, OPEN_EXISTING,
      FILE_FLAG_BACKUP_SEMANTICS | FILE_FLAG_OVERLAPPED,
      nullptr);
 
  // Start monitoring
  Ovr.hEvent = CreateEvent(nullptr, FALSE, FALSE, nullptr);
 
  ReadDirectoryChangesW(hDir,
    Buffer, sizeof(Buffer),
    TRUE,
    FILE_NOTIFY_CHANGE_LAST_WRITE | FILE_NOTIFY_CHANGE_CREATION |
      FILE_NOTIFY_CHANGE_FILE_NAME,
    nullptr,
    &Ovr,
    nullptr);
} /* End of 'StartWatch' function */
 
/* Stop directory watching function.
  * ARGUMENTS: None.
  * RETURNS: None.
  */
VOID arvk::dir_watcher::StopWatch( VOID )
{
  if (Ovr.hEvent != nullptr)
    CloseHandle(Ovr.hEvent);
  if (hDir != nullptr)
    CloseHandle(hDir);
 
  ZeroMemory(&Ovr, sizeof(OVERLAPPED));
  hDir = nullptr;
  Path = "";
} /* End of 'StopWatch' function */
 
/* Check if directory is changed function.
  * ARGUMENTS: None.
  * RETURNS:
  *   (BOOL) TRUE if directory contents is changed (and subfolders).
  */
BOOL arvk::dir_watcher::IsChanged( VOID )
{
  if (Ovr.hEvent == nullptr || hDir == nullptr)
    return FALSE;
 
  INT id = WaitForSingleObject(Ovr.hEvent, 0);
  if (id == WAIT_OBJECT_0)
  {
    // Restart monitoring
    ResetEvent(Ovr.hEvent);
    ReadDirectoryChangesW(hDir,
      Buffer, sizeof(Buffer),
      TRUE,
      FILE_NOTIFY_CHANGE_LAST_WRITE | FILE_NOTIFY_CHANGE_CREATION |
        FILE_NOTIFY_CHANGE_FILE_NAME,
      nullptr,
      &Ovr,
      nullptr);
    return TRUE;
  }
  return FALSE;
} /* End of 'IsChanged' function */

/* Free shader function.
 * ARGUMENTS: None.
 * RETURNS:
 *   (VOID) None.
 */
VOID arvk::shader::Free( VOID )
{
  if (IsFree == FALSE)
    IsFree = TRUE;
  else
    return;
  struct
  {
    VkShaderModule &Mod;
  } Modules[] =
  {
    {ShaderModuleVert},
    //{ShaderModuleCtrl},
    //{ShaderModuleEval},
    //{ShaderModuleGeom},
    {ShaderModuleFrag},
  };
  Watcher.StopWatch();
  for (auto shd : Modules)
    if (shd.Mod != VK_NULL_HANDLE)
      vkDestroyShaderModule(Rnd->Device, shd.Mod, nullptr), shd.Mod = VK_NULL_HANDLE;
} /* End of 'Free' function */

/* Free shader function.
 * ARGUMENTS: None.
 * RETURNS:
 *   (VOID) None.
 */
VOID arvk::shader::Destroy( VOID )
{
  struct
  {
    VkShaderModule &Mod;
  } Modules[] =
  {
    {ShaderModuleVert},
    //{ShaderModuleCtrl},
    //{ShaderModuleEval},
    //{ShaderModuleGeom},
    {ShaderModuleFrag},
  };
  Watcher.StopWatch();
  for (auto shd : Modules)
    if (shd.Mod != VK_NULL_HANDLE)
      vkDestroyShaderModule(Rnd->Device, shd.Mod, nullptr), shd.Mod = VK_NULL_HANDLE;
} /* End of 'Free' function */

/* END OF 'shd.cpp' FILE */
