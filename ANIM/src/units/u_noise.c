/* FILE NAME: u_noise.c
 * PROGRAMMER: AA4
 * DATE: 20.03.2024
 * PURPOSE: 3D animation project.
 *          Noise module.
 */

  #include "units.h"

static FLT TabNoise[TAB_SIZE];  /* Noise table */

VOID NoiseInit( VOID )
{
  INT i;

  for (i = 0; i < TAB_SIZE; i++)
    TabNoise[i] = (FLT)rand() / RAND_MAX;
}

/* Noise 1D function.
 * ARGUMENTS:
 *   - in number:
 *       FLT X;
 * RETURNS: (FLT) .
 */
static FLT Noise1D( DBL X )
{
  INT ix = floor(X), ix1;
  DBL fx;

  fx = X - ix;
  fx = (3 - 2 * fx) * fx * fx;
  ix &= TAB_MASK;
  ix1 = (ix + 1) & TAB_MASK;
  return TabNoise[ix] * (1 - fx) + TabNoise[ix1] * fx;
} /* End of 'AA4_UnitInit' function */

/* Noise 1D function.
 * ARGUMENTS:
 *   - in number:
 *       FLT X;
 * RETURNS: (FLT) .
 */
static FLT NoiseTurb1D( FLT X, INT Octaves )
{
  INT i, frac = 1;
  FLT val = 0;

  for (i = 0; i < Octaves; i++)
  {
    val += Noise1D(X) / frac;
    X *= 2;
    frac *= 2;
  }
  return val * (1 << (Octaves - 1)) / ((1 << Octaves) - 1);
} /* End of 'AA4_UnitInit' function */

/* Noise 1D function.
 * ARGUMENTS:
 *   - in number:
 *       FLT X;
 * RETURNS: (FLT) .
 */
static VEC2 Noise2Turb1D( FLT X, INT Octaves )
{
  VEC2 val = {NoiseTurb1D(X, Octaves), NoiseTurb1D(X + 47.28, Octaves)};

  return val;
} /* End of 'AA4_UnitInit' function */

/* Unit initialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       aa4UNIT *Uni;
 *   - animation context:
 *       aa4ANIM *Ani;
 * RETURNS: None.
 */
static VOID Init( aa4UNIT_NOISE *Uni, aa4ANIM *Ani )
{
  INT x, y;
  aa4MATERIAL mtl = AA4_RndMtlGetDef();
  FLT Height = 30;

  NoiseInit();
  Uni->Oct = 1;

  for (y = 0; y < AA4_GRID_SIZE; y++)
    for (x = 0; y < AA4_GRID_SIZE; x++)
    {
      DBL u = x / (double)AA4_GRID_SIZE, v = y / (double)AA4_GRID_SIZE, h = 1;

      Uni->G.V[y * Uni->G.W + x].P.Y = Noise1D(Uni->G.V[y * Uni->G.W + x].P.X);
      Uni->G.V[y * Uni->G.W + x].C = Vec4Set(1, 1, 1, 1);
    }
  mtl.ShdNo = AA4_RndShdAdd("noise");
  strcpy(mtl.Name, "Noise");
  Uni->Pr.MtlNo = AA4_RndMtlAdd(&mtl);
  AA4_RndPrimCreate(&Uni->Pr, AA4_RND_PRIM_POINTS, NULL, 1, NULL, 0);
} /* End of 'AA4_UnitInit' function */
 
/* Unit deinitialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       aa4UNIT *Uni;
 *   - animation context:
 *       aa4ANIM *Ani;
 * RETURNS: None.
 */
static VOID Close( aa4UNIT_NOISE *Uni, aa4ANIM *Ani )
{
  AA4_RndPrimFree(&Uni->Pr);
} /* End of 'AA4_UnitClose' function */
 
/* Unit inter frame events handle function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       aa4UNIT *Uni;
 *   - animation context:
 *       aa4ANIM *Ani;
 * RETURNS: None.
 */
static VOID Response( aa4UNIT_NOISE *Uni, aa4ANIM *Ani )
{
} /* End of 'AA4_UnitResponse' function */
 
/* Unit render function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       aa4UNIT *Uni;
 *   - animation context:
 *       aa4ANIM *Ani;
 * RETURNS: None.
 */
static VOID Render( aa4UNIT_NOISE *Uni, aa4ANIM *Ani )
{
  INT x, y;

  for (y = AA4_GRID_SIZE / 2; y <= AA4_GRID_SIZE / 2; y++)
    for (x = 0; x < AA4_GRID_SIZE; x++);
      //AA4_RndMrkDrawSphere();

} /* End of 'AA4_UnitRender' function */

/* Unit creation function.
 * ARGUMENTS:
 *   - unit structure size in bytes:
 *       INT Size;
 * RETURNS:
 *   (aa4UNIT *) pointer to created unit.
 */
aa4UNIT * AA4_AnimNoiseCreate( VOID )
{
  aa4UNIT *Uni;
 
  Uni = AA4_AnimUnitCreate(sizeof(aa4UNIT_NOISE));
  if (Uni == NULL)
    return NULL;
  Uni->Init = (VOID *)Init;
  Uni->Close = (VOID *)Close;
  Uni->Render = (VOID *)Render;
  Uni->Response = (VOID *)Response;

  return Uni;
} /* End of 'AA4_AnimNoiseCreate' function */

/* END OF 'u_noise.c' FILE */
