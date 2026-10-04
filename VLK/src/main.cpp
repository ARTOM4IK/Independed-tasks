/*************************************************************
 * Copyright (C) 2025
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : main.cpp
 * PURPOSE     : Ray Tracing project.
 *               Main startup module.
 * PROGRAMMER  : CGSG-SummerCamp'2025.
 *               Artemy V. Arsentev
 * LAST UPDATE : 23.07.2025.
 * NOTE        : Module namespace 'virt'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */
 
#include "arvk.h"
 
/* The main program function */
INT main( VOID )
{
} /* End of 'main' function */

/* Animation namespace */
namespace arvk
{
  /* my_unit class */
  class my_unit: public unit
  {
  private:
    model *mdl;
    prim *Pr, *Pr1;
    //model *mtl;
  public:
    my_unit( anim *Ani )
    {
      //mdl = Ani->model_manager::ModelCreate("bin/models/hollow_knight.g3dm");
      //mdl = Ani->model_manager::ModelCreate("bin/models/trump1/scene.gltf");
      //mdl = Ani->model_manager::ModelCreate("bin/models/knight/scene.gltf");
      //mdl = Ani->model_manager::ModelCreate("bin/models/Strawberry.gltf");
      std::vector<vertex::std> V {{{0.5, 0, -0.25}}, {{0, 1, 0.25}}, {{-0.5, 0, 0.0}}};
      std::vector<vertex::std> V1 {{{0.2, 0, -0.1}}, {{0, 1, 0.1}}, {{-0.8, 0, 0.3}}, {{-1.2, 1.2, 0.1}}};
      std::vector<INT> Ind {0, 1, 2, 3};

      //Pr = Ani->primitive_manager::PrimCreate(arvk::prim_type::TRIMESH, std::span(V), std::span(Ind));
      //Pr1 = Ani->primitive_manager::PrimCreate(arvk::prim_type::TRIMESH, std::span(V1), std::span(Ind));
      //Pr1->Mtl = Ani->material_manager::MtlCreate("zzz");
      //Pr1->Mtl->Ka = vec3(1);
      //Pr1->Mtl->Kd = vec3(1);
      //Pr1->Mtl->Ks = vec3(1);
      //Pr1->Mtl->Trans = 1;
      //Pr1->Mtl->Ph = 1;
    }

    VOID Render( anim *Ani ) override
    {
      //Ani->Draw(Pr, matr::RotateY(Ani->Timer.Time * 30));
      Ani->Draw(Pr1/*, matr::Scale(vec3(0.1))*/);
      //Ani->Draw(*mdl, matr::Translate(vec3(0, 1, 0.7)));
    } /* End of 'Render' function */

    VOID Response( anim *Ani ) override
    {
    } /* End of 'Response' function */
  }; /* End of 'my_unit' class*/

  class animated_knight_unit : public unit 
  {
  private:
    animated_model_wrapper* Knight = nullptr;
    
  public:
    animated_knight_unit( anim* Ani ) 
    {
      Knight = new animated_model_wrapper(Ani);
        
      if (Knight->Load("bin/models/knight/scene.gltf"))
      {
        std::cout << "Animated knight loaded successfully!\n";
        Knight->Play();
        Knight->SetSpeed(1.0f);
      }
      else
      {
        std::cout << "Failed to load animated knight\n";
      }
    }
    
    VOID Render( anim* Ani ) override 
    {
      if (!Knight || !Knight->GetModel()) 
        return;
        
      Ani->Draw(*Knight->GetModel(), matr::Identity());
    }
    
    VOID Response( anim* Ani ) override 
    {
      if (!Knight)
        return;
        
      Knight->UpdateAnimation(Ani->Timer.DeltaTime);
        
      static BOOL isPlaying = TRUE;
        
      if (Ani->KeysClick[VK_SPACE]) 
      {
        if (isPlaying)
        {
          Knight->Pause();
          isPlaying = FALSE;
          std::cout << "Animation paused\n";
        } 
        else
        {
          Knight->Play();
          isPlaying = TRUE;
          std::cout << "Animation playing\n";
        }
      }
        
      if (Ani->KeysClick['+']) 
      {
        FLT newSpeed = Knight->GetSpeed() * 1.2f;
        Knight->SetSpeed(newSpeed);
        std::cout << "Speed: " << newSpeed << "\n";
      }
        
      if (Ani->KeysClick['-']) 
      {
        FLT newSpeed = Knight->GetSpeed() * 0.8f;
        Knight->SetSpeed(newSpeed);
        std::cout << "Speed: " << newSpeed << "\n";
      }
        
      if (Ani->KeysClick['R']) 
      {
        Knight->Pause();
        Knight->Play();
        std::cout << "Animation restarted\n";
      }
    }
    
    ~animated_knight_unit( VOID ) 
    {
      delete Knight;
    }
  };
} /* End of 'arvk' mamespace */

/* The main program function.
 * ARGUMENTS:
 *   - handle of application instance:
 *       HINSTANCE hInstance;
 *   - dummy handle of previous application instance (not used):
 *       HINSTANCE hPrevInstance;
 *   - command line string:
 *       CHAR *CmdLine;
 *   - show window command parameter (see SW_***):
 *       INT CmdShow;
 * RETURNS:
 *   (INT) Error level for operation system (0 for success).
 */
INT WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,
                    CHAR *CmdLine, INT ShowCmd )
{
  AllocConsole();

  std::freopen("CONOUT$", "w", stdout);
  std::freopen("CONOUT$", "w", stderr);
  std::freopen("CONIN$", "r", stdin);

  system("@chcp 1251 > nul");
  SetConsoleTitle("CGSG Vulkan Animation");
  std::cout << "CGSG FOREVER\n";
  tst::RunAllTests();
  //arvk::anim MyAnim(hInstance);

  //MyAnim.Create();  
  //MyAnim << new arvk::skybox_unit(MyAnim);
  //MyAnim << new arvk::control_unit(MyAnim);
  //MyAnim << new arvk::my_unit(MyAnim);
  //MyAnim.Run();

  //std::thread Second([hInstance]( VOID )
  //{
  //  arvk::anim My1(hInstance);
  //  My1.Create();
  //  My1 << new arvk::control_unit(&My1);
  //  My1 << new arvk::my_unit(&My1);
  //  My1.Run();
  //});
  arvk::anim My(hInstance);
  My.Create();
  My << new arvk::control_unit(&My);
  //My << new arvk::my_unit(&My);
  My << new arvk::animated_knight_unit(&My);
  My.Run();
  //Second.join();

} /* End of 'WinMain' function */

/* End of 'main.cpp' function */
