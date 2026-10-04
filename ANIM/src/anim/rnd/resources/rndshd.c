/* FILE NAME: rndshd.c
 * PROGRAMMER: AA4
 * LAST UPDATE: 29.01.2025
 * PURPOSE: 3D animation project.
 *          Shader module.
 */

#include "rndres.h"
#include <stdio.h>
#include <string.h>

aa4SHADER AA4_RndShaders[AA4_MAX_SHADERS]; /* Array of shaders */
INT AA4_RndShadersSize;                    /* Shadres array store size */

/* Loads text from file function.
 * ARGUMENTS:
 *   - file name to be load from:
 *       CHAR *FileName;
 * RETURNS:
 *   (CHAR *) load text (allocated through malloc).
 */
static CHAR * AA4_RndShdLoadTextFromFile( CHAR *FileName )
{
  FILE *F;
  CHAR *txt;
  int flen;

  if ((F = fopen(FileName, "rb")) == NULL)
    return NULL;
  fseek(F, 0, SEEK_END);
  flen = ftell(F);
  rewind(F);
  if ((txt = malloc(flen + 1)) == NULL)
  {
    fclose(F);
    return NULL;
  }
  memset(txt, 0, flen + 1);
  fread(txt, 1, flen, F);
  fclose(F);
  return txt;
} /* End of 'AA4_RndShdLoadTextFromFile' function */

/* Store log to file function.
 * ARGUMENTS:
 *   - message file prefix, shader name and text:
 *       CHAR *Prefix, *Type, *Text;
 * RETURNS:
 *   None.
 */
static VOID AA4_RndShdLog( CHAR *Prefix, CHAR *Type, CHAR *Text )
{
  FILE *F;
  if ((F = fopen("bin/shaders/AA4{30}SHD.LOG", "a")) == NULL)
    return;
  fprintf(F, "%s/%s.GLSL:\n%s\n", Prefix, Type, Text);
  fclose(F);
} /* End of 'AA4_RndShdLog' function */

/* Load shader program from .GLSL files function.
 * ARGUMENTS:
 *   - shader file path to load (path\***.glsl):
 *       CHAR *ShaderFileNamePrefix;
 * RETURNS:
 *   (INT) load shader program Id.
 */
INT AA4_RndShdLoad( CHAR *ShaderFileNamePrefix )
{ /*
  INT i, prg = 0, res, Ns = sizeof(shd) / sizeof(shd[0]);
  CHAR *txt;
  BOOL is_ok = TRUE;
  static CHAR Buf[3000];
*/
  BOOL is_ok = TRUE;
  CHAR *txt[AA4_MAX_SHADER_FILES], *chr_pos;
  INT prg = 0, txt_size = 0, txt_common_size = 0, bufline_size = 0;

  struct
  {
    CHAR *Name;      /* Shader file name */
    INT Type;        /* Shader type (see GL_***_SHADER) */
    CHAR *Define;    /* SHader version and type define */
    INT Id;          /* Result shader OpenGL Id */
  } shds[] =
  {
    {"vert", GL_VERTEX_SHADER, "#version 460\n#define VERTEX_SHADER 1\n"},
    {"frag", GL_FRAGMENT_SHADER, "#version 460\n#define FRAGMENT_SHADER 1\n"},
    {"geom", GL_GEOMETRY_SHADER, "#version 460\n#define GEOMETRY_SHADER 1\n"},
    {"ctrl", GL_TESS_CONTROL_SHADER, "#version 460\n#define TESS_CONTROL_SHADER 1\n"},
    {"eval", GL_TESS_EVALUATION_SHADER, "#version 460\n#define TESS_EVALUATION_SHADER 1\n"},
  };

  INT i, res, NoofS = sizeof(shds) / sizeof(shds[0]);
  static CHAR Buf[3000], Buf1[300], BufLine[AA4_MAX_SHADER_FILES / 2][102];

  /* skip '#version' line */
  txt_size++;

  /* load 'commondg.glsl' */
  if ((txt[txt_size + 1] = AA4_RndShdLoadTextFromFile("bin/shaders/includes/commondf.glsl")) != NULL)
  {
    txt[txt_size++] = "#line 1 \"commondf.glsl\"\n";
    txt_size++;
  }

  /* Load local 'incl.glsl' files */
  chr_pos = ShaderFileNamePrefix;
  do
  {
    chr_pos = strchr(chr_pos, '/');
    strcpy(Buf1, ShaderFileNamePrefix);
    if (chr_pos != NULL)
      Buf1[chr_pos++ - ShaderFileNamePrefix] = 0;
    sprintf(Buf, "bin/shaders/%s/incl.glsl", Buf1);
    if ((txt[txt_size + 1] = AA4_RndShdLoadTextFromFile(Buf)) != NULL)
    {
      sprintf(BufLine[bufline_size], "\n#line 1 \"%s/incl.glsl\"\n", Buf1);
      txt[txt_size++] = BufLine[bufline_size++];
      txt_size++;
    }
  } while (chr_pos != NULL);

  for (i = 0; i < NoofS; i++)
  {
    txt[0] = shds[i].Define;
    /* Load file */
    sprintf(Buf, "bin/shaders/%s/%s.glsl", ShaderFileNamePrefix, shds[i].Name);
    txt[txt_size + 1] = AA4_RndShdLoadTextFromFile(Buf);
    sprintf(Buf, "\n#line 1 \"%s/%s.glsl\"\n", ShaderFileNamePrefix, shds[i].Name);
    txt[txt_size] = Buf;
    if (txt[txt_size + 1] == NULL)
    {
      if (i >= 2)
        continue;
      AA4_RndShdLog(ShaderFileNamePrefix, shds[i].Name, "Error load file");
      is_ok = FALSE;
      break;
    }
    /* Create shader */
    if ((shds[i].Id = glCreateShader(shds[i].Type)) == 0)
    {
      AA4_RndShdLog(ShaderFileNamePrefix, shds[i].Name, "Error create shader");
      free(txt[txt_size + 1]);
      is_ok = FALSE;
      break;
    }
    /* Send text to shader to compile */
    glShaderSource(shds[i].Id, txt_size + 2, txt, NULL);
    free(txt[txt_size + 1]);
    /* Compiler shader */
    glCompileShader(shds[i].Id);
    glGetShaderiv(shds[i].Id, GL_COMPILE_STATUS, &res);
    if (res != 1)
    {
      glGetShaderInfoLog(shds[i].Id, sizeof(Buf), &res, Buf);
      AA4_RndShdLog(ShaderFileNamePrefix, shds[i].Name, Buf);
      is_ok = FALSE;
      break;
    }
  }
  if (is_ok)
  {
    if ((prg = glCreateProgram()) == 0)
    {
      is_ok = FALSE;
      AA4_RndShdLog(ShaderFileNamePrefix, "PROG", "Error create program");
    }
    else
    {
      /* Attach shaders to program */
      for (i = 0; i < NoofS; i++)
        if (shds[i].Id != 0)
          glAttachShader(prg, shds[i].Id);
      /* Link shader program */
      glLinkProgram(prg);
      glGetProgramiv(prg, GL_LINK_STATUS, &res);
      if (res != 1)
      {
        glGetProgramInfoLog(prg, sizeof(Buf), &res, Buf);
        AA4_RndShdLog(ShaderFileNamePrefix, "PROG", Buf);
        is_ok = FALSE;
      }
    }
  }
  /* Error handle */
  if (!is_ok)
  {
    /* Remove all shaders */
    for (i = 0; i < NoofS; i++)
      if (shds[i].Id != 0)
      {
        if (prg != 0)
          glDetachShader(prg, shds[i].Id);
        glDeleteShader(shds[i].Id);
      }
    /* Remove program */
    if (prg != 0)
      glDeleteProgram(prg);
    prg = 0;
  }
  return prg;
} /* End of 'AA4_RndShdLoad' function */

