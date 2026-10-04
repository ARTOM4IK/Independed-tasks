/* FILE NAME: rndprim.h
 * PROGRAMMER: AA4
 * LAST UPDATE: 22.01.2025
 * PURPOSE: 3D animation project.
 *          Primitives module.
 */

#include <stdio.h>
#include "anim/anim.h"
#include "rnd.h"

/* Primitive bound box obtaining function.
 * ARGUMENTS:
 *   - pinter to result min-max vectors:
 *       VEC *MinBB, *MaxBB;
 *   - pointer to vertex attributes array:
 *       aa4VERTEX *V;
 *   - vertex attributes array size:
 *       NoofV;
 * RETURNS: None.
 */
VOID AA4_RndPrimEvalBB( VEC *MinBB, VEC *MaxBB, aa4VERTEX *V, INT NoofV )
{
  INT i;

  if (V == NULL || NoofV == 0)
    return;
  *MinBB = *MaxBB = V[0].P;
  for (i = 1; i < NoofV; i++)
  {
    if (MinBB->X > V[i].P.X)
      MinBB->X = V[i].P.X;
    if (MaxBB->X < V[i].P.X)
      MaxBB->X = V[i].P.X;
 
    if (MinBB->Y > V[i].P.Y)
      MinBB->Y = V[i].P.Y;
    if (MaxBB->Y < V[i].P.Y)
      MaxBB->Y = V[i].P.Y;
 
    if (MinBB->Z > V[i].P.Z)
      MinBB->Z = V[i].P.Z;
    if (MaxBB->Z < V[i].P.Z)
      MaxBB->Z = V[i].P.Z;
  }
} /* End of 'AA4_RndPrimEvalBB' function */

/* Primitive vertex normals evaluate function.
 * ARGUMENTS:
 *   - vertex attributes array:
 *       aa4VERTEX *V;
 *   - vertex attributes array size:
 *       INT NoofV;
 *   - primitive vertex index array:
 *       INT *Ind;
 *   - primitive vertex index array size:
 *       INT NoofI;
 * RETURNS: None.
 */
VOID AA4_RndPrimAutoNormals( aa4VERTEX *V, INT NoofV, INT *Ind, INT NoofI )
{
  INT i;
  VEC L = VecSet1(1);
  FLT nl;

  /* Set all vertex normals to zero */
  for (i = 0; i < NoofV; i++)
    V[i].N = VecSet(0, 0, 0);
 
  /* Eval normal for every facet */
  for (i = 0; i < NoofI; i += 3)
  {
    INT
      n0 = Ind[i], n1 = Ind[i + 1], n2 = Ind[i + 2];
    VEC
      p0 = V[n0].P,
      p1 = V[n1].P,
      p2 = V[n2].P,
      N = VecNormalize(VecCrossVec(VecSubVec(p1, p0), VecSubVec(p2, p0)));
 
    V[n0].N = VecAddVec(V[n0].N, N);
    V[n1].N = VecAddVec(V[n1].N, N);
    V[n2].N = VecAddVec(V[n2].N, N);
  }
 
  /* Normalize all vertex normals */
  for (i = 0; i < NoofV; i++)
  {
    V[i].N = VecNormalize(V[i].N);
    nl = VecDotVec(V[i].N, L), nl = nl < 0.1 ? 0.1 : nl;
    V[i].C = Vec4Set(V[i].C.X * nl, V[i].C.Y * nl, V[i].C.Z * nl, 1);
  }
} /* End of 'AA4_RndPrimAutoNormals' function */

