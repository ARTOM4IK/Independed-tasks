/* FILE NAME: rndubo.c
 * PROGRAMMER: AA4
 * LAST UPDATE: 22.01.2025
 * PURPOSE: 3D animation project.
 *          UBO module.
*/

#include "rndres.h"
#include "anim/anim.h"

aa4UBO AA4_RndUBOs[AA4_MAX_UBOS]; /* Array of UBO */
INT AA4_RndUBOsSize;              /* UBO array store size */

/* UBO handle initialization function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID AA4_RndUBOInit( VOID )
{
  AA4_RndUBOsSize = 0;
} /* End of 'AA4_RndUBOInit' function */
 
/* UBO handle deinitialization function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID AA4_RndUBOClose( VOID )
{
  INT i;
 
  for (i = 0; i < AA4_RndUBOsSize; i++)
    glDeleteBuffers(1, &AA4_RndUBOs[i].UBOId);
  AA4_RndUBOsSize = 0;
} /* End of 'AA4_RndUBOClose' function */
 
/* Add UBO to stock function.
 * ARGUMENTS:
 *   - UBO name:
 *       CHAR *Name;
 *   - OpenGL UBO bind point:
 *       UINT BindPoint;
 *   - UBO size in bytes:
 *       INT Size;
 *   - UBO data:
 *       VOID *Bits;
 * RETURNS:
 *   (INT) UBO stock number (-1 if error is occured).
 */
INT AA4_RndUBOCreate( CHAR *Name, UINT BindPoint, INT Size, VOID *Bits )
{
  if (AA4_RndUBOsSize >= AA4_MAX_UBOS)
    return -1;
 
  /* Setup OpenGL UBO */
  /* Size = COM_MAX(Size, 16); */
  /* !!! Size = (Size + 15) >> 4 << 4; - alignment to 16 bytes */
  glGenBuffers(1, &AA4_RndUBOs[AA4_RndUBOsSize].UBOId);
  glBindBuffer(GL_UNIFORM_BUFFER, AA4_RndUBOs[AA4_RndUBOsSize].UBOId);
  glBufferData(GL_UNIFORM_BUFFER, Size, NULL, GL_STATIC_DRAW);
 
  if (Bits != NULL)
    glBufferSubData(GL_UNIFORM_BUFFER, 0, Size, Bits);
  glBindBuffer(GL_UNIFORM_BUFFER, 0);
 
  /* Add to stock */
  AA4_RndUBOs[AA4_RndUBOsSize].Size = Size;
  AA4_RndUBOs[AA4_RndUBOsSize].BindPoint = BindPoint;
  strncpy(AA4_RndUBOs[AA4_RndUBOsSize].Name, Name, AA4_STR_MAX - 1);
  return AA4_RndUBOsSize++;
} /* End of 'AA4_RndUBOCreate' function */
 
/* UBO data update function.
 * ARGUMENTS:
 *   - UBO number in stock:
 *       INT UBONo;
 *   - UBO offset in bytes:
 *       INT Offset;
 *   - UBO update data size in bytes:
 *       INT Size;
 *   - UBO data ('Size' bytes):
 *       VOID *Bits;
 * RETURNS: None.
 */
VOID AA4_RndUBOUpdate( INT UBONo, INT Offset, INT Size, VOID *Bits )
{
  if (UBONo < 0 || UBONo >= AA4_RndUBOsSize)
    return;
 
  /* Update UBO data */
  if (Offset >= AA4_RndUBOs[UBONo].Size)
    return;
  if (Offset < 0)
    Offset = 0;
  if (Size == 0)
    Size = AA4_RndUBOs[UBONo].Size;
  if (Offset + Size > AA4_RndUBOs[UBONo].Size)
    Size = AA4_RndUBOs[UBONo].Size - Offset;
 
  glBindBuffer(GL_UNIFORM_BUFFER, AA4_RndUBOs[UBONo].UBOId);
  glBufferSubData(GL_UNIFORM_BUFFER, Offset, Size, Bits);
  glBindBuffer(GL_UNIFORM_BUFFER, 0);
} /* End of 'AA4_RndUBOUpdate' function */

/* UBO Cam data update function.
 * ARGUMENTS:
 *   - None.
 * RETURNS: None.
 */
