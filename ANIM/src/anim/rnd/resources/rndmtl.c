/* FILE NAME: rndmtl.c
 * PROGRAMMER: AA4
 * LAST UPDATE: 29.01.2025
 * PURPOSE: 3D animation project.
 *          Material module.
 */

#include "anim/anim.h"
#include "rndres.h"

static struct
{
  char *Name;
  VEC amb, dif, spec;
  FLT shin;
} MatLib[] =
{
  {"Black Plastic", {0.0, 0.0, 0.0},             {0.01, 0.01, 0.01},           {0.5, 0.5, 0.5},               32},
  {"Brass",         {0.329412,0.223529,0.027451}, {0.780392,0.568627,0.113725}, {0.992157,0.941176,0.807843}, 27.8974},
  {"Bronze",        {0.2125,0.1275,0.054},       {0.714,0.4284,0.18144},       {0.393548,0.271906,0.166721},  25.6},
  {"Chrome",        {0.25, 0.25, 0.25},          {0.4, 0.4, 0.4},              {0.774597, 0.774597, 0.774597}, 76.8},
  {"Copper",        {0.19125,0.0735,0.0225},     {0.7038,0.27048,0.0828},      {0.256777,0.137622,0.086014},  12.8},
  {"Gold",          {0.24725,0.1995,0.0745},     {0.75164,0.60648,0.22648},    {0.628281,0.555802,0.366065},  51.2},
  {"Peweter",       {0.10588,0.058824,0.113725}, {0.427451,0.470588,0.541176}, {0.3333,0.3333,0.521569},      9.84615},
  {"Silver",        {0.19225,0.19225,0.19225},   {0.50754,0.50754,0.50754},    {0.508273,0.508273,0.508273},  51.2},
  {"Polished Silver", {0.23125,0.23125,0.23125}, {0.2775,0.2775,0.2775},       {0.773911,0.773911,0.773911},  89.6},
  {"Turquoise",     {0.1, 0.18725, 0.1745},      {0.396, 0.74151, 0.69102},    {0.297254, 0.30829, 0.306678}, 12.8},
  {"Ruby",          {0.1745, 0.01175, 0.01175},  {0.61424, 0.04136, 0.04136},  {0.727811, 0.626959, 0.626959}, 76.8},
  {"Polished Gold", {0.24725, 0.2245, 0.0645},   {0.34615, 0.3143, 0.0903},    {0.797357, 0.723991, 0.208006}, 83.2},
  {"Polished Bronze", {0.25, 0.148, 0.06475},    {0.4, 0.2368, 0.1036},        {0.774597, 0.458561, 0.200621}, 76.8},
  {"Polished Copper", {0.2295, 0.08825, 0.0275}, {0.5508, 0.2118, 0.066},      {0.580594, 0.223257, 0.0695701}, 51.2},
  {"Jade",          {0.135, 0.2225, 0.1575},     {0.135, 0.2225, 0.1575},      {0.316228, 0.316228, 0.316228}, 12.8},
  {"Obsidian",      {0.05375, 0.05, 0.06625},    {0.18275, 0.17, 0.22525},     {0.332741, 0.328634, 0.346435}, 38.4},
  {"Pearl",         {0.25, 0.20725, 0.20725},    {1.0, 0.829, 0.829},          {0.296648, 0.296648, 0.296648}, 11.264},
  {"Emerald",       {0.0215, 0.1745, 0.0215},    {0.07568, 0.61424, 0.07568},  {0.633, 0.727811, 0.633},       76.8},
  {"Black Plastic", {0.0, 0.0, 0.0},             {0.01, 0.01, 0.01},           {0.5, 0.5, 0.5},                32.0},
  {"Black Rubber",  {0.02, 0.02, 0.02},          {0.01, 0.01, 0.01},           {0.4, 0.4, 0.4},                10.0},
};
#define MAT_N (sizeof(MatLib) / sizeof(MatLib[0]))

aa4MATERIAL AA4_RndMaterials[AA4_MAX_MATERIALS]; /* Array of materials */
INT AA4_RndMaterialsSize = 0;                        /* Materials array size */

/* Experimental function! */

/* Load material from file function.
 * ARGUMENTS:
 *   None.
 * RETURNS:
 *   (aa4MATERIAL) Loaded material.
 */
