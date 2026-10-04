/*************************************************************
 * Copyright (C) 2025
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : vlk_device.cpp
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

/* Create logical device and choose physical device function.
 *  ARGUMENTS:
 *   - Instance:
 *      VkInstance &Instance;
 * RETURNS: None.
 */
VOID arvk::VlkDevice::CreateDevice( VkInstance &Instance )
{
 // Get number of physical devices.
  std::vector<VkPhysicalDevice> PhysDevices;
  UINT32 PhysicalDeviceCount = 0;
  if (vkEnumeratePhysicalDevices(Instance, &PhysicalDeviceCount, nullptr) != VK_SUCCESS)
    throw std::runtime_error("Error finding physical devices");

  // Get physical system devices.
  PhysDevices.resize(PhysicalDeviceCount);
  if (vkEnumeratePhysicalDevices(Instance, &PhysicalDeviceCount, PhysDevices.data()) != VK_SUCCESS)
    throw std::runtime_error("Error get physical system devices");

  // Choose physical device for requirments.
  for (VkPhysicalDevice &Device : PhysDevices)
  {
    VkPhysicalDeviceProperties DeviceProperties;                
    vkGetPhysicalDeviceProperties(Device, &DeviceProperties);                                                                   

    VkPhysicalDeviceFeatures DeviceFeatures;                    // Addiditional abilities
    vkGetPhysicalDeviceFeatures(Device, &DeviceFeatures);       
                                                                
    vkGetPhysicalDeviceQueueFamilyProperties(Device, &QueueFamilyCount, nullptr);                                                                                                                                                                       
    
    QueueFamilies.resize(QueueFamilyCount);        
    vkGetPhysicalDeviceQueueFamilyProperties(Device, &QueueFamilyCount, QueueFamilies.data());
    
    if (DeviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU && DeviceFeatures.geometryShader)
      PhysDevice = Device, std::cout << DeviceProperties.deviceName << std::endl; 
  }

  if (PhysDevice == VK_NULL_HANDLE)
    throw std::runtime_error("Physical device is null");

  /* Check extentions */
  vkEnumerateDeviceExtensionProperties(PhysDevice, nullptr, &ExtensionCount, nullptr);
  AvailableExtensions.resize(ExtensionCount);
  vkEnumerateDeviceExtensionProperties(PhysDevice, nullptr, &ExtensionCount, AvailableExtensions.data());
  
  BOOL HasSwapchain = FALSE;
  for (VkExtensionProperties &Extention : AvailableExtensions)
  {
    if (std::string(Extention.extensionName) == "VK_KHR_swapchain")
    {
      HasSwapchain = TRUE;
      break;
    }
  }

  //Queue Priorities
  const std::vector<float>QueuePriorities(QueueFamilyCount, 1.0);
  
  VkDeviceQueueCreateInfo QueueInfo
  {
    .sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
    .pNext = nullptr,
    .flags = 0,
    .queueFamilyIndex = 0,
    .queueCount = QueueFamilyCount,
    .pQueuePriorities = QueuePriorities.data()
  };        

  // Extensions for logical device.
  std::vector<const CHAR *> ExtensionNames
  {
    HasSwapchain ? VK_KHR_SWAPCHAIN_EXTENSION_NAME : "", 
    "VK_KHR_pipeline_library",
    "VK_EXT_graphics_pipeline_library",
  };

  vkGetPhysicalDeviceFeatures(PhysDevice, &DeviceFeatures);
    
  VkDeviceCreateInfo DeviceInfo
  {
    .sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
    .pNext = nullptr,
    .flags = 0,
    .queueCreateInfoCount = 1,
    .pQueueCreateInfos = &QueueInfo,
    .enabledLayerCount = 0,
    .ppEnabledLayerNames = nullptr,
    .enabledExtensionCount = UINT32(ExtensionNames.size()),
    .ppEnabledExtensionNames = ExtensionNames.data(),
    .pEnabledFeatures = &DeviceFeatures
  };

  VK_CHECK(vkCreateDevice(PhysDevice, &DeviceInfo, nullptr, &Device));

  VkPhysicalDeviceProperties PhysicalDeviceProperties;                
  vkGetPhysicalDeviceProperties(PhysDevice, &PhysicalDeviceProperties);

  // Create VMA allocator
  AllocatorCreateInfo = VmaAllocatorCreateInfo{};
  AllocatorCreateInfo.vulkanApiVersion = PhysicalDeviceProperties.apiVersion;
  AllocatorCreateInfo.physicalDevice = PhysDevice;
  AllocatorCreateInfo.device = Device;
  AllocatorCreateInfo.instance = Instance;
  vmaCreateAllocator(&AllocatorCreateInfo, &Allocator);
} /* End of 'CreateDevice' fucntion */

/* Destroy logical and physical device function.
 *  ARGUMENTS:
 *   - Instance:
 *      VkInstance &Instance;
 * RETURNS: None.
 */
VOID arvk::VlkDevice::DestroyDevice( VkInstance &Instance )
{
  vmaDestroyAllocator(Allocator);
  vkDestroyDevice(Device, nullptr);
} /* End of 'DestroyDevice' fucntion */

/* END OF 'vlk_device.cpp' FILE */
