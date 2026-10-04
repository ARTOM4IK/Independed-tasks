/*************************************************************
 * Copyright (C) 2025
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : triangle.h
 * PURPOSE     : Ray Tracing project.
 *               Frame module.
 * PROGRAMMER  : CGSG-SummerCamp'2025.
 *               Artemy V. Arsentev
 * LAST UPDATE : 21.07.2025.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __triangle_h_
#define __triangle_h_

#include "rt/rt_def.h"

/* Ray tracing namespace */
namespace arrt
{
  /* Triangle class */
  class triangle: public shape
  {
  public: 
    /* Vertex class */
    class vertex
    {
    public:
      mth::vec3<FLT> P;
      mth::vec4<FLT> C;
      mth::vec3<FLT> N;
      mth::vec2<FLT> T;
      mth::vec3<FLT> Tangent;
      mth::vec3<FLT> Bitangent;

      /* Type constructor.
       * ARGUMENTS:
       *   - vertex parametrs:
       *       vec3 p, vec3 c, vec3 n, vec3 t, vec3 tan, vec3 bit;
       */
      vertex( mth::vec3<FLT> p, mth::vec2<FLT> t, mth::vec3<FLT> n ) : P(p), T(t), N(n)
      {
      } /* End of 'vertex' function */

      /* Type constructor.
       * ARGUMENTS: None.
       */
      vertex( VOID )
      {
      } /* End of 'vertex' function */
    }; /* End of 'vertex' class */    
    
    vec3 Color, P0, P1, P2, S1, S2, U1, V1, N;
    DBL D, u0, v0;
    surface surf;
    envi env;
    vertex p0, p1, p2;
    vec2 t0, t1, t2;

    /* Type constructor.
     * ARGUMENTS:
     *   - triangle parametrs:
     *       vec3 p0, vec3 p1, vec3 p2, vec3 color, envi e, surface S;
     */
    triangle( vec3 newp0, vec3 newp1, vec3 newp2, vec3 color, envi e, surface S ): P0(newp0), P1(newp1), P2(newp2), Color(color), env(e), surf(S)
    {
      Surf = surf;
      Env = env;
      S1 = P1 - P0;
      S2 = P2 - P0;
      U1 = (S1 * (S2 & S2) - S2 * (S1 & S2)) / ((S1 & S1) * (S2 & S2) - (S1 & S2) * (S1 & S2));
      V1 = (S2 * (S1 & S1) - S1 * (S1 & S2)) / ((S1 & S1) * (S2 & S2) - (S1 & S2) * (S1 & S2));
      u0 = P0 & U1;
      v0 = P0 & V1;
      N = (P1 - P0) % (P2 - P0);
      N.Normalize();
      D = N & P0;
    } /* End of 'triangle' funciton */