/* Unload shader program fropm memory files function.
 * ARGUMENTS:
 *   - shader program Id:
 *       INT ProgId;
 * RETURNS:
 *   None.
 */
VOID AA4_RndShdDelete( INT ProgId )
{
  INT shdrs[5], n, i;

  if (ProgId == 0 || ! glIsProgram(ProgId))
    return;
  glGetAttachedShaders(ProgId, 5, &n, shdrs);
  for (i = 0; i < n; i++)
    if(glIsShader(shdrs[i]))
      {
      glDetachShader(ProgId, shdrs[i]);
      glDeleteShader(shdrs[i]);
    }
  glDeleteProgram(ProgId);
} /* End of 'AA4_RndShdDelete' function */

/* Add shader to stock from file function.
 * ARGUMENTS:
 *   - shader file path to load:
 *       CHAR *ShaderFileNamePrefix;
 * RETURNS:
 *   (INT) new shader stock number.
 */
INT AA4_RndShdAdd( CHAR *ShaderFileNamePrefix )
{
  INT i;
 
  /* Look for existed shader */
  for (i = 0; i < AA4_RndShadersSize; i++)
    if (strcmp(ShaderFileNamePrefix, AA4_RndShaders[i].Name) == 0)
      return i;
 
  /* Add a new one */
  if (AA4_RndShadersSize >= AA4_MAX_SHADERS)
    return 0;
  strncpy(AA4_RndShaders[AA4_RndShadersSize].Name, ShaderFileNamePrefix,
          AA4_STR_MAX - 1);
  AA4_RndShaders[AA4_RndShadersSize].ProgId =
    AA4_RndShdLoad(ShaderFileNamePrefix);
  return AA4_RndShadersSize++;
}
 
/* Shader storage initialize function.
 * ARGUMENTS:
 *   None.
 * RETURNS:
 *   None.
 */
VOID AA4_RndShdInit( VOID )
{
  AA4_RndShadersSize = 0;
  AA4_RndShdAdd("default");
} /* End of 'AA4_RndShdInit' function */

/* Shader storage deinitialize function.
 * ARGUMENTS:
 *   None.
 * RETURNS:
 *   None.
 */
VOID AA4_RndShdClose( VOID )
{
  INT i;
 
  for (i = 0; i < AA4_RndShadersSize; i++)
    AA4_RndShdDelete(AA4_RndShaders[i].ProgId);
  AA4_RndShadersSize = 0;
} /* End of 'AA4_RndShdClose' function */

/* Update from file all load shaders function.
 * ARGUMENTS:
 *   None.
 * RETURNS:
 *   None.
 */
VOID AA4_RndShdUpdate( VOID )
{
  INT i;

  for (i = 0; i < AA4_RndShadersSize; i++)
  {
    AA4_RndShdDelete(AA4_RndShaders[i].ProgId);
    AA4_RndShaders[i].ProgId =
      AA4_RndShdLoad(AA4_RndShaders[i].Name);
  }
} /* End of 'AA4_RndShdUpdate' function */

/* END OF 'rndshd.c' FILE */