/*aa4MATERIAL AA4_LoadMaterial( CHAR *FileName )
{
  FILE *F;
  CHAR Buf[10000];
  aa4MATERIAL Mtl;

  F = fopen(FileName, "rb");

  while (fgets(Buf, sizeof(Buf) - 1, F) != NULL)
  {
    
    if (Buf[0] == 'newmtl' && Buf[1] == ' ')
    {
      DBL x, y, z;
      sscanf(Buf + 2, "%lf %lf %lf", &x, &y, &z);
      Mtl.Name = ;
    } 
    if (Buf[0] == 'K' && Buf[1] == 'a' && Buf[2] == ' ')
    {
      DBL x, y, z;
      sscanf(Buf + 2, "%lf %lf %lf", &x, &y, &z);
      Mtl.Ka = VecSet(x, y, z);
    }
    else if (Buf[0] == 'K' && Buf[1] == 'd' && Buf[2] == ' ')
    {
      DBL x, y, z;
      sscanf(Buf + 2, "%lf %lf %lf", &x, &y, &z);
      Mtl.Kd = VecSet(x, y, z);
    }
    else if (Buf[0] == 'K' && Buf[1] == 's' && Buf[2] == ' ')
    {
      DBL x, y, z;
      sscanf(Buf + 2, "%lf %lf %lf", &x, &y, &z);
      Mtl.Ks = VecSet(x, y, z);
    }
    else if (Buf[0] == 'N' && Buf[1] == 's' && Buf[2] == ' ')
    {
      DBL x;
      sscanf(Buf + 2, "%lf", &x);
      Mtl.Ph = x;
    }
  }
  fclose(F);
  return Mtl;
} */ /* End of 'AA4_LoadMaterial' function */

/* Set default material function.
 * ARGUMENTS:
 *   None.
 * RETURNS:
 *   (aa4MATERIAL) Default material.
 */
aa4MATERIAL AA4_RndMtlGetDef( VOID )
{
  /*
  aa4MATERIAL def_mtl =
  {
    "Default",
    {0.1, 0.1, 0.1},
    {0.9, 0.9, 0.9},
    {0.3, 0.3, 0.3},
    30, 1,
    {-1, -1, -1, -1, -1, -1, -1, -1},
    0
  };
  */
  aa4MATERIAL def_mtl;
  INT i;

  strcpy(def_mtl.Name, MatLib[10].Name);
  def_mtl.Ka = MatLib[10].amb;
  def_mtl.Kd = MatLib[10].dif;
  def_mtl.Ks = MatLib[10].spec;
  def_mtl.Ph = MatLib[10].shin;
  for (i = 0; i < 8; i++)
    def_mtl.Tex[i] = -1;
  def_mtl.ShdNo = 0;
  return def_mtl;
} /* End of 'AA4_RndMtlGetDef' function */

/* Get material by number function.
 * ARGUMENTS:
 *   None.
 * RETURNS:
 *   (aa4MATERIAL) material.
 */
aa4MATERIAL * AA4_RndMtlGet( INT MtlNo )
{
  return &AA4_RndMaterials[MtlNo];
} /* End of 'AA4_RndMtlGet' function */

/* Get material from table by number function.
 * ARGUMENTS:
 *   None.
 * RETURNS:
 *   (aa4MATERIAL) material.
 */
aa4MATERIAL AA4_RndMtlGetFromTable( INT MtlNo )
{
  aa4MATERIAL mtl;
  INT i;

  strcpy(mtl.Name, MatLib[MtlNo].Name);
  mtl.Ka = MatLib[MtlNo].amb;
  mtl.Kd = MatLib[MtlNo].dif;
  mtl.Ks = MatLib[MtlNo].spec;
  mtl.Ph = MatLib[MtlNo].shin;
  for (i = 0; i < 8; i++)
    mtl.Tex[i] = -1;
  mtl.ShdNo = 0;
  return mtl;
} /* End of 'AA4_RndMtlGetFromTable' function */

/* Get material by name function.
 * ARGUMENTS:
 *   None.
 * RETURNS:
 *   (aa4MATERIAL) material.
 */
aa4MATERIAL * AA4_RndMtlGetByName( CHAR *MtlName )
{
  INT i;

  for (i = 0; i < AA4_RndMaterialsSize; i++)
    if (strcmp(MtlName, AA4_RndMaterials[i].Name) == 0)
      return &AA4_RndMaterials[i];

  return NULL;
} /* End of 'AA4_RndMtlGetByName' function */

/* Get number of material by name function.
 * ARGUMENTS:
 *   None.
 * RETURNS:
 *   (aa4MATERIAL) material.
 */
INT AA4_RndMtlGetNoByName( CHAR *MtlName )
{
  INT i;

  for (i = 0; i < AA4_RndMaterialsSize; i++)
    if (strcmp(MtlName, AA4_RndMaterials[i].Name) == 0)
      return i;

  return 0;
} /* End of 'AA4_RndMtlGetNoByName' function */

