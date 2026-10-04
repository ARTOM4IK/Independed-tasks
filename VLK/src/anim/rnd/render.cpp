/*************************************************************
 * Copyright (C) 2025
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : render.cpp
 * PURPOSE     : Ray Tracing project.
 *               Precompiled header definition module.
 * PROGRAMMER  : CGSG-SummerCamp'2025.
 *               Artmey V. Arsentev.
 * LAST UPDATE : 23.07.2025.
 * NOTE        : Module namespace 'virt'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#include "arvk.h"
           
#pragma comment(lib, "vulkan-1.lib")

/* Init render function.
 * ARGUMENTS: None.
 * RETURNS:
 *   None.
 */
VOID arvk::render::Init( VOID )
{
  if (IsRenderInit)
    return;

  CreateInstance();
  CreateDebug(Instance);
  CreateDevice(Instance);
  INT W = 1040, H = 720;
  CreateContext(hWndRef, Instance);
  CreateSwapchain(Device, PhysDevice, Surface, W, H);
  CreateRenderPass(Device, SwapchainImageFormat);
  CreateFrameBuffer(Device, RenderPass, SwapchainImageViews, ClampedW, ClampedH);
  CreateCommandQueue(Device, PhysDevice, Surface);
  CreateCommandBuffer(Device);
  CreateFence(Device);
  CreateSemaphores(Device);
  CreateDescriptorLayout(Device);
  CreateMaterialDescriptorLayout(Device);
  shader *Shd = ShdCreate("test");
  CreatePipelineLayout(Device);
  CreatePipeline(Device, RenderPass, Shd, ClampedW, ClampedH);
  CreateDescriptorPool(Device);
  CreateDescriptorSet(Device, DescriptorSetLayout);

  Cam.SetLocAtUp(vec3(1, 0, 0), vec3(0), vec3(0, 1, 0));

  //std::vector<vertex::std> V {{{0.5, 0, -0.25}}, {{0, 1, 0.25}}, {{-0.5, 0, 0.0}}};
  //V[0].P = Cam.VP.TransformPoint(V[0].P);
  //V[1].P = Cam.VP.TransformPoint(V[1].P);
  //V[2].P = Cam.VP.TransformPoint(V[2].P);
  //std::vector<INT> Ind {0, 1, 2};
  BufSync = buffer_manager::BufCreate<BUF_SYNC>(1, nullptr);

  //VertexBuf.CreateBuffer(Device, PhysDevice, BYTE(V.size() * sizeof(vertex::std)), VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, VK_SHARING_MODE_EXCLUSIVE);
  //IndexBuffer.CreateBuffer(Device, PhysDevice, BYTE(Ind.size() * sizeof(INT)), VK_BUFFER_USAGE_INDEX_BUFFER_BIT, VK_SHARING_MODE_EXCLUSIVE);
  //VertexBuf.BufferWrite(Device, PhysDevice, BYTE(V.size() * sizeof(vertex::std)), V.data());
  //IndexBuffer.BufferWrite(Device, PhysDevice, BYTE(Ind.size() * sizeof(INT)), Ind.data());

  BUF_SYNC bs
  {
    vec4(Timer.GlobalDeltaTime, Timer.GlobalDeltaTime, Timer.Time, Timer.DeltaTime)
  };
  //BufSync->Update(&bs);
  BufSync->CreateData(&bs, sizeof(bs), 0);
  //DescriptorBufferFill(BufSync->Buffer, Device, sizeof(bs), 0, 0);

  BUF_CAM bc
  {
    Cam.View.M,
    Cam.Proj.M,
    Cam.VP.M,
    vec4(Cam.Loc, Cam.FrameW),
    vec4(Cam.Dir, Cam.ProjDist),
    vec4(Cam.Right, Cam.Wp),
    vec4(Cam.Up, Cam.Hp),
    vec4(Cam.At, Cam.FrameH),
    vec4(Cam.Wp, Cam.Hp, Cam.Size, Cam.ProjDist)
  };
  BufCam = buffer_manager::BufCreate<BUF_CAM>(1, nullptr);
  BufCam->CreateData(&bc, sizeof(bc), sizeof(bs));
  //DescriptorBufferFill(BufCam->Buffer, Device, sizeof(bc), 1, /*0*/sizeof(bs));

  VkDescriptorBufferInfo BufferInfo1
  {
    .buffer = BufSync->Buffer,          // Buffer to be written in this descriptor.
    .offset = 0,          // Offset in bytes.
    .range = sizeof(bs), // Buffer size.
  };
  VkDescriptorBufferInfo BufferInfo2
  {
    .buffer = BufCam->Buffer,          // Buffer to be written in this descriptor.
    .offset = 0/*sizeof(bs)*/,          // Offset in bytes.
    .range = sizeof(bc), // Buffer size.
  };

  // Only one descriptor.
  std::array<VkWriteDescriptorSet, 2> DescriptorWrites;

  DescriptorWrites[0].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
  DescriptorWrites[0].dstSet = DescriptorSet;                             
  DescriptorWrites[0].dstBinding = 0;                                     
  DescriptorWrites[0].dstArrayElement = 0;                                
  DescriptorWrites[0].descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER /*VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER*/; 
  DescriptorWrites[0].descriptorCount = 1;                                
  DescriptorWrites[0].pBufferInfo = &BufferInfo1;                          
  DescriptorWrites[0].pNext = nullptr;                          

  DescriptorWrites[1].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
  DescriptorWrites[1].dstSet = DescriptorSet;                             
  DescriptorWrites[1].dstBinding = 1;                                     
  DescriptorWrites[1].dstArrayElement = 0;                                
  DescriptorWrites[1].descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER /*VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER*/; 
  DescriptorWrites[1].descriptorCount = 1;                                
  DescriptorWrites[1].pBufferInfo = &BufferInfo2;                          
  DescriptorWrites[1].pNext = nullptr;                          

  vkUpdateDescriptorSets(Device, (UINT)DescriptorWrites.size(), DescriptorWrites.data(), 0, nullptr);
  //BUF_PRIM bp
  //{
  //  matr::Identity(), matr::Identity(), matr::Identity(), vec4(0, 0, 0, 0)
  //};
  //BufPrim = buffer_manager::BufCreate<BUF_PRIM>(1, nullptr);
  //BufPrim->CreateData(&bp, sizeof(bp), sizeof(bp));
  //DescriptorBufferFill(BufPrim->Buffer, Device, sizeof(bp), 2, 0);
} /* End of 'Init' function */
 
