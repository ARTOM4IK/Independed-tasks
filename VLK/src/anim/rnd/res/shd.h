/*************************************************************
 * Copyright (C) 2025
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : shd.h
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

#ifndef __shd_h_
#define __shd_h_

#include "resources.h"
#include "def.h"

/* Amimation namespace */
namespace arvk
{
  /* Directory watcher class */
  class dir_watcher
  {
  private:
  // Overlapped structure for changing hook
  OVERLAPPED Ovr {};
  // Traching directory handle
  HANDLE hDir {};
  // Read directory changes data buffer
  BYTE Buffer[27 * 47] {};
  // Store path
  std::string Path;
 
  public:
  /* Start directory watching function.
   * ARGUMENTS:
   *   - directory path:
   *       const std::string &DirPath;
   * RETURNS: None.
   */
  VOID StartWatch( const std::string &DirPath );
  /* Stop directory watching function.
   * ARGUMENTS: None.
   * RETURNS: None.
   */
  VOID StopWatch( VOID );
  /* Check if directory is changed function.
   * ARGUMENTS: None.
   * RETURNS:
   *   (BOOL) TRUE if directory contents is changed (and subfolders).
   */
  BOOL IsChanged( VOID );
  }; /* End of 'dir_watcher' class */
 
  /* Shader class */
  class shader : public resource
  {
  friend class shader_manager;
  template<typename entry_type, typename index_type>
    friend class resource_manager;
  public:
  BOOL IsFree = FALSE;
  VkShaderModule ShaderModuleVert, ShaderModuleCtrl, ShaderModuleEval, ShaderModuleGeom, ShaderModuleFrag;
  /* Create shader function.
   * ARGUMENTS: None.
   * RETURNS:
   *   (UINT) shader id.
   */
  VOID Free( VOID );
  VOID Destroy( VOID );
  private:

  BOOL IsReload;
  /* Binary SPIR-V file load to memory function.
   * ARGUMENTS:
   *   - SPIR-V file name:
   *       const std::string &FileName;
   * RETURNS:
   *   (VkShaderModule) load shader module.
   */
  VkShaderModule LoadSPIRVFile( const std::string &FileName );
  /* Save text to log file function.
   * ARGUMENTS:
   *   - text 1 to save:
   *       const std::string &Stage;
   *   - text 2 to save:
   *       const std::string &Text;
   * RETURNS: None.
   */
  VOID Log( const std::string &Stage, const std::string &Text );
  /* Text file load to memory function.
   * ARGUMENTS:
   *   - file name:
   *       const std::string &FileName;
   * RETURNS:
   *   (std::string) load text.
   */
  std::string LoadTextFile( const std::string &FileName );
  /* Load shader function.
   * ARGUMENTS: None.
   * RETURNS:
   *   (shader &) self reference.
   */
  shader & Load( VOID );
 
  dir_watcher Watcher;  // Directory watcher handler
 
  public:
  std::string Name; // Shader name
  UINT ProgId;      // Shader program Id
 
  struct ATTR_INFO
  {
    std::string SType; // String type like shader
    INT Components;    // Number of components
    BOOL IsFloat;      // Float value flag (otherwise integer)
    INT MatrRows;      // For matrix number of rows
    INT Loc;           // Shader attribute location
  }; /* End of 'ATTR_INFO' structure */
 
  struct BLOCK_INFO
  {
    std::string SType; // String type like shader
    INT Index;         // Buffer block index
    INT Bind;          // Buffer bind point
  }; /* End of 'BLOCK_INFO' structure */
 
  // Attributes and uniforms information
  std::map<std::string, ATTR_INFO> Attributes, Uniforms;
  // Shader storage blocks informations (type, index, bind point)
  std::map<std::string, BLOCK_INFO> SSBOBuffers;

  shader( VOID ) 
  {
  } /* End of 'buffer' function */


  shader( render &rnd )
  {
    Rnd = &rnd;
  } /* End of 'shader' function */

  /* Class constructor.
    * ARGUMENTS:
    *   - shader prefix:
    *       const std::string &FileNamePrefix;
    */
  shader( const std::string &FileNamePrefix, render &rnd );

  /* Class destructor */
  ~shader( VOID )
  {
  } /* End of '~shader' function */
 
  /* Create shader function.
   * ARGUMENTS: None.
   * RETURNS:
   *   (UINT) shader id.
   */
  UINT Apply( VOID );
  /* Create shader function.
   * ARGUMENTS: None.
   * RETURNS: None.
   */
  VOID Update( VOID );
  /* Create shader function.
   * ARGUMENTS: None.
   * RETURNS: None.
   */
  VOID UpdateInfo( VOID );
  }; /* End of 'shader' class */
 
  /* Shader manager class */
  class shader_manager : public resource_manager<shader, std::string>
  {
  private:
  dir_watcher Watcher; // Directory watcher handler
  public:
  /* Create shader function.
   * ARGUMENTS:
   *   - shader file name prefix:
   *       const std::string &FileNamePrefix;
   * RETURNS:
   *   (shader *) created primitive interface.
   */
  shader * ShdCreate( const std::string &FileNamePrefix );
  /* Class constructor.
   * ARGUMENTS:
   *   - render instance reference:
   *       render &Rnd;
   */
  shader_manager( render &Rnd );

  /* Class destructor */
  ~shader_manager( void )
  {
    Watcher.StopWatch();
  } /* End of '~shader_manager' function */
  /* Create shader function.
   * ARGUMENTS:
   *   - shader file name prefix:
   *       const std::string &FileNamePrefix;
   * RETURNS: None.
   */
  VOID Update( VOID );
  /* Free shader function.
   * ARGUMENTS:
   *   - shader file name prefix:
   *       const std::string &FileNamePrefix;
   * RETURNS: None.
   */
  VOID ShdFree( shader *Shd )
  {
    resource_manager::Delete(Shd);
  } /* End of 'ShdFree' function */
  }; /* End of 'shader_manager' class */
} /* End of 'arvk' namespace */

#endif /* __shd_h_ */

/* END OF 'shd.h' FILE */