/* Add material function.
 * ARGUMENTS:
 *   - pointer to material:
 *       aa4MATERIAL *Mtl;
 * RETURNS:
 *   (INT) Number of materials.
 */
INT AA4_RndMtlAdd( aa4MATERIAL *Mtl )
{
     if (AA4_RndMaterialsSize >= AA4_MAX_SHADERS)
    return 0;
  AA4_RndMaterials[AA4_RndMaterialsSize] = *Mtl;

  Mtl->UBONo = AA4_RndUBOCreate("Material UBO", AA4_RND_UBO_BIND_MATERIAL, sizeof(aa4RND_UBO_MTL), &AA4_UboMtl);

  return AA4_RndMaterialsSize++;
} /* End of 'AA4_RndPrimFree' function */

/* Material initializate function.
 * ARGUMENTS:
 *   None.
 * RETURNS:
 *   (VOID) Nothing.
 */
VOID AA4_RndMtlInit( VOID )
{
  /*
  aa4MATERIAL def = AA4_RndMtlGetDef();
  aa4MATERIAL mtl;
  */
  AA4_RndMaterialsSize = 0;
  /*AA4_RndMtlAdd(&def);*/

  /*mtl = AA4_RndMtlGetDef();
  mtl.ShdNo = AA4_RndShdAdd("samples");
  mtl.Tex[0] = AA4_RndTexAddFromFile("bin/textures/M.G24");
  AA4_RndMtlAdd(&mtl);*/

} /* End of 'AA4_RndMtlInit' function 

/* Material deinitializate function.
 * ARGUMENTS:
 *   - pointer to primitive to load:
 *       aa4PRIM *Pr;
 *   - world matrix:
 *       MATR World;
 * RETURNS:
 *   (VOID) Nothing.
 */
VOID AA4_RndMtlClose( VOID )
{
  AA4_RndMaterialsSize = 0;
} /* End of 'AA4_RndMtlClose' function */

/* Apply material on object function.
 * ARGUMENTS:
 *   - pointer to primitive to load:
 *       aa4PRIM *Pr;
 *   - world matrix:
 *       MATR World;
 * RETURNS:
 *   (VOID) Nothing.
 */
INT AA4_RndMtlApply( INT MtlNo )
{
  INT prg, loc, i;
  aa4MATERIAL *mtl;
 
  /* Set material pointer */
  if (MtlNo < 0 || MtlNo >= AA4_RndMaterialsSize)
    MtlNo = 0;
  mtl = &AA4_RndMaterials[MtlNo];
 
  /* Set shader program Id */
  prg = mtl->ShdNo;
  if (prg < 0 || prg >= AA4_RndShadersSize)
    prg = 0;
  prg = AA4_RndShaders[prg].ProgId;
 
  if (prg == 0)
    return 0;
 
  glUseProgram(prg);
 
  AA4_RndUBOApply(mtl->UBONo);
/*
  if ((loc = glGetUniformLocation(prg, "Time")) != -1)
    glUniform1f(loc, AA4_Anim.Time);
  if ((loc = glGetUniformLocation(prg, "GlobalTime")) != -1)
    glUniform1f(loc, AA4_Anim.GlobalTime);

  if ((loc = glGetUniformLocation(prg, "Ka")) != -1)
    glUniform3fv(loc, 1, &mtl->Ka.X);
  if ((loc = glGetUniformLocation(prg, "Kd")) != -1)
    glUniform3fv(loc, 1, &mtl->Kd.X);
  if ((loc = glGetUniformLocation(prg, "Ks")) != -1)
    glUniform3fv(loc, 1, &mtl->Ks.X);
  if ((loc = glGetUniformLocation(prg, "Ph")) != -1)
    glUniform1f(loc, mtl->Ph);
  if ((loc = glGetUniformLocation(prg, "Trans")) != -1)
    glUniform1f(loc, mtl->Trans);
*/ 
  /* Set textures */
  for (i = 0; i < 8; i++)
  {
    CHAR tname[] = "IsTexture0";  /*--> shader: uniform bool IsTexture2;*/
 
    tname[9] = '0' + i;
    if (mtl->Tex[i] != -1)
    {
      glActiveTexture(GL_TEXTURE0 + i);
      glBindTexture(GL_TEXTURE_2D, AA4_RndTextures[mtl->Tex[i]].TexId);
    }
    if ((loc = glGetUniformLocation(prg, tname)) != -1)
      glUniform1i(loc, mtl->Tex[i] != -1);
  }

  glBindBufferBase(GL_UNIFORM_BUFFER, 1, mtl->BufId);
  return prg;
} /* End of 'AA4_RndMtlApply' function */

/* END OF 'rndmtl.c' FILE */
