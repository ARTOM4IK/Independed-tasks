/*************************************************************
 * Copyright (C) 2025
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : vlk_instance.cpp
 * PURPOSE     : Vulkan animation project.
 *               Vulkan module.
 * PROGRAMMER  : CGSG-FallCamp'2025.
 *               Artmey V. Arsentev.
 * LAST UPDATE : 29.10.2025.
 * NOTE        : Module namespace 'arvk'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#include "arvk.h"

/* Create instance function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID arvk::VlkInstance::CreateInstance( VOID )
{
  // Informtaional application structure.
  VkApplicationInfo AppInfo 
  {
    .sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
    .pApplicationName = "Damn",
    .applicationVersion = 1,
    .apiVersion = VK_MAKE_VERSION(1, 4, 0),   // VulkanAPI version.
  };
  

  // Informtaional instance structure.
  VkInstanceCreateInfo InstanceCreateInfo 
  {
    .sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
    .pApplicationInfo = &AppInfo,
  };

  // Instance extensions.
  std::vector<const CHAR *> InstanceExtensionNames 
  {
    #if defined(_DEBUG)
      "VK_EXT_debug_utils",  // Debug extentions.
      "VK_EXT_debug_report",
    #endif
    //"VK_EXT_layer_settings",
    "VK_KHR_surface",
    "VK_KHR_win32_surface" // Window extentions.
  };

    // Instance layers. 
    std::vector<const CHAR *> EnabledLayersNames
    {
      #if defined(_DEBUG)
        "VK_LAYER_KHRONOS_validation"   // Validation layer.
      #endif
    };

  #if defined(_DEBUG)
    // Validation abilities.
    VkValidationFeaturesEXT ValidationFeatures 
    {
      .sType = VK_STRUCTURE_TYPE_VALIDATION_FEATURES_EXT,
    };

  std::vector<VkValidationFeatureEnableEXT> ValidationFeaturesEnable
  {
    VK_VALIDATION_FEATURE_ENABLE_GPU_ASSISTED_EXT,    // Shader validation.
    VK_VALIDATION_FEATURE_ENABLE_BEST_PRACTICES_EXT   // Additional warnings output.
  };
  #endif

  InstanceCreateInfo.enabledExtensionCount = (UINT32)InstanceExtensionNames.size();
  InstanceCreateInfo.ppEnabledExtensionNames = InstanceExtensionNames.data();
  InstanceCreateInfo.enabledLayerCount = (UINT32)EnabledLayersNames.size();
  InstanceCreateInfo.ppEnabledLayerNames = EnabledLayersNames.data();

  #if defined(_DEBUG)
    ValidationFeatures.enabledValidationFeatureCount = (UINT32)ValidationFeaturesEnable.size();
    ValidationFeatures.pEnabledValidationFeatures = ValidationFeaturesEnable.data();
  #endif

  InstanceCreateInfo.pNext = nullptr;
  #if defined(_DEBUG)
    InstanceCreateInfo.pNext = &ValidationFeatures;
  #endif

  // Disable ray query
  //VkBool32 validateQuery = VK_FALSE;

  //VkLayerSettingEXT LayerSettings = 
  //{
  //  .pLayerName = "VK_LAYER_KHRONOS_validation",
  //  .pSettingName = "gpuav_validate_ray_query",
  //  .type = VK_LAYER_SETTING_TYPE_BOOL32_EXT,
  //  .valueCount = 1,
  //  .pValues = &validateQuery
  //};

  //VkLayerSettingsCreateInfoEXT LayerSettingCreateInfo =
  //{
  //  .sType = VK_STRUCTURE_TYPE_LAYER_SETTINGS_CREATE_INFO_EXT,
  //  .pNext = nullptr,
  //  .settingCount = 1,
  //  .pSettings = &LayerSettings
  //};

  //InstanceCreateInfo.pNext = &LayerSettingCreateInfo;

  #if defined(_DEBUG)
    // Create debug callback.
    VkDebugReportCallbackCreateInfoEXT DebugReportCallbackInfo {};
    DebugReportCallbackInfo.sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CALLBACK_CREATE_INFO_EXT;

    DebugReportCallbackInfo.sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CALLBACK_CREATE_INFO_EXT;
    DebugReportCallbackInfo.pNext = nullptr;
    DebugReportCallbackInfo.flags =
      VK_DEBUG_REPORT_INFORMATION_BIT_EXT |
      VK_DEBUG_REPORT_WARNING_BIT_EXT |
      VK_DEBUG_REPORT_PERFORMANCE_WARNING_BIT_EXT |
      VK_DEBUG_REPORT_ERROR_BIT_EXT |
      VK_DEBUG_REPORT_DEBUG_BIT_EXT;
    DebugReportCallbackInfo.pfnCallback = [](
      VkDebugReportFlagsEXT Flags,
      VkDebugReportObjectTypeEXT ObjectType,
      UINT64 Object,
      UINT_PTR Location,
      INT32 MessageCode,
      const CHAR *LayerPrefix,
      const CHAR *Message,
      VOID *UserData) -> VkBool32
    {
      if ((Flags & VK_DEBUG_REPORT_DEBUG_BIT_EXT) != 0)
        return VK_FALSE;
      std::string Res = "DEBUG REPORT: (";
      std::cout << Res;

      if ((Flags & VK_DEBUG_REPORT_INFORMATION_BIT_EXT) != 0)
      {
        Res += "INFO", std::cout << "\033[44;37m" << "INFO" << "\033[0m";
        Res += ")";
        Res += std::string("{") + LayerPrefix + "} " + Message + "\n";
        OutputDebugString(Res.c_str());
        std::cout << "){" << "\033[34m" << LayerPrefix << "\033[0m" << "} " << "\033[34m" << Message << "\033[0m" << std::endl;
      }
      if ((Flags & VK_DEBUG_REPORT_WARNING_BIT_EXT) != 0)
      {
        Res += "WARNING", std::cout << "\033[43;37m" << "WARNING" << "\033[0m";
        Res += ")";
        Res += std::string("{") + LayerPrefix + "} " + Message + "\n";
        OutputDebugString(Res.c_str());
        std::cout << "){" << "\033[33m" << LayerPrefix << "\033[0m" << "} " << "\033[33m" << Message << "\033[0m" << std::endl;
      }
      if ((Flags & VK_DEBUG_REPORT_PERFORMANCE_WARNING_BIT_EXT) != 0)
      {
        Res += "PERFORMANCE", std::cout << "\033[45;37m" << "PERFORMANCE" << "\033[0m";
        Res += ")";
        Res += std::string("{") + LayerPrefix + "} " + Message + "\n";
        OutputDebugString(Res.c_str());
        std::cout << "){" << "\033[35m" << LayerPrefix << "\033[0m" << "} " << "\033[35m" << Message << "\033[0m" << std::endl;
      }
      if ((Flags & VK_DEBUG_REPORT_ERROR_BIT_EXT) != 0)
      {
        Res += "ERROR", std::cout << "\033[41;37m" << "ERROR" << "\033[0m";
        Res += ")";
        Res += std::string("{") + LayerPrefix + "} " + Message + "\n";
        OutputDebugString(Res.c_str());
        std::cout << "){" << "\033[31m" << LayerPrefix << "\033[0m" << "} " << "\033[31m" << Message << "\033[0m" << std::endl;
      }
      //Res += std::string("{") + LayerPrefix + "} " + Message + "\n";
      //OutputDebugString(Res.c_str());
      //std::cout << "){" << LayerPrefix << "} " << Message << std::endl;
      //std::cout << std::endl;
      return VK_FALSE;
    };
    DebugReportCallbackInfo.pUserData = nullptr;

    //ValidationFeatures.pNext = &DebugReportCallbackInfo;
  #endif

  //Create Instance;
  VK_CHECK(vkCreateInstance(&InstanceCreateInfo, nullptr, &Instance));
} /* End of 'CreateInstance' fucntion */

/* Destroy instance function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID arvk::VlkInstance::DestroyInstance( VOID )
{
  vkDestroyInstance(Instance, nullptr);
} /* End of 'DestroyInstance' fucntion */

/* END OF 'vlk_instance.cpp' FILE */
