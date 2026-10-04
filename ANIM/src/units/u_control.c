/* FILE NAME  : u_ctrl.c
 * PROGRAMMER : AA4
 * LAST UPDATE: 05.02.2025
 * PURPOSE    : 3D animation project.
 *              Units samples.
 *              Control unit.
 */
 
#include <stdio.h>
#include "units.h"
 
/* Control unit initialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       aa4UNIT_CONTROL *Uni;
 *   - animation context:
 *       aa4ANIM *Ani;
 * RETURNS: None.
 */
static VOID AA4_UnitInit( aa4UNIT_CONTROL *Uni, aa4ANIM *Ani )
{
  AA4_RndFntInit();
} /* End of 'AA4_UnitInit' function */
 
/* Control unit deinitialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       aa4UNIT_CONTROL *Uni;
 *   - animation context:
 *       aa4ANIM *Ani;
 * RETURNS: None.
 */
static VOID AA4_UnitClose( aa4UNIT_CONTROL *Uni, aa4ANIM *Ani )
{
  AA4_RndFntClose();
} /* End of 'AA4_UnitClose' function */
 
/* Control unit inter frame events handle function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       aa4UNIT_CONTROL *Uni;
 *   - animation context:
 *       aa4ANIM *Ani;
 * RETURNS: None.
 */
static VOID AA4_UnitResponse( aa4UNIT_CONTROL *Uni, aa4ANIM *Ani )
{
  INT modes[2];
 
  AA4_TimerResponse();

  /* Common usage control */
  if (Ani->Keys[VK_SHIFT] && Ani->KeysClick['P'])
    Ani->IsPause = !Ani->IsPause;
  if (Ani->KeysClick[VK_F11])
    AA4_AnimFlipFullScreen();
  if (Ani->KeysClick[VK_ESCAPE])
    AA4_AnimDoExit();
  if (Ani->Keys[VK_CONTROL] && Ani->KeysClick['F'])
    AA4_RndCamSet(VecSet(2, 3, 5), VecSet(0, 0, 0), VecSet(0, 1, 0));
 
  /* Wireframe/solid switch */
  if (Ani->Keys[VK_SHIFT] && Ani->Keys['W'])
  {
    glGetIntegerv(GL_POLYGON_MODE, modes);
    if (modes[0] == GL_LINE)
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    else
      glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  }

  /* Camera handle */
  if (Ani->Keys[VK_LCONTROL])
  {
    /* Rotate handle */
    FLT
      Dist = VecLen(VecSubVec(AA4_RndCamAt, AA4_RndCamLoc)),
      cosT = (AA4_RndCamLoc.Y - AA4_RndCamAt.Y) / Dist,
      sinT = sqrt(1 - cosT * cosT),
      plen = Dist * sinT,
      cosP = (AA4_RndCamLoc.Z - AA4_RndCamAt.Z) / plen,
      sinP = (AA4_RndCamLoc.X - AA4_RndCamAt.X) / plen,
      Azimuth = R2D(atan2(sinP, cosP)),
      Elevator = R2D(atan2(sinT, cosT));

    Azimuth += 
      (-1 * Ani->Keys[VK_LBUTTON] * Ani->Mdx +
       Ani->GlobalDeltaTime * 100 * -(Ani->Keys[VK_LEFT] - Ani->Keys[VK_RIGHT]));

    Elevator += 
      (-1 * Ani->Keys[VK_LBUTTON] * Ani->Mdy +
       Ani->GlobalDeltaTime * 100 * (Ani->Keys[VK_UP] - Ani->Keys[VK_DOWN]));

    if (Elevator < 0.08)
      Elevator = 0.08;
    else if (Elevator > 178.90)
      Elevator = 178.90;
 
    Dist += (1 + Ani->Keys[VK_SHIFT] * 30) *
      (0.01 * Ani->Mdz +
       Ani->GlobalDeltaTime * 100 * (Ani->Keys[VK_NEXT] - Ani->Keys[VK_PRIOR]));
    if (Dist < 0.1)
      Dist = 0.1;
 
    /* Handle camera position */
    if (Ani->Keys[VK_RBUTTON])
    {
      FLT Wp, Hp, sx, sy;
      VEC dv;
 
      Wp = AA4_RndProjSize;
      Hp = AA4_RndProjSize;
 
      if (Ani->W > Ani->H)
        Wp *= (FLT)Ani->W / Ani->H;
      else
        Hp *= (FLT)Ani->H / Ani->W;
 
      sx = -Ani->Mdx * Wp / Ani->W * Dist / AA4_RndProjDist;
      sy = Ani->Mdy * Hp / Ani->H * Dist / AA4_RndProjDist;

      dv = VecAddVec(VecMulNum(AA4_RndCamRight, sx),
                     VecMulNum(AA4_RndCamUp, sy));
      AA4_RndCamAt = VecAddVec(AA4_RndCamAt, dv);
      AA4_RndCamLoc = VecAddVec(AA4_RndCamLoc, dv);
    }

    /* Setup result camera */
    AA4_RndCamSet(PointTransform(VecSet(0, Dist, 0),
                                 MatrMulMatr(MatrRotateX(Elevator),MatrMulMatr(
                                              MatrRotateY(Azimuth),
                                              MatrTranslate(AA4_RndCamAt)))),
                  AA4_RndCamAt,
                  VecSet(0, 1, 0));
  }
} /* End of 'AA4_UnitResponse' function */
 
/* Control unit render function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       aa4UNIT_CONTROL *Uni;
 *   - animation context:
 *       aa4ANIM *Ani;
 * RETURNS: None.
 */
static VOID AA4_UnitRender( aa4UNIT_CONTROL *Uni, aa4ANIM *Ani )
{
  MATR SaveWVP = AA4_RndMatrVP;
  static CHAR Buf[102];


    sprintf(Buf, "CGSG Animation: FPS = %.5f Time: %.5f", Ani->FPS, Ani->Time);
  AA4_RndMatrVP = MatrOrtho(0, (Ani->W - 1) / 30.0, -(Ani->H - 1) / 30.0, 0, -1, 1); //MatrOrtho(-50, 10, -10, 5, -1, 1)
  AA4_RndFntDraw(Buf, VecSet(-30, 15, 0), 1);
  AA4_RndMatrVP = SaveWVP;
  SetWindowText(Ani->hWnd, Buf);
} /* End of 'AA4_UnitRender' function */

/* Control unit creation function.
 * ARGUMENTS: None.
 * RETURNS:
 *   (aa4UNIT *) pointer to created unit.
 */
aa4UNIT * AA4_UnitCamCreate( VOID )
{
  aa4UNIT *Uni;
 
  /* Memory allocation */
  if ((Uni = AA4_AnimUnitCreate(sizeof(aa4UNIT_CONTROL))) == NULL)
    return NULL;
  /* Setup unit methods */
  Uni->Init = (VOID *)AA4_UnitInit;
  Uni->Close = (VOID *)AA4_UnitClose;
  Uni->Response = (VOID *)AA4_UnitResponse;
  Uni->Render = (VOID *)AA4_UnitRender;
  return Uni;
} /* End of 'AA4_UnitCreateControl' function */
 
/* END OF 'u_ctrl.c' FILE */