    /* Type constructor.
     * ARGUMENTS:
     *   - triangle parametrs:
     *       vec3 p0, vec3 p1, vec3 p2, vec3 color, envi e, surface S;
     */
    triangle( vertex newp0, vertex newp1, vertex newp2 ): p0(newp0), p1(newp1), p2(newp2)
    {
      arrt::envi env1;
      env1.Decay = 1;
      env1.RefractionCoef = 0.98;

      Env = env1;
      arrt::surface tr_surf;
      surf.Ka = arrt::coef(1, 1, 0.01175);
      surf.Kd = arrt::coef(1, 1, 0.04136);
      tr_surf.Ks = arrt::coef(0.633, 0.727811, 0.633);
      tr_surf.Ph = 76.8;
      tr_surf.Kr = arrt::coef(0.0);
      tr_surf.Kt = arrt::coef(0.8);

      Surf = tr_surf;

      env = env1;
      surf = tr_surf; 

      P0 = vec3(static_cast<DBL>(p0.P.X), static_cast<DBL>(p0.P.Y), static_cast<DBL>(p0.P.Z));
      P1 = vec3(static_cast<DBL>(p1.P.X), static_cast<DBL>(p1.P.Y), static_cast<DBL>(p1.P.Z));
      P2 = vec3(static_cast<DBL>(p2.P.X), static_cast<DBL>(p2.P.Y), static_cast<DBL>(p2.P.Z));

      t0 = vec2(static_cast<DBL>(newp0.T.X), static_cast<DBL>(newp0.T.Y));
      t1 = vec2(static_cast<DBL>(newp1.T.X), static_cast<DBL>(newp1.T.Y));
      t2 = vec2(static_cast<DBL>(newp2.T.X), static_cast<DBL>(newp2.T.Y));

      S1 = P1 - P0;
      S2 = P2 - P0;
      U1 = (S1 * (S2 & S2) - S2 * (S1 & S2)) / ((S1 & S1) * (S2 & S2) - (S1 & S2) * (S1 & S2));
      V1 = (S2 * (S1 & S1) - S1 * (S1 & S2)) / ((S1 & S1) * (S2 & S2) - (S1 & S2) * (S1 & S2));
      u0 = P0 & U1;
      v0 = P0 & V1;
      N = (P1 - P0) % (P2 - P0);
      N = N.Normalize();
      D = N & P0;
    } /* End of 'triangle' funciton */

    /* Finder intersection an object function.
     * ARGUMENTS:
     *   - ray:
     *       const ray &Ray;
     *   - intersection structure:
     *       intr_list &IList;
     *   (BOOL) Is intersect sign.
     */
    virtual BOOL Intersect( const ray &R, intr *Intr );      

    /* Get normal function.
     * ARGUMENTS:
     *   - intersection structure:
     *       intr *I;
     * RETURNS: None.
     */
    virtual VOID GetNormal( intr *Intr );

    /* Get color function.
     * ARGUMENTS:
     *   - intersection structure:
     *       intr *I;
     * RETURNS: None.
     */
    virtual VOID GetColor( intr *Intr );

    /* Find intersection with all objects function.
     * ARGUMENTS:
     *   - ray:
     *       const ray &Ray;
     *   - intersection structure:
     *       intr_list &IList;
     * RETURNS: None.
     */
    virtual INT AllIntersect( const ray &Ray, intr_list &IList ) override;
  }; /* End of 'triangle' class */

  /* Rdr class */
  class rdr
  {
  private:
    BYTE *&Ptr;

  public:
    /* Class constructor.
     * ARGUMENTS:
     *   - reference to memory pointer:
     *       BYTE *&PtrRef;
     */
    rdr( BYTE *&PtrRef ) : Ptr(PtrRef)
    {
    } /* End of 'rdr' function */

    /* Read data function.
     * ARGUMENTS:
     *   - read data pointer:
     *       type *Data;
     *   - read data count:
     *       const INT Count;
     * RETURNS: None.
     */
     template<typename type>
      VOID operator()( type *Data, const INT Count = 1 )
      {
        if (Count == 1)
        {
          *Data = *(type *)Ptr;
          Ptr += sizeof(type);
        }
        else
        {
          memcpy(Data, Ptr, sizeof(type) * Count);
          Ptr += sizeof(type) * Count;
        }
      } /* End of 'operator()' function */

    /* Read data function.
     * ARGUMENTS:
     *   - read data (skip with store pointer) pointer:
     *       type **Data;
     *   - read data count:
     *       const INT Count;
     * RETURNS: None.
     */
     template<typename type>
      VOID operator()( type **Data, const INT Count = 1 )
      {
        *Data = (type *)Ptr;
        Ptr += sizeof(type) * Count;
      } /* End of 'operator()' function */
  }; /* End of 'rdr' class */

  /* Trimesh class */
  class trimesh: public shape
  {
  public:
    std::vector<triangle> Triangles;
    std::vector<image *> Textures;

