/*************************************************************
 * Copyright (C) 2025
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : rt_def.h
 * PURPOSE     : Ray Tracing project.
 *               Frame module.
 * PROGRAMMER  : CGSG-SummerCamp'2025.
 *               Artemy V. Arsentev
 * LAST UPDATE : 25.07.2025.
 * NOTE        : Module namespace 'arrt'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __rt_def_h_
#define __rt_def_h_

#include "def.h"

/* Ray tracing namespace */
namespace arrt
{
  class shape;

  /* Intersection class */
  class intr
  {
  public:
    DBL T;       // Distance to intersection
    shape *Shp;  // Object shape
    vec3 P;      // Intersection point
    vec3 N;      // Normalized vector
    vec3 Color;  // color
    BOOL IsN;    //
    BOOL IsP;    //
    vec3 MinBB;  // min bound box
    vec3 MaxsBB; // max bound box
    INT I[5] = { 0 };    // additional index
    DBL D[5];    // additional dist
    vec3 V[5];   // additional vec

    /* Ray object entering flag */
    enum ENTER_TYPE
    {
      ENTER,     // Ray goes inside object
      STAY,      // Ray stay in object
      LEAVE      // Ray goes outside object
    } EnterFlag; // Intersection entering flag

    /* Class constructor.
     * AGUMENTS: None.
     */
    intr( VOID ) : Shp(nullptr), IsN(FALSE), IsP(FALSE), EnterFlag(ENTER)
    {
    } /* End of 'intr' function */

    /* Class constructor.
     * ARGUMENTS:
     *   - shape pointer:
     *       shape *Shp;
     *   - ray distance:
     *       DBL RayT;
     *   - entering flag:
     *       ENTER_TYPE EnterType;
     */
    intr( shape *Shp, DBL RayT, ENTER_TYPE EnterType = intr::ENTER ) :
      Shp(Shp), T(RayT), EnterFlag(EnterType),
      IsN(FALSE), IsP(FALSE)
    {
    } /* End of 'intr' function */
  }; /* End of 'intr' class */

  /* Intersection store class */
  struct intr_list : public stock<intr>
  {
  }; /* End of 'intr_list' structure */

  /* Environment class */
  class envi
  {
  public:
    DBL
      RefractionCoef,  // Refraction coefficient
      Decay;           // Environment media decay coefficient
  }; /* End of 'envi' class */

  /* Light information class */
  class light_info
  {
  public:
    vec3 L;     // Light source direction
    vec3 Color; // Light source color
    DBL Dist;   // Distance to light source
  }; /* End of 'light_info' class */

  /* Light class */
  class light
  {
  public:
    DBL Cc, Cl, Cq; // Attenuation coefficients
    //vec3 Color;   // Light source color

    /* Get shadow coefficient function.
     *   - shadow parametrs:
     *       const vec3 &P, light_info *L;
     * RETURNS:
     *   (DBL) shadow coef.
     */
    virtual DBL Shadow( const vec3 &P, light_info *L );
  }; /* End of 'light' class */

  /* Coefficient class */
  class coef
  {
  public:
    // Coefficient color value
    vec3 K;
 
    // Coefficient usage flag
    BOOL IsUsage;
 
    /* Class constructor */
    coef( VOID ) : IsUsage(FALSE)
    {
    } /* End of 'coef' function */
 
    /* Class constructor.
     * AGUMENTS:
     *   - color all components value:
     *       DBL C;
     */
    coef( DBL C ) : K(C, C, C), IsUsage(C > Theshold)
    {
    } /* End of 'coef' function */
 
    /* Class constructor.
     * AGUMENTS:
     *   - color component values:
     *       DBL R, G, Z;
     */
    coef( DBL X, DBL Y, DBL Z ) :
      K(X, Y, Z),
      IsUsage(X > Theshold ||
              Y > Theshold ||
              Z > Theshold)
    {
    } /* End of 'coef' function */
 
    /* Class constructor.
     * AGUMENTS:
     *   - color value:
     *       const vec3 &C;
     */
    coef( const vec3 &C ) :
      K(C),
      IsUsage(C.X > Theshold ||
              C.Y > Theshold ||
              C.Z > Theshold)
    {
    } /* End of 'coef' function */
 
    /* Coefficient set from vec3 function.
     * AGUMENTS:
     *   - color value:
     *       const vec3 &C;
     * RETURNS:
     *   (coef &) self reference.
     */
    coef & operator=( const vec3 &C )
    {
      K = C;
      IsUsage = C.X > Theshold ||
                C.Y > Theshold ||
                C.Z > Theshold;
      return *this;
    } /* End of 'operator=' constructor */
 