/* Close render function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID arvk::render::Close( VOID )
{
  //BufPrim->Free();
  BufSync->Free();
  BufCam->Free();
  for (INT i = 0; i < 4; i++)
    BufferFree(StageBuffer[i], StageBufferAllocation[i]);
  //VertexBuf.DestroyBuffer(Device);
  //IndexBuffer.DestroyBuffer(Device);
  DestroyDescriptorPool(Device);
  DestroyPipeline(Device);
  DestroyPipelineLayout(Device);
  shader *Shd = shader_manager::Find("test");
  Shd->Destroy();
  arvk::primitive_manager::Clear();
  DestroyMaterialDescriptorLayout(Device);
  DestroyDescriptorLayout(Device);
  DestroySemaphores(Device);
  DestroyFence(Device);
  DestroyCommandQueue(Device);
  DestroyFrameBuffer(Device);
  DestroyRenderPas(Device);
  DestroySwapchain(Device);  
  DestroyContext(Instance);
  DestroyDevice(Instance);
  DestroyDebug(Instance);
  DestroyInstance();
  ReleaseDC(hWndRef, hDC);
} /* End of 'Close' function */
 
/* Resize function.
 * ARGUMENTS:
 *   - Window size:
 *       INT W, INT H;
 * RETURNS: None.
 */
VOID arvk::render::Resize( INT NewW, INT NewH )
{
  /* Setup projection */
  FrameW = NewW;
  FrameH = NewH;
  ResizeSwapchain(PhysDevice, Device, Surface, NewW, NewH, RenderPass);

  /* Recalculate projection */
  Cam.Resize(FrameW, FrameH);
} /* End of 'Resize' function */
 