BOOL AA4_RndPrimCreate( aa4PRIM *Pr, aa4PRIM_TYPE PrimType, aa4VERTEX *V, INT NoofV, INT* Ind, INT NoofI )
{
  Pr->IBuf = Pr->VA = Pr->VBuf = 0;
  Pr->Trans = MatrIdentity();

  glGenVertexArrays(1, &Pr->VA);
  /* Vertex data */
  if (V != NULL && NoofV != 0)
  {
    glGenBuffers(1, &Pr->VBuf);
  }
  /* Index data */
  if (Ind != NULL && NoofI != 0)
  {
    glGenBuffers(1, &Pr->IBuf);
    Pr->NumOfElements = NoofI;
  }
  else
    Pr->NumOfElements = NoofV;

  /* Activate vertex array */
  glBindVertexArray(Pr->VA);

  glBindBuffer(GL_ARRAY_BUFFER, Pr->VBuf);
  glBufferData(GL_ARRAY_BUFFER, sizeof(aa4VERTEX) * NoofV, V, GL_STATIC_DRAW);

  /* Index data */
  if (Ind != NULL && NoofI != 0)
  {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Pr->IBuf);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(INT) * NoofI, Ind, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, Pr->VBuf);
  }

  glVertexAttribPointer(0, 3, GL_FLOAT, FALSE, sizeof(aa4VERTEX),
                        (VOID *)0);                                 /* Position */
  glVertexAttribPointer(1, 2, GL_FLOAT, FALSE, sizeof(aa4VERTEX),
                        (VOID *)sizeof(VEC));                       /* Texture vertex */
  glVertexAttribPointer(2, 3, GL_FLOAT, FALSE, sizeof(aa4VERTEX),
                        (VOID *)(sizeof(VEC) + sizeof(VEC2)));      /* Normalize vertex */
  glVertexAttribPointer(3, 4, GL_FLOAT, FALSE, sizeof(aa4VERTEX),
                        (VOID *)(sizeof(VEC) * 2 + sizeof(VEC2)));  /* Color vertex */

  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);
  glEnableVertexAttribArray(2);
  glEnableVertexAttribArray(3);
  
  glBindVertexArray(0);

  AA4_RndPrimEvalBB(&Pr->MinBB, &Pr->MaxBB, V, NoofV);

  Pr->Trans = MatrIdentity();
  Pr->Type = PrimType;
  return TRUE;
} /* End of 'AA4_RndPrimCreate' function */

/* Free primitive struct function.
 * ARGUMENTS:
 *   - pointer to primitive to load:
 *       aa4PRIM *Pr;
 * RETURNS:
 *   (VOID) Nothing.
 */
VOID AA4_RndPrimFree( aa4PRIM *Pr )
{
  glBindVertexArray(Pr->VA);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glDeleteBuffers(1, &Pr->VBuf);
  glBindVertexArray(0);
  glDeleteVertexArrays(1, &Pr->VA);
  glDeleteBuffers(1, &Pr->IBuf);
} /* End of 'AA4_RndPrimFree' function */

/* Draw primitive function.
 * ARGUMENTS:
 *   - pointer to primitive to load:
 *       aa4PRIM *Pr;
 *   - world matrix:
 *       MATR World;
 * RETURNS:
 *   (VOID) Nothing.
 */
VOID AA4_RndPrimDraw( aa4PRIM *Pr, MATR World )
{
  MATR
    w = MatrMulMatr(Pr->Trans, World),
    winv = MatrTranspose(MatrInverse(w)),
    wvp = MatrMulMatr(w, AA4_RndMatrVP);

  INT 
    ProgId,
    gl_prim =
    Pr->Type == AA4_RND_PRIM_LINES ? GL_LINES :
    Pr->Type == AA4_RND_PRIM_TRIMESH ? GL_TRIANGLES :
    Pr->Type == AA4_RND_PRIM_TRISTRIP ? GL_TRIANGLE_STRIP :
    Pr->Type == AA4_RND_PRIM_PATCH ? GL_PATCHES :
    GL_POINTS;

  if ((ProgId = AA4_RndMtlApply(Pr->MtlNo)) == 0)
    return;

  MatrInverse(wvp);

  /* Upadte UBO */
  AA4_RndUBOCamUpdate();
  AA4_RndUBOPrimUpdate(w, winv, wvp);

  /* Activate vertex array */
  glBindVertexArray(Pr->VA);

  if (Pr->Type == AA4_RND_PRIM_PATCH)
    glPatchParameteri(GL_PATCH_VERTICES, Pr->NumOfPatchPoints);

  if (Pr->IBuf != 0)
  {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Pr->IBuf);
    /* Drawing */
    glDrawElements(gl_prim, Pr->NumOfElements, GL_UNSIGNED_INT, NULL);
    /* Unable face array */
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  }
  else
    glDrawArrays(gl_prim, 0, Pr->NumOfElements);

  glBindVertexArray(0);
  glUseProgram(0);
}  /* End of 'AA4_RndPrimDraw' function */