    /* Class constructor.
     * ARGUMENTS: None
     */
    trimesh( VOID )
    {
      arrt::envi env1;
      env1.Decay = 1;
      env1.RefractionCoef = 0.98;

      Env = env1;
      arrt::surface surf;

      surf.Ka = arrt::coef(0.1745, 0.01175, 0.01175);
      surf.Kd = arrt::coef(0.61424, 0.04136, 0.04136);
      surf.Ks = arrt::coef(0.727811, 0.626959, 0.626959);
      surf.Ph = 76.8;
      surf.Kr = arrt::coef(0);
      surf.Kt = arrt::coef(1);

      Surf = surf;
    } /* End of 'trimesh' function */

    /* Get normal function.
     * ARGUMENTS:
     *   - intersection structure:
     *       intr *I;
     * RETURNS: None.
     */
    virtual VOID GetNormal( intr *Intr )
    {
    }

    /* Finder intersection an object function.
     * ARGUMENTS:
     *   - ray:
     *       const ray &Ray;
     *   - intersection structure:
     *       intr_list &IList;
     *   (BOOL) Is intersect sign.
     */
    virtual BOOL Intersect( const ray &R, intr *Intr )
    {
      intr closest_intr {};

      for (auto tr : Triangles)
      {
        intr cur_intr {};

        if (tr.Intersect(R, &cur_intr))
          if (closest_intr.Shp == nullptr || (closest_intr.T > cur_intr.T))
            closest_intr = cur_intr, closest_intr.Shp = this;
        ////fake texture
        //DBL U = (Intr->P & tr.U1) - tr.u0;
        //DBL V = (Intr->P & tr.V1) - tr.v0;
        //vec3 sampl = Textures[0]->Sample(tr.t0 * V + tr.t1 * U + tr.t2 * (1 - U - V));
        //tr.Surf.Ka.K = arrt::coef(sampl);
        Surf = tr.Surf;
      }

      if (closest_intr.Shp == nullptr)
        return FALSE;
      if (Intr != nullptr)
        *Intr = closest_intr;
      return TRUE; 
    } /* End of 'Intersect' function*/

    /* Find intersection with all objects function.
     * ARGUMENTS:
     *   - ray:
     *       const ray &Ray;
     *   - intersection structure:
     *       intr_list &IList;
     * RETURNS: None.
     */
    virtual INT AllIntersect( const ray &Ray, intr_list &IList ) override
    {
      INT sum = 0;

      for (auto tr : Triangles)
        sum += tr.AllIntersect(Ray, IList);
      return sum;
    } /* End of 'AllIntersect' function*/