/* Start of render function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID arvk::render::FrameStart( VOID )
{
  // Queue sync
  vkWaitForFences(Device, 1, &Fence[CurrentFrame], VK_TRUE, UINT64_MAX);
  vkResetFences(Device, 1, &Fence[CurrentFrame]);
 
  vkAcquireNextImageKHR(Device, Swapchain, UINT64_MAX,
                        ImageAvailableSemaphores[CurrentFrame], VK_NULL_HANDLE, &ActiveSwapchainImage);
 
  // Reset & start command buffer
  vkResetCommandBuffer(CommandBuffer[CurrentFrame], 0);
 
  VkCommandBufferBeginInfo CommandBufferBeginInfo
  {
    .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
    .pInheritanceInfo = nullptr,
  };
  //vkEndCommandBuffer(CommandBuffer[CurrentFrame]);
  vkBeginCommandBuffer(CommandBuffer[CurrentFrame], &CommandBufferBeginInfo);
  //GraphicsPipelineUpdate();
  //RenderPassStart();

  /*
  // Queue sync
  switch (vkWaitForFences(Device, 1, &Fence, VK_TRUE, UINT64_MAX))
  {
  case VK_SUCCESS:
    break;
  case VK_TIMEOUT:
    throw "Fence timeout at frame start";
  }
  vkResetFences(Device, 1, &Fence);

  // Reset & start command buffer
  vkResetCommandBuffer(CommandBuffer, 0);
  */

  BUF_SYNC bs
  {
    vec4(Timer.GlobalDeltaTime, Timer.GlobalDeltaTime, Timer.Time, Timer.DeltaTime)
  };
  BufSync->Update(&bs, sizeof(bs));
  BUF_CAM bc
  {
    Cam.View.M,
    Cam.Proj.M,
    Cam.VP.M,
    vec4(Cam.Loc, Cam.FrameW),
    vec4(Cam.Dir, Cam.ProjDist),
    vec4(Cam.Right, Cam.Wp),
    vec4(Cam.Up, Cam.Hp),
    vec4(Cam.At, Cam.FrameH),
    vec4(Cam.Wp, Cam.Hp, Cam.Size, Cam.ProjDist)
  };
  BufCam->Update(&bc, sizeof(bc));

  shader_manager::Update();
  
  //std::vector<vertex::std> V {{{0.5, 0, 0.0}, {1.00, 0.00, 0.47, 1.00}}, {{-0.0, 0.5, 0.0}, {0.00, 1.0, 0.00, 1.00}}, {{-0.5, 0.0, 0.0}, {0.00, 0.00, 1.00,1.00}}};
  //V[0].P = (matr::RotateY(Timer.Time * 30) * Cam.VP).TransformPoint(V[0].P);
  //V[1].P = (matr::RotateY(Timer.Time * 30) * Cam.VP).TransformPoint(V[1].P);
  //V[2].P = (matr::RotateY(Timer.Time * 30) * Cam.VP).TransformPoint(V[2].P);
  //std::vector<INT> Ind {0, 1, 2};
  //VertexBuf.DestroyBuffer(Device);
  //IndexBuffer.DestroyBuffer(Device);
  //
  //VertexBuf.CreateBuffer(Device, PhysDevice, BYTE(V.size() * sizeof(vertex::std)), VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, VK_SHARING_MODE_EXCLUSIVE);
  //IndexBuffer.CreateBuffer(Device, PhysDevice, BYTE(Ind.size() * sizeof(INT)), VK_BUFFER_USAGE_INDEX_BUFFER_BIT, VK_SHARING_MODE_EXCLUSIVE);  
  //VertexBuf.BufferWrite(Device, PhysDevice, BYTE(V.size() * sizeof(vertex::std)), V.data());
  //IndexBuffer.BufferWrite(Device, PhysDevice, BYTE(Ind.size() * sizeof(INT)), Ind.data());  

  /*
  vkAcquireNextImageKHR(Device, Swapchain, UINT64_MAX, VK_NULL_HANDLE, Fence, &ActiveSwapchainImage);

  VkCommandBufferBeginInfo CommandBufferBeginInfo
  {
    .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
    .pInheritanceInfo = nullptr,
  };
  vkBeginCommandBuffer(CommandBuffer, &CommandBufferBeginInfo);
  */
  //Renderpass start
 
  //if (GraphicsPipeline != VK_NULL_HANDLE)
  //{
  //  vkCmdBindPipeline(CommandBuffers[CurrentFrame], VK_PIPELINE_BIND_POINT_GRAPHICS, GraphicsPipeline);
  //  vkCmdBindDescriptorSets(CommandBuffers[CurrentFrame], VK_PIPELINE_BIND_POINT_GRAPHICS,
  //    GraphicsPipelineLayout, 0, 1, &FrameDescriptorSet, 0, nullptr);
  //  vkCmdBindDescriptorSets(CommandBuffers[CurrentFrame], VK_PIPELINE_BIND_POINT_GRAPHICS,
  //    GraphicsPipelineLayout, 1, 1, &FrameDescriptorSet, 0, nullptr);
  //  vkCmdBindDescriptorSets(CommandBuffers[CurrentFrame], VK_PIPELINE_BIND_POINT_GRAPHICS,
  //    GraphicsPipelineLayout, 3, 1, &SyncDescriptorSet, 0, nullptr);
  //}

  std::array<VkClearValue, 2> ClearValues {};
  ClearValues[0].color = {{0.3f, 0.47f, 0.8f, 1.0f}};
  ClearValues[1].depthStencil = {1.0f, 0};
  
  VkRenderPassBeginInfo RenderPassBeginInfo
  {
    .sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO,
    .renderPass = RenderPass,
    .framebuffer = FrameBuffers[ActiveSwapchainImage],
    .renderArea {.offset {.x = 0, .y = 0}, .extent {.width = UINT32(ClampedW), .height = UINT32(ClampedH)}},
    .clearValueCount = static_cast<UINT32>(ClearValues.size()),
    .pClearValues = ClearValues.data()
  };  
  vkCmdBeginRenderPass(CommandBuffer[CurrentFrame], &RenderPassBeginInfo, VK_SUBPASS_CONTENTS_INLINE);

  vkCmdBindPipeline(CommandBuffer[CurrentFrame], VK_PIPELINE_BIND_POINT_GRAPHICS, Pipeline);
  vkCmdBindDescriptorSets(CommandBuffer[CurrentFrame], VK_PIPELINE_BIND_POINT_GRAPHICS, PipelineLayout, 0, 1, &DescriptorSet, 0, nullptr);

  VkViewport Viewport
  {
    .x = 0.0f,
    .y = static_cast<FLT>(ClampedH), 
    .width = static_cast<FLT>(ClampedW),
    .height = -static_cast<FLT>(ClampedH),
    .minDepth = 0.0f,
    .maxDepth = 1.0f,
  };
  vkCmdSetViewport(CommandBuffer[CurrentFrame], 0, 1, &Viewport);
  VkRect2D Scissor
  {
    .offset {.x = 0, .y = 0},
    .extent {.width = UINT32(ClampedW), .height = UINT32(ClampedH)}
  };
  vkCmdSetScissor(CommandBuffer[CurrentFrame], 0, 1, &Scissor);
  //vkCmdSetPrimitiveTopology(CommandBuffer, VK_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP);
  //VkBuffer VertexBuffers[] = {VertexBuf.Buffer}; 
  //VkDeviceSize Offsets[] = {0};               

  //vkCmdBindVertexBuffers(CommandBuffer, 0, 1, VertexBuffers, Offsets);
  //vkCmdBindIndexBuffer(CommandBuffer, IndexBuffer.Buffer, 0, VK_INDEX_TYPE_UINT32);

  //vkCmdDraw(CommandBuffer, 3/*VerticesCount*/, 1, 0, 0);
} /* End of 'FrameStart' function */
 