    /* Coefficient to vec3 color conversion function.
     * AGUMENTS: None.
     * RETURNS:
     *   (vec3) color value.
     */
    operator vec3( VOID ) const
    {
      return K;
    } /* End of 'operator color' function */
  }; /* End of 'coef' class */

  /* Surface class */
  class surface
  {
  public:
    coef Ka, Kd, Ks; // ambient, diffuse, specular
    DBL Ph;          // Bui Tong Phong coefficient
    coef Kr, Kt;     // reflected, transmitted
  }; /* End of 'surface' class*/ 
             
  /* Shading store info type */
  class shade_info
  {
  public:
    vec3 P;       // Point of shading evaluation
    vec3 N;       // Point normal
    surface Surf; // Surface material
    envi Env;     // Object media environment
 
    vec3 MapP;    // Mapping point of shading evaluation
    vec3 Du, Dv;  // Tangent vectors
    shape *Shp;   // Shape pointer
  }; /* End of 'shade_info' class */

  /* Scene class */
  class scene
  {
  public:
    stock<shape *> Shapes;                   // stock of shapes         
    vec3 BackgroundColor = vec3(0.1);//vec3(0.30, 0.47, 0.8); 
    // Sync flags
    std::atomic_bool IsRenderActive = FALSE; // is render active flag
    std::atomic_bool IsToBeStop = FALSE;     // is to be stopped flag
    std::atomic_bool IsReadyToFinish = TRUE; // is ready to finish flag
    INT RecLevel, MaxRecLevel = 8;           // recursion level
    envi Air;                                // air environment
     
    // Store rendering line
    std::atomic_int StartRow = 0;            // parallel row
    vec3 AmbientColor, FogColor = vec3(0);   // color
    DBL FogStart = 15, FogEnd = 30;          // fog parametrs
    stock<light *> Lights;                   // stock of lights

    virtual ~scene( VOID );                                        

    /* Add shape to stock function.
     *   - shape:
     *       shape *Shp;
     * RETURNS:
     *   (scene &) this scene.
     */
    scene &operator<<( shape *Shp )                          
    {                                                        
      Shapes << Shp;                                         
      return *this;                                          
    } /* End of 'operator<<' function */

    /* Add light to stock function.
     *   - light:
     *       shape *Lgh;
     * RETURNS:
     *   (scene &) this scene.
     */
    scene & operator<<( light *Lgh )
    {
      Lights << Lgh;
      return *this;
    } /* End of 'operator<<' function */

    /* Render scene function.
     *   - camera:
     *       camera &Cam;
     *   - frame:
     *       frame &Frm;
     * RETURNS: None.
     */
    virtual VOID Render( camera &Cam, frame &Frm );             

    /* Shade color function.
     *   - light:
     *       shape *Lgh;
     * RETURNS:
     *   (vec3) shaded color.
     */
    virtual vec3 Shade( const vec3 &V, const envi &Env, shade_info *Sh, DBL Weight, INT RecLevel );

    /* Add sphere to stock function.
     *   - sphere parametrs:
     *       const DBL &radius, const vec3 &centre, const vec3 &color, const envi &env, const surface &srf;
     * RETURNS: None.
     */
    virtual VOID AddSphere( const DBL &radius, const vec3 &centre, const vec3 &color, const envi &env, const surface &srf );           

    /* Add point light to stock function.
     *   - point light parametrs:
     *       const vec3 &pos, const vec3 &color, const DBL &dist, const vec3 &att;
     * RETURNS: None.
     */
    virtual VOID AddPointL( const vec3 &pos, const vec3 &color, const DBL &dist, const vec3 &att );

    /* Add triangle to stock function.
     *   - triangle paramtrs:
     *       const vec3 &p0, const vec3 &p1, const vec3 &p2, const vec3 &color, const envi &e, const surface &S;
     * RETURNS: None.
     */
    virtual VOID AddTriangle( const vec3 &p0, const vec3 &p1, const vec3 &p2, const vec3 &color, const envi &e, const surface &S );

    /* Add cylinder to stock function.
     *   - cylinder parametrs:
     *       const vec3 &C, const vec3 &Axis, const DBL &R, const vec3 &color, const envi &e, const surface &S;
     * RETURNS: None.
     */
    virtual VOID AddCylinder( const vec3 &C, const vec3 &Axis, const DBL &R, const vec3 &color, const envi &e, const surface &S );

    /* Add box to stock function.
     *   - box parametrs:
     *       const vec3 &B1, const vec3 &B2, const vec3 &color, const envi &e, const surface &S;
     * RETURNS: None.
     */
    virtual VOID AddBox( const vec3 &B1, const vec3 &B2, const vec3 &color, const envi &e, const surface &S );