    /* Add trimesh model to shape function.
     * ARGUMENTS:
     *   - trimesh filename (.G3DM):
     *       const std::string;
     *   - transform matrix:
     *       const matr &Transform;
     *   - texture vertical flip flag:
     *       BOOL IsTextureFlipY;
     * RETURNS: 
     *   (BOOL) TRUE if success, FALSE otherwise.
     */
    BOOL AddModel( const std::string &FileName, const matr &Transform = matr::Identity(), BOOL IsTextureFlipY = FALSE)
    {
      std::fstream f(FileName, std::fstream::in | std::fstream::binary);

      if (!f.is_open())
        return FALSE;

      f.seekg(0, std::fstream::end);
      SIZE_T flen = f.tellg();
      f.seekg(0, std::fstream::beg);

      std::vector<BYTE> mem;
      mem.resize(flen);
      f.read((CHAR *)mem.data(), flen);
      BYTE *ptr = mem.data();
      BYTE *ptr1 = ptr;

      rdr rd(ptr);

      //load header
      DWORD sign;
      rd(&sign);
      if (sign != *(DWORD *)"G3DM")
      {
        std::cout << " NOT G3DM\n";
        return FALSE;
      }

      //recalculate triangles count
      rdr rdp(ptr1);
      rdp(&sign);
      INT NoofP1 = 0, NoofM1 = 0, NoofT1 = 0;
      rdp(&NoofP1);
      rdp(&NoofM1);
      rdp(&NoofT1);
      INT tcnt = 0;
      for (INT i = 0; i < NoofP1; i++)
      {
        //Vertex store type
        struct STORE_VERTEX
        {
          mth::vec3<FLT> P;
          mth::vec2<FLT> T;
          mth::vec3<FLT> N;
          mth::vec4<FLT> C;
        }; /* End of 'STORE_VERTEXz ' structure */
        STORE_VERTEX *V;
        INT *Ind;
        INT nv = 0, ni = 0, mtl_no;
        rdp(&nv);
        rdp(&ni);
        rdp(&mtl_no);

        rdp(&V, nv);
        rdp(&Ind, ni);
        tcnt += ni / 3;
      }
      Triangles.reserve(Triangles.size() + tcnt);

      INT NoofP = 0, NoofM = 0, NoofT = 0;
      rd(&NoofP);
      rd(&NoofM);
      rd(&NoofT);
      std::cout << std::format("\nG3DM: prims {}, mtls {}, texs{}\n", NoofP, NoofM, NoofT);

      //Load primitives
      std::vector<INT> trgs_mtl;

      auto VertexTBNOrtho =
        []( triangle::vertex *V ) -> VOID
        {
          V->N.Normalize();
          V->Tangent.Normalize();
          V->Bitangent.Normalize();

          V->Tangent = V->Tangent - V->N * (V->N & V->Tangent);
          V->Tangent.Normalize();

          V->Bitangent = V->Bitangent - V->N * (V->N & V->Bitangent) - V->Tangent * (V->Tangent & V->Bitangent);
          V->Bitangent.Normalize();
        }; /* End of 'VertexTBNOrtho' function */

      auto TriangleTangentSpace =
        []( triangle::vertex *P0, triangle::vertex *P1, triangle::vertex *P2 ) -> VOID
        {
          FLT
            s1 = P1->T.X - P0->T.X,
            s2 = P2->T.X - P0->T.X,
            t1 = P1->T.Y - P0->T.Y,
            t2 = P2->T.Y - P0->T.Y,
            det = s1 * t2 - s2 * t1;
           if (det != 0)
           {
             mth::vec3<FLT>
               Q1 = P1->P - P0->P,
               Q2 = P2->P - P0->P,
               T = (Q1 * t2 - Q2 * t1) / det,
               B = (Q2 * s1 - Q1 * s2) / det;

             T.Normalize();
             B.Normalize();

             P0->Tangent = P0->Tangent + T;
           }
        }; /* End of 'TriangleTangentSpace' function */

      /* Load primitives */
      INT start_trg_no = (INT)Triangles.size();
      for( INT i = 0; i < NoofP; i++)
      {
        //Vertex store type
        struct STORE_VERTEX
        {
          mth::vec3<FLT> P;
          mth::vec2<FLT> T;
          mth::vec3<FLT> N;
          mth::vec4<FLT> C;
        }; /* End of 'STORE_VERTEX' structure */
        std::cout << std::format("Load prim: {:5} of {:5}\r", i + 1, NoofP);

        STORE_VERTEX *V;
        INT *Ind;
        INT nv = 0, ni = 0, mtl_no;
        rd(&nv);
        rd(&ni);
        rd(&mtl_no);
        trgs_mtl.resize(trgs_mtl.size() + ni / 3, mtl_no);

        rd(&V, nv);
        rd(&Ind, ni);
        for( INT j = 0; j < nv; j++)
        {
          V[j].P = Transform.TransformPoint(V[j].P);
          V[j].N = Transform.TransformNormal(V[j].N);
        }
        std::vector<triangle::vertex> Vrt;
        Vrt.resize(nv);
        for( INT j = 0; j < nv; j ++)
          Vrt[j] = {V[j].P, V[j].T, V[j].N};
        for( INT j = 0; j < ni; j += 3)
          TriangleTangentSpace(&Vrt[Ind[j]], &Vrt[Ind[j + 1]], &Vrt[Ind[j + 2]]);
        for( INT j = 0; j < nv; j++)
          VertexTBNOrtho(&Vrt[j]);
        for( INT j = 0; j < ni; j += 3)
        {
          Triangles.emplace_back(triangle{Vrt[Ind[j]], Vrt[Ind[j + 1]], Vrt[Ind[j + 2]]});
        }
      }
      std::cout << "\n";

      //load materials
    
      /* Stored material structure */
      struct STORE_MATERIAL
      {
        CHAR Name[300]; //Material name

        /* Illumination coefficients */
        mth::vec3<FLT> Ka, Kd, Ks; // Ambient, diffuse, specular coefficients
        FLT Ph;
        FLT Trans;
        FLT Tex[8];

        //Shader string
        CHAR ShaderStr[300];
        INT Shader;           // Shader index (not used)
      }; /* End of 'STORE_MATERIAL' struct */

      std::cout << "Load materials\n";
      STORE_MATERIAL *store_mtls = nullptr;
      if (NoofM > 0)
        rd(&store_mtls, NoofM);

      //load textures;
      std::cout << "Load textures\n";
      INT start_tex_no = (INT)Textures.size();
      Textures.resize(start_tex_no + NoofT);
      for (INT i = 0; i < NoofT; i++)
      {
        CHAR Name[300];
        INT W, H, C;

        rd(Name, 300);
        rd(&W);
        rd(&H);
        rd(&C);
      
        Textures[start_tex_no + i] = new image();
        Textures[start_tex_no + i]->Create(W, H);
        rd(Textures[start_tex_no + i]->RowsD[0], W * H);
        if (IsTextureFlipY)
          Textures[i]->FlipY();
      }

      // Correct material texture reference
      std::cout << std::format("Finilize, total triangles: {}\n", Triangles.size() - start_trg_no);
      if (store_mtls != nullptr)
        for (INT i = start_trg_no; i < Triangles.size(); i++)
        {
          STORE_MATERIAL *mtl = store_mtls + trgs_mtl[i - start_trg_no];
          Triangles[i].Surf.Ka = arrt::coef(mtl->Ka.X, mtl->Ka.Y, mtl->Ka.Z/*.Min(vec3(0.1)*/);
          Triangles[i].Surf.Kd = arrt::coef(mtl->Kd.X, mtl->Kd.Y, mtl->Kd.Z);
          Triangles[i].Surf.Ks = arrt::coef(mtl->Ks.X, mtl->Ks.Y, mtl->Ks.Z);
          Triangles[i].Surf.Ph = mtl->Ph;
          Triangles[i].Surf.Kr = arrt::coef(mtl->Ks.X * 0.47, mtl->Ks.Y * 0.47, mtl->Ks.Z * 0.47);
          Triangles[i].Surf.Kt = arrt::coef((1.0 - mtl->Trans) * 1.2, (1.0 - mtl->Trans) * 1.2, (1.0 - mtl->Trans) * 1.2);
          //Triangles[i].Mods.push_back(new mods::texture(Textures[0], Triangles[i].u0, Triangles[i].v0, Triangles[i].V1, Triangles[i].U1, Triangles[i].t0, Triangles[i].t1, Triangles[i].t2));
        }
      else
      {
        for (INT i = start_trg_no; i < Triangles.size(); i++)
        {
          Triangles[i].Surf.Ka = arrt::coef(0.1745, 0.01175, 0.01175);
          Triangles[i].Surf.Kd = arrt::coef(0.61424, 0.04136, 0.04136);
          Triangles[i].Surf.Ks = arrt::coef(0.727811, 0.626959, 0.626959);
          Triangles[i].Surf.Ph = 76.8;
          Triangles[i].Surf.Kr = arrt::coef(0.0);
          Triangles[i].Surf.Kt = arrt::coef(1);
        }
      }
      return TRUE;
    } /* End of 'AddModel' function */
  }; /* Enf of 'trimesh' class */
} /* End of 'arrt' namespace */

#endif /* __triangle_h_ */
 
/* END OF 'triangle.h' FILE */