/* End of render function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID arvk::render::FrameEnd( VOID )
{
  vkCmdEndRenderPass(CommandBuffer[CurrentFrame]);
  vkEndCommandBuffer(CommandBuffer[CurrentFrame]);

  VkPipelineStageFlags WaitPipelineStageFlags[] = {VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT};
  VkSemaphore WaitSemaphores[] = {ImageAvailableSemaphores[CurrentFrame]};
  VkSemaphore SignalSemaphores[] = {RenderFinishSemaphores[CurrentFrame]};
  VkSubmitInfo SubmitInfo
  {
    .sType = VK_STRUCTURE_TYPE_SUBMIT_INFO,
    .waitSemaphoreCount = 1,
    .pWaitSemaphores = WaitSemaphores,
    .pWaitDstStageMask = WaitPipelineStageFlags,
    .commandBufferCount = 1,
    .pCommandBuffers = &CommandBuffer[CurrentFrame],
    .signalSemaphoreCount = 1,
    .pSignalSemaphores = SignalSemaphores,
  };
  vkQueueSubmit(GraphicsQueue, 1, &SubmitInfo, Fence[CurrentFrame]);
 
  VkPresentInfoKHR PresentInfo
  {
    .sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR,
    .waitSemaphoreCount = 1,
    .pWaitSemaphores = SignalSemaphores,
    .swapchainCount = 1,
    .pSwapchains = &Swapchain,
    .pImageIndices = &ActiveSwapchainImage,
    .pResults = nullptr
  };
  vkQueuePresentKHR(PresentQueue, &PresentInfo);
  /*
  vkWaitForFences(Device, 1, &Fence, TRUE, UINT64_MAX);
  vkResetFences(Device, 1, &Fence);



  VkPipelineStageFlags PipelineStageFlags[] = {VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT};
  VkSubmitInfo SubmitInfo
  {
    .sType = VK_STRUCTURE_TYPE_SUBMIT_INFO,
    .waitSemaphoreCount = 0,
    .pWaitDstStageMask = PipelineStageFlags,
    .commandBufferCount = 1,
    .pCommandBuffers = &CommandBuffer
  };
  vkQueueSubmit(GraphicsQueue, 1, &SubmitInfo, Fence);

  VkPresentInfoKHR PresentInfo
  {
    .sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR,
    .pWaitSemaphores = 0,
    .swapchainCount = 1,
    .pSwapchains = &Swapchain,
    .pImageIndices = &ActiveSwapchainImage,
    .pResults = nullptr
  };
  vkWaitForFences(Device, 1, &Fence, TRUE, UINT64_MAX);
  vkQueuePresentKHR(PresentQueue, &PresentInfo);
  */
  CurrentFrame = (CurrentFrame + 1) % 3;
} /* End of 'FrameEnd' function */

