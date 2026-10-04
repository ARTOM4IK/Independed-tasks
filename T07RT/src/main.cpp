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
 
#include "arrt.h"
 
/* The main program function */
INT main( VOID )
{
  return tst::RunAllTests();
} /* End of 'main' function */
 
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
  auto title = "CGSG Riy Tricing Console";
  SetConsoleTitle(title);

  HWND hCnsWnd = GetConsoleWindow();
  RECT rc;
  GetWindowRect(hCnsWnd, &rc);
  MoveWindow(hCnsWnd, 1920 - 500, 180, 500, 800, TRUE);

  //SetConsoleCtrlHandler(reinterpret_cast<PHANDLER_ROUTINE>(CtrlHandler), TRUE);

  CONSOLE_FONT_INFOEX cfi {.cbSize = sizeof(CONSOLE_FONT_INFO)};
  GetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
  cfi.dwFontSize.Y = 18;
  GetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);

  std::freopen("CONOUT&", "w", stdout);
  system("@chcp 1251 > nul");

  main();

  arrt::rt_win RT(hInstance);

  RT.Create();
  //RT << "default";
  //RT.Cam.SetLocAtUp(arrt::vec3(-7, 10, 20), arrt::vec3(0, 0, 0), arrt::vec3(0, 1, 0));
  //RT.Cam.SetLocAtUp(arrt::vec3(-7, 0, 20), arrt::vec3(0, 0, 0), arrt::vec3(0, 1, 0));

  RT.Cam.SetLocAtUp(arrt::vec3(0, 10, 3), arrt::vec3(-5, 6, 5), arrt::vec3(0, 1, 0));
  RT.Cam.SetLocAtUp(arrt::vec3(-5, 20, 6), arrt::vec3(-4, 6, 5), arrt::vec3(0, 1, 0));
  RT.Cam.SetLocAtUp(arrt::vec3(-5, 10, 6), arrt::vec3(0), arrt::vec3(0, 1, 0));
  RT.Cam.SetLocAtUp(arrt::vec3(0, 10, 14), arrt::vec3(0, 3, 0), arrt::vec3(0, 9, 0));

  arrt::surface surf;

  surf.Ka = arrt::coef(0.1745, 0.01175, 0.01175);
  surf.Kd = arrt::coef(0.61424, 0.04136, 0.04136);
  //surf.Ka = arrt::coef(1, 1, 0.01175);
  //surf.Kd = arrt::coef(1, 1, 0.04136);
  surf.Ks = arrt::coef(0.727811, 0.626959, 0.626959);
  surf.Ph = 76.8;
  surf.Kr = arrt::coef(0);
  surf.Kt = arrt::coef(1);
  RT.Scn.Air.RefractionCoef = 1;
  RT.Scn.Air.Decay = 1;

  arrt::surface plane_surf;

  plane_surf.Ka = arrt::coef(0.25, 0.25, 0.25);
  plane_surf.Kd = arrt::coef(0.4, 0.4, 0.4);
  //surf.Ka = arrt::coef(1, 1, 0.01175);
  //surf.Kd = arrt::coef(1, 1, 0.04136);
  plane_surf.Ks = arrt::coef(0.874597, 0.874597, 0.874597);
  plane_surf.Ph = 76.8;
  plane_surf.Kr = arrt::coef(0.0);
  plane_surf.Kt = arrt::coef(0);
//  plane_surf.Kt = arrt::coef(0.7);

  arrt::surface glass_surf;
  glass_surf.Ka = arrt::coef(0.0245, 0.11175, 0.12175);
  glass_surf.Kd = arrt::coef(0.015, 0.15, 0.2);
  //surf.Ka = arrt::coef(1, 1, 0.01175);
  //surf.Kd = arrt::coef(1, 1, 0.04136);
  glass_surf.Ks = arrt::coef(0.4, 0.4, 0.4);
  glass_surf.Ph = 76.8;
  glass_surf.Kr = arrt::coef(0);
  glass_surf.Kt = arrt::coef(0.8);

  arrt::surface tr_surf;
  tr_surf.Ka = arrt::coef(0.0215, 0.1745, 0.0215);
  tr_surf.Kd = arrt::coef(0.07568, 0.61424, 0.07568);
  //surf.Ka = arrt::coef(1, 1, 0.01175);
  //surf.Kd = arrt::coef(1, 1, 0.04136);
  tr_surf.Ks = arrt::coef(0.633, 0.727811, 0.633);
  tr_surf.Ph = 76.8;
  tr_surf.Kr = arrt::coef(0.0);
  tr_surf.Kt = arrt::coef(0.8);

  arrt::envi env;
  env.Decay = 1;
  env.RefractionCoef = 1;

  //RT.Scn.AddPlane(0, arrt::vec3(0, 1, 0), arrt::vec3(1, 0, 0), env, plane_surf);
  auto p = new arrt::plane(5.001, arrt::vec3(0, 1, 0), arrt::vec3(1, 0, 0), env, plane_surf);
  p->Mods.push_back(new arrt::mods::checker(0, 1));
  //RT.Scn.Shapes << p;
   
  arrt::torus *t = new arrt::torus (2, 1, arrt::vec3(0), arrt::vec3(0), env, surf);

  arrt::trimesh *model = new arrt::trimesh;
  model->AddModel("bin/models/cow.g3dm", arrt::matr::Scale(arrt::vec3(0.8)) * arrt::matr::RotateY(-42));
  arrt::bicubic *bic = new arrt::bicubic(env, surf);
  //arrt::triangle *tr = new arrt::triangle(arrt::vec3(0), arrt::vec3(0, 1, 0), arrt::vec3(1, 1, 0), arrt::vec3(1), env, surf);
  //arrt::triangle *tr1 = new arrt::triangle(arrt::vec3(0), arrt::vec3(1, 0, 0), arrt::vec3(1, 1, 0), arrt::vec3(1), env, surf);
  //bic->Load("bin/bicubic/TEACUP.TXT");
  //tr->Mods.push_back(new arrt::mods::checker(1, 0));
  for ( auto &tr : model->Triangles)
  {
    tr.Mods.push_back(new arrt::mods::test(arrt::vec3(1, 0, 1)));
    //tr.Mods.push_back(new arrt::mods::texture(model->Textures[0], tr.u0, tr.v0, tr.V1, tr.U1, tr.t0, tr.t1, tr.t2));
  }

  RT.Scn.Shapes << model;
  
  RT.Scn.AddPointL(arrt::vec3(0), arrt::vec3(1, 0, 0), 5, arrt::vec3(0.5, -0.001, 0));
  //RT.Scn.AddPointL(arrt::vec3(-5, -2, 5), arrt::vec3(1, 0, 0), 5, arrt::vec3(0.5, 0.001, 0));

  RT.Run();

  if (RT.Scn.IsRenderActive)
  {
    RT.Scn.IsToBeStop = TRUE;
    std::cout << "\nWait rendering threads are finished\n";
    while (!RT.Scn.IsReadyToFinish)
      ;
    std::cout << "\nWaiting is finished\n";
  }
  std::cout << "\nFinish...\n";

  std::fclose(stdout);
  FreeConsole();
  return 30;
} /* End of 'WinMain' function */

/* End of 'main.cpp' function */