VOID AA4_RndUBOCamUpdate( VOID )
{
  AA4_UboCam.CamLoc = Vec4Set(AA4_RndCamLoc.X, AA4_RndCamLoc.Y, AA4_RndCamLoc.Z, 0);
  AA4_UboCam.CamRight = Vec4Set(AA4_RndCamRight.X, AA4_RndCamRight.Y, AA4_RndCamRight.Z, 0);
  AA4_UboCam.CamUp = Vec4Set(AA4_RndCamUp.X, AA4_RndCamUp.Y, AA4_RndCamUp.Z, 0);
  AA4_UboCam.CamDir = Vec4Set(AA4_RndCamDir.X, AA4_RndCamDir.Y, AA4_RndCamDir.Z, 0);

  AA4_UboCam.MatrV = AA4_RndMatrView;
  AA4_UboCam.MatrP = AA4_RndMatrProj;
  AA4_UboCam.MatrVP = AA4_RndMatrVP;
  AA4_UboCam.FrameWHProjSizeDist = Vec4Set(AA4_Anim.W, AA4_Anim.H, AA4_RndProjSize, AA4_RndProjDist);

  AA4_RndUBOUpdate(AA4_RndShdUBOCameraNo, 0, sizeof(aa4RND_UBO_CAMERA), &AA4_UboCam);
} /* End of 'AA4_RndUBOCamUpdate' function */

/* UBO Sync data update function.
 * ARGUMENTS:
 *   - None.
 * RETURNS: None.
 */
VOID AA4_RndUBOSyncUpdate( VOID )
{
  AA4_UboSync.IsWireFrameIsPauseFPS = Vec4Set(AA4_Anim.IsPause, AA4_Anim.IsPause, AA4_Anim.FPS, 0);
  AA4_UboSync.TimeDeltaTimeGlobalTimeDeltaTime = Vec4Set(AA4_Anim.Time, AA4_Anim.DeltaTime, AA4_Anim.GlobalTime, AA4_Anim.GlobalDeltaTime);
  AA4_RndUBOUpdate(AA4_RndShdUBOSyncNo, 0, sizeof(aa4RND_UBO_SYNC), &AA4_UboSync);
} /* End of 'AA4_RndUBOSyncUpdate' function */

/* UBO Prim data update function.
 * ARGUMENTS:
 *   - Prim Matrixes.
 *       MATR W, MATR WINV, MATR WVP;
 * RETURNS: None.
 */
VOID AA4_RndUBOPrimUpdate( MATR W, MATR WINV, MATR WVP )
{
  AA4_UboPrim.MatrW = W;
  AA4_UboPrim.MatrWInv = WINV;
  AA4_UboPrim.MatrWVP = WVP;
  memcpy(AA4_UboPrim.AddonI, AA4_RndShdAddonI, sizeof(AA4_RndShdAddonI));
  memcpy(AA4_UboPrim.AddonV, AA4_RndShdAddonV, sizeof(AA4_RndShdAddonV));
  memcpy(AA4_UboPrim.AddonF, AA4_RndShdAddonF, sizeof(AA4_RndShdAddonF));
  AA4_RndUBOUpdate(AA4_RndShdUBOPrimNo, 0, sizeof(aa4RND_UBO_PRIM), &AA4_UboPrim);
} /* End of 'AA4_RndUBOPrimUpdate' function */

/* Update light source data on GPU function.
 * ARGUMENTS:
 *   - light source pointer:
 *       aa4LIGHT *Lig;
 * RETURNS: None.
 */
VOID AA4_RndUBOLightUpdate( aa4LIGHT *Lig )
{
  AA4_UboLig.PosCutOffAngle1 = Vec4Set(Lig->Pos.X, Lig->Pos.Y, Lig->Pos.Z, Lig->CutOffAngle.X);
  AA4_UboLig.DirCutOffAngle2 = Vec4Set(Lig->Pos.X, Lig->Pos.Y, Lig->Pos.Z, Lig->CutOffAngle.Y);
  AA4_UboLig.ColorCutOffDist1 = Vec4Set(Lig->Color.X, Lig->Color.Y, Lig->Color.Z, Lig->CutOffDist.X);
  AA4_UboLig.AttCutOffDist2 = Vec4Set(Lig->Att.X, Lig->Att.Y, Lig->Att.Z, Lig->CutOffDist.Y);
  AA4_RndUBOUpdate(Lig->UBONo, 0, sizeof(aa4RND_UBO_LIGHT), &AA4_UboLig);
} /* End of 'AA4_RndUBOLightUpdate' function */

/* UBO apply function.
 * ARGUMENTS:
 *   - UBO number in stock:
 *       INT UBONo;
 * RETURNS: None.
 */
VOID AA4_RndUBOApply( INT UBONo )
{
  if (UBONo < 0 || UBONo >= AA4_RndUBOsSize)
    return;

  glBindBufferBase(GL_UNIFORM_BUFFER, AA4_RndUBOs[UBONo].BindPoint,
    AA4_RndUBOs[UBONo].UBOId);
} /* End of 'AA4_RndUBOApply' function */

/* END OF 'rndubo.c' FILE */