/* Copy frame function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID arvk::render::ChangeWireMode( BOOL &IsWire )
{
  //vkCmdSetPolygonModeEXT(CommandBuffer, IsWire == TRUE ? VK_POLYGON_MODE_FILL : VK_POLYGON_MODE_LINE);
} /* End of 'CopyFrame' function */

/* Primitive draw function.
  * ARGUMENTS:
  *   - primitive pointer:
  *       prim *Pr;
  *   - transformation matrix:
  *       const matr &World;
  * RETURNS: None.
  */
VOID arvk::render::Draw( const prim *Pr, const matr &World )
{
  matr
    w = Pr->Transform * World,
    wvp = w * Cam.VP,
    invw = w.Inverse();

  // shaders
  BUF_PRIM bp
  {
    wvp, w, invw, vec4(0, 0, 0, 0)
  };
  PUSH_CONST pc
  {
    wvp.M, w.M,
    vec4(Pr->Mtl->Ka, 0),
    vec4(Pr->Mtl->Kd, Pr->Mtl->Trans),
    vec4(Pr->Mtl->Ks, Pr->Mtl->Ph)
  };

  //BufPrim->Update(&bp, sizeof(bp));

  VkBuffer VertexBuffers[] = {Pr->VertexBuf.Buffer}; 
  VkDeviceSize Offsets[] = {0};               

  vkCmdBindVertexBuffers(CommandBuffer[CurrentFrame], 0, 1, VertexBuffers, Offsets);
  vkCmdBindIndexBuffer(CommandBuffer[CurrentFrame], Pr->IndexBuffer.Buffer, 0, VK_INDEX_TYPE_UINT32);
  vkCmdPushConstants(CommandBuffer[CurrentFrame], PipelineLayout, VK_SHADER_STAGE_ALL_GRAPHICS, 0, sizeof(pc), &pc);
  //vkCmdPushConstants(CommandBuffer, PipelineLayout, VK_SHADER_STAGE_ALL_GRAPHICS, 0/*sizeof(pc)*/, sizeof(pm), &pm);

  //update material descripor set
  VkDescriptorSet descriptorSets[2] = { DescriptorSet, Pr->Mtl->DescriptorSet};
  vkCmdBindDescriptorSets(CommandBuffer[CurrentFrame], VK_PIPELINE_BIND_POINT_GRAPHICS, PipelineLayout, 0, 2, descriptorSets, 0, nullptr);

  vkCmdDrawIndexed(CommandBuffer[CurrentFrame], Pr->NumOfElements, 1, 0, 0, 0);
  //vkCmdDraw(CommandBuffer, Pr->NumOfElements, 1, 0, 0);
} /* End of 'Draw' function */

/* Draw model render function.
 *  ARGUMENTS:
 *   - pointer to model:
 *      model *Mdl;
 *   - world matrix:
 *       &World;
 * RETURNS: None.
 */
VOID arvk::render::Draw( const model &Mdl, const matr &World )
{
  matr m = Mdl.Transform * World;
  //vkCmdSetCullMode(CommandBuffer, VK_CULL_MODE_FRONT_AND_BACK);
  for (auto pr : Mdl.Prims)
    if (pr->Mtl == nullptr || pr->Mtl->Trans == 1)
      Draw(pr, m);
  //for (auto pr : Mdl.Prims)
  //  if (pr->Mtl != nullptr && pr->Mtl->Trans != 1)
  //    Draw(pr, m);
  //for (auto pr : Mdl.Prims)
  //  if (pr->Mtl != nullptr && pr->Mtl->Trans != 1)
  //    Draw(pr, m);
}

/* END OF 'render.cpp' FILE */