    /* Add quadric to stock function.
     *   - quadric parametrs:
     *       const vec3 &col, const DBL &A, const DBL &B, const DBL &C, const DBL &D, const DBL &E, 
     *       const DBL &F, const DBL &G, const DBL &H, const DBL &I, const DBL &J, const envi &env, const surface &srf;
     * RETURNS: None.
     */
    virtual VOID AddQuadric( const vec3 &col, const DBL &A, const DBL &B, const DBL &C, const DBL &D, const DBL &E, const DBL &F, const DBL &G, const DBL &H, const DBL &I, const DBL &J, const envi &env, const surface &srf );

    /* Add plane to stock function.
     *   - plane parametrs:
     *       const DBL &d, const vec3 &n, const vec3 &color, const envi &env, const surface &srf;
     * RETURNS: None.
     */
    virtual VOID AddPlane( const DBL &d, const vec3 &n, const vec3 &color, const envi &env, const surface &srf );

    /* Finder intersection an object function.
     * ARGUMENTS:
     *   - ray:
     *       const ray &Ray;
     *   - intersection structure:
     *       intr_list &IList;
     *   (BOOL) Is intersect sign.
     */
    virtual BOOL IsIntersect( const ray &R );

    /* Find intersection with all objects function.
     * ARGUMENTS:
     *   - ray:
     *       const ray &Ray;
     *   - intersection structure:
     *       intr_list &IList;
     * RETURNS: None.
     */
    virtual INT AllIntersect( const ray &Ray, intr_list &IList );

    /* Finder intersection an object function.
     * ARGUMENTS:
     *   - ray:
     *       const ray &Ray;
     *   - intersection structure:
     *       intr_list &IList;
     *   (BOOL) Is intersect sign.
     */
    virtual BOOL Intersect( const ray &R, intr *Intr );    

    /* Trace ray function.
     *   - ray:
     *       const ray &R;
     *   - trace parametrs:
     *       const envi &Media, DBL Weight, INT RecLevel;
     * RETURNS:
     *   (vec3) traced ray's vector.
     */
    virtual vec3 Trace( const ray &R, const envi &Media, DBL Weight, INT RecLevel );
  }; /* End of 'scene' class */    

  /* Modifier class */
  class modifier
  {
  public:
    virtual ~modifier( VOID )
    {
    } /* End of '~modifier' function */

    /* Apply modification function.
     * ARGUMENTS:
     *   - shade information:
     *       shade_info *Sh;
     * RETURNS: None.
     */
    virtual VOID Apply( shade_info *Sh )
    {
    } /* End of 'Apply' function */
  }; /* End of 'modifier' class */

  /* Shape class */
  class shape                                                
  {                                                          
  public:                                                    
    surface Surf;           // surface
    envi Env;               // environment
    stock<modifier *> Mods; // modifications
    vec3 MinBB, MaxBB;

    virtual ~shape( VOID )
    {
      //for (auto &m : Mods)
      //  delete m;
    } /* End of '~shape' function */

    /* Finder intersection an object function.
     * ARGUMENTS:
     *   - ray:
     *       const ray &Ray;
     *   - intersection structure:
     *       intr_list &IList;
     *   (BOOL) Is intersect sign.
     */
    virtual BOOL IsIntersect( const ray &R );

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
    virtual INT AllIntersect( const ray &Ray, intr_list &IList );

    /* Check if ray starts inside function.
     * ARGUMENTS:
     *   - position:
     *       const vec3 &P;
     * RETURNS:
     *   (BOOL) Is inside sign.
     */
    virtual BOOL IsInside( const vec3 &P );

    /* Get shade information function.
     * ARGUMENTS:
     *   - shade information:
     *       shade_info *Sh;
     *   - intersection structure:
     *       intr *I;
     * RETURNS: None.
     */
    virtual VOID GetShadeInfo( shade_info *Sh, intr *I )
    {
      Sh->Shp = this;
 
      Sh->P = I->P;
      Sh->N = I->N;
      Sh->Surf = I->Shp->Surf;
      Sh->Env = I->Shp->Env;
 
      Sh->MapP = I->P;
      Sh->Du = vec3(1, 0, 0);
      Sh->Dv = vec3(0, 0, -1);
 
      for (auto m : Mods)
        m->Apply(Sh);
    } /* End of 'GetShadeInfo' function */

    /* Get shape bound function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    virtual VOID GetBound( VOID );
  }; /* End of 'shape' class */       
} /* End of 'arrt' namespace */

#endif /* __rt_def_h_ */                                     
                                                             
/* END OF 'rt_def.h' FILE */                                 
                                                             