/* Load primitive from '*.OBJ' file function.
 * ARGUMENTS:
 *   - pointer to primitive to load:
 *       aa4PRIM *Pr;
 *   - '*.OBJ' file name:
 *       CHAR *FileName;
 * RETURNS:
 *   (BOOL) TRUE if success, FALSE otherwise.
 */
BOOL AA4_RndPrimLoad( aa4PRIM *Pr, CHAR *FileName )
{
  aa4VERTEX *V;
  INT *I, size;
  FILE *F;                 /* File variable */
  INT nv = 0, nf = 0;      /* Vertex / Face counters */
  static CHAR Buf[10000];  /* Buffer of vertexes and faces */

  memset(Pr, 0, sizeof(aa4PRIM));
  if ((F = fopen(FileName, "r")) == NULL)
    return FALSE;

  /* Count vertices and indices */
  while (fgets(Buf, sizeof(Buf) - 1, F) != NULL)
    if (Buf[0] == 'v' && Buf[1] == ' ')
      nv++;
    else if (Buf[0] == 'f' && Buf[1] == ' ')
    {
      INT n = 0;
      CHAR *ptr = Buf + 2, old = ' ';
 
      while (*ptr != 0)
        n += !isspace((UCHAR)*ptr) && isspace((UCHAR)old), old = *ptr++;
      nf += n - 2;
    }

  /* Allocate memory */
  size = sizeof(aa4VERTEX) * nv + sizeof(INT) * nf * 3;
  if ((V = malloc(size)) == NULL)
  {
    fclose(F);
    return FALSE;
  }

  I = (INT *)(V + nv);
  memset(V, 0, size);

  /* Read data */
  rewind(F);
  nv = nf = 0;
  while (fgets(Buf, sizeof(Buf) - 1, F) != NULL)
    if (Buf[0] == 'v' && Buf[1] == ' ')
    {
      DBL x, y, z;
      sscanf(Buf + 2, "%lf %lf %lf", &x, &y, &z);
      V[nv].C = Vec4Set((FLT)rand() / RAND_MAX, (FLT)rand() / RAND_MAX, (FLT)rand() / RAND_MAX, 1);
      /*V[nv].C = Vec4Set(255, 255, 255, 1);*/
      V[nv++].P = VecSet(x, y, z);
    }
    else if (Buf[0] == 'f' && Buf[1] == ' ')
    {
      INT n = 0, c = 0, c0 = 0, c1 = 0;
      CHAR *ptr = Buf + 2, old = ' ';
 
      while (*ptr != 0)
      {
        if (!isspace((UCHAR)*ptr) && isspace((UCHAR)old))
        {
          sscanf(ptr, "%d", &c);
          if (c < 0)
            c = nv + c;
          else
            c--;

          if (n == 0)
            c0 = c;
          else if (n == 1)
            c1 = c;
          else
          {
            /* Add a new triangle */
            I[nf++] = c0;
            I[nf++] = c1;
            I[nf++] = c;
            c1 = c;
          }
          n++;
        }
        old = *ptr++;
      }
    }
  fclose(F);

  AA4_RndPrimAutoNormals(V, nv, I, nf);

  AA4_RndPrimCreate(Pr, AA4_RND_PRIM_TRIMESH, V, nv, I, nf);
  free(V);
  return TRUE;
} /* End of 'AA4_RndPrimLoad' function */

/* END OF 'rndprim.c' FILE */
