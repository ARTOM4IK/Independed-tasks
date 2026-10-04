/*************************************************************
 * Copyright (C) 2025
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : tex.cpp
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
 
arvk::texture & arvk::texture::Create( const std::string &NewName, INT NewW, INT NewH, INT BytesPerPixel, BYTE *Pixels, BOOL IsMips )
{
  W = NewW;
  H = NewH;
  Name = NewName;
    
  if (Rnd != nullptr)
  {
    if (BytesPerPixel == 4)
      Format = VK_FORMAT_B8G8R8A8_SRGB;
    else if (BytesPerPixel == 3)
      Format = VK_FORMAT_R8G8B8_SRGB;
    else if (BytesPerPixel == 1)
      Format = VK_FORMAT_R8_SRGB;
        
    Rnd->ImageCreate(Image, ImageView, Allocation, W, H, TRUE, FALSE, Format, VK_IMAGE_USAGE_SAMPLED_BIT | VK_IMAGE_USAGE_TRANSFER_DST_BIT, VK_IMAGE_LAYOUT_UNDEFINED, Pixels, W * H * BytesPerPixel, IsMips ? 0 : 1);
        
    VkSamplerCreateInfo samplerInfo = 
    {
        .sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO,
        .magFilter = VK_FILTER_LINEAR,
        .minFilter = VK_FILTER_LINEAR,
        .mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR,
        .addressModeU = VK_SAMPLER_ADDRESS_MODE_REPEAT,
        .addressModeV = VK_SAMPLER_ADDRESS_MODE_REPEAT,
        .addressModeW = VK_SAMPLER_ADDRESS_MODE_REPEAT,
        .mipLodBias = 0.0f,
        .anisotropyEnable = VK_TRUE,
        .maxAnisotropy = 16.0f,
        .compareEnable = VK_FALSE,
        .compareOp = VK_COMPARE_OP_ALWAYS,
        .minLod = 0.0f,
        .maxLod = static_cast<float>(IsMips ? 0 : 1),
        .borderColor = VK_BORDER_COLOR_INT_OPAQUE_BLACK,
        .unnormalizedCoordinates = VK_FALSE,
    };
        
    vkCreateSampler(Rnd->Device, &samplerInfo, nullptr, &Sampler);
  }
  return *this;
} /* End of 'Create' function */

arvk::texture & arvk::texture::CreateFromMemory( const std::string &NewName, const std::vector<BYTE> &ImageData )
{
  //try
  //{
  //  // Сохраняем данные во временный файл
  //  std::string tempFile = std::filesystem::temp_directory_path().string() + 
  //                        "\\temp_texture_" + std::to_string(GetTickCount()) + ".png";
  //  
  //  std::ofstream out(tempFile, std::ios::binary);
  //  out.write(reinterpret_cast<const char*>(ImageData.data()), ImageData.size());
  //  out.close();
  //  
  //  // Загружаем через существующий конструктор image
  //  image img(tempFile);
  //  
  //  // Удаляем временный файл
  //  std::filesystem::remove(tempFile);
  //  
  //  if (img.W == 0 || img.H == 0 || img.RowsB.empty())
  //  {
  //    std::cerr << "Failed to load image from memory: " << NewName << std::endl;
  //    return *this;
  //  }
  //  
  //  // Используем существующую функцию Create
  //  return Create(NewName, img.W, img.H, 4, img.RowsB[0][0], TRUE);
  //}
  //catch (const std::exception &e)
  //{
  //  std::cerr << "Error creating texture from memory: " << e.what() << std::endl;
  //  return *this;
  //}
  if (ImageData.empty())
  {
    std::cerr << "Empty image data for texture: " << NewName << std::endl;
    return *this;
  }
  
  // Создаем image и загружаем прямо из памяти
  image img;
  
  if (!img.LoadFromMemory(ImageData))
  {
    std::cerr << "Failed to load image from memory: " << NewName << std::endl;
    return *this;
  }
  
  if (img.W == 0 || img.H == 0 || img.RowsB.empty() || img.RowsB[0] == nullptr)
  {
    std::cerr << "Invalid image data for texture: " << NewName << std::endl;
    return *this;
  }
  
  //std::cout << "Creating texture from memory: " << NewName 
  //          << " (" << img.W << "x" << img.H << ")\n";
  //
  std::vector<BYTE> rgbaData(img.W * img.H * 4);
  BYTE* src = img.RowsB[0][0];
  BYTE* dst = rgbaData.data();
    
  for (INT i = 0; i < img.W * img.H * 4; i += 4)
  {
      dst[i + 0] = src[i + 2];
      dst[i + 1] = src[i + 1]; 
      dst[i + 2] = src[i + 0];
      dst[i + 3] = src[i + 3];
  }
    
  return Create(NewName, img.W, img.H, 4, rgbaData.data(), TRUE);
}

/* Free texture function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID arvk::texture::Free( VOID )
{
  if (Rnd != nullptr)
  {
    if (Sampler != VK_NULL_HANDLE)
    {
      vkDestroySampler(Rnd->Device, Sampler, nullptr);
      Sampler = VK_NULL_HANDLE;
    }
        
    if (ImageView != VK_NULL_HANDLE)
    {
      vkDestroyImageView(Rnd->Device, ImageView, nullptr);
      ImageView = VK_NULL_HANDLE;
    }
        
    if (Image != VK_NULL_HANDLE && Allocation != VK_NULL_HANDLE)
    {
      vmaDestroyImage(Rnd->Allocator, Image, Allocation);
      Image = VK_NULL_HANDLE;
      Allocation = VK_NULL_HANDLE;
    }
  }
} /* End of 'Free' fucntion */

/* Texture create function.
  * ARGUMENTS:
  *   - texture file name:
  *       const std::string &FileName;
  * RETURNS:
  *   (texture &) self reference.
  */
arvk::texture & arvk::texture::Create( const std::string &FileName )
{
  image img(FileName);
 
  return Create(FileName, img.W, img.H, 4, img.RowsB[0][0], TRUE);
} /* End of 'Create' function */

arvk::texture & arvk::texture::Load( VOID )
{
  return *this;
} /* End of 'Load' function */

arvk::texture* arvk::texture_manager::TexCreate(const std::string& FileName)
{
  arvk::image img(FileName);
    
  if (img.W != 0 && img.H != 0 && !img.RowsB.empty() && img.RowsB[0] != nullptr)
      return TexCreate(FileName, img.W, img.H, 4, reinterpret_cast<BYTE*>(img.RowsB[0]), TRUE);    
  return nullptr;
} /* End of 'TexCreate' function */

arvk::texture * arvk::texture_manager::TexCreate( const std::string &NewName, INT NewW, INT NewH, INT BytesPerPixel, BYTE *Pixels, BOOL IsMips )
{
  return resource_manager::Add(texture(RndRef).Create(NewName, NewW, NewH, BytesPerPixel, Pixels, IsMips));
} /* End of 'TexCreate' function */

arvk::texture * arvk::texture_manager::TexCreateFmt( const std::string &NewName, INT NewW, INT NewH, INT Format )
{
  return resource_manager::Add(texture(RndRef).CreateFmt(NewName, NewW, NewH, Format));
} /* End of 'TexCreate' function */

arvk::texture & arvk::texture::CreateFmt( const std::string &NewName, INT NewW, INT NewH, INT Format )
{
  //glGenTextures(1, &TexNo);
  //glBindTexture(GL_TEXTURE_2D, TexNo);
  //glTexStorage2D(GL_TEXTURE_2D, 1, Format, NewW, NewH);
  //  
  //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  //glBindTexture(GL_TEXTURE_2D, 0);
  //  
  W = NewW;
  H = NewH;
  Name = NewName;

  return *this;
}

/* Create 3D Cube map texture function.
 * ARGUMENTS:
 *   - texture name:
 *       CHAR *TextureName;
 * RETURNS:
 *    twrTEXTURE *Tex.
 */
arvk::texture & arvk::texture::CreateCubeMap( const std::string &TextureName )
{
  const std::vector<std::string> Names = 
  {
      "PosX", "NegX", "PosY", "NegY", "PosZ", "NegZ"
  };
    
  const std::vector<std::string> TypeImg = 
  {
      "bmp", "png", "g24", "g32", "tga", "dds", "jpg"
  };
    
  std::string currentType;
  INT mips = 1, W = 1;
    
  // Find supported image type
  for (const auto &type : TypeImg)
  {
      std::string path = "bin/textures/SkyBoxes/" + TextureName + "/" + Names[0] + "." + type;
      image img(path);
      if (!(img.W == 0 || img.H == 0 || img.RowsB.empty() || img.RowsB[0] == nullptr))
      {
          currentType = type;
          break;
      }
  }
    
  if (currentType.empty())
  {
      // Handle error - no supported image format found
      return *this;
  }
    
  //// Create OpenGL cube map texture
  //glGenTextures(1, &TexNo);
  //glBindTexture(GL_TEXTURE_CUBE_MAP, TexNo);
  //  
  //// Set texture parameters
  //glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  //glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  //glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  //glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  //glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    
  // Load each face of the cube map
  for (INT i = 0; i < 6; i++)
  {
      std::string path = "bin/textures/SkyBoxes/" + TextureName + "/" + Names[i] + "." + currentType;
        
      image img(path);
      if (img.W == 0 || img.H == 0 || img.RowsB.empty() || img.RowsB[0] == nullptr)
      {
          //glDeleteTextures(1, &TexNo);
          TexNo = 0;
          return *this;
      }
      
      if (i == 0)
      {
          W = img.W;
          mips = log(W) / log(2);
          mips = mips < 1 ? 1 : mips;
          //glTexStorage2D(GL_TEXTURE_CUBE_MAP, mips, GL_RGBA8, W, W);
      }
        
      //glTexSubImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, 0, 0, 
      //                img.W, img.W, GL_BGRA, GL_UNSIGNED_BYTE, img.RowsB[0][0]);
  }
    
  //glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
  //glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
    
  // Set texture properties
  W = W;
  H = W;
  Name = TextureName;
    
  return *this;
}

arvk::texture * arvk::texture_manager::TexCreateFromMemory( const std::string &NewName, const std::vector<BYTE> &ImageData )
{
  texture tex(RndRef);
  tex.CreateFromMemory(NewName, ImageData);
  return resource_manager::Add(std::move(tex));
}

arvk::texture * arvk::texture_manager::TexCreateCubeMap( const std::string &FileName )
{
  return resource_manager::Add(texture(RndRef).CreateCubeMap(FileName));
}

arvk::texture & arvk::texture::CreateWithFileCache(const std::string &NewName, const std::vector<BYTE> &ImageData)
{
    if (!std::filesystem::exists(NewName))
    {
        std::cout << "File " << NewName << " does not exist, creating..." << std::endl;
        
        //std::filesystem::path filePath(NewName);
        //if (filePath.has_parent_path())
        //{
        //    std::filesystem::create_directories(filePath.parent_path());
        //}
        
        std::ofstream outFile(NewName, std::ios::binary);
        if (!outFile.is_open())
        {
            std::cerr << "Failed to create file: " << NewName << std::endl;
            return *this;
        }
        
        outFile.write(reinterpret_cast<const char*>(ImageData.data()), ImageData.size());
        outFile.close();
        
        std::cout << "File created: " << NewName << " (" << ImageData.size() << " bytes)" << std::endl;
    }
    else
    {
        std::cout << "File " << NewName << " already exists, loading from disk..." << std::endl;
    }
    
    try
    {
        arvk::image img(NewName);
        
        if (img.W == 0 || img.H == 0 || img.RowsB.empty() || img.RowsB[0] == nullptr)
        {
            std::cerr << "Failed to load image from file: " << NewName << std::endl;
            return *this;
        }
        
        std::cout << "Image loaded from file: " << img.W << "x" << img.H << std::endl;
        
        if (img.W > 0 && img.H > 0)
        {
            BYTE* firstPixel = img.RowsB[0][0];
            std::cout << "First pixel (BGRA): " 
                      << (int)firstPixel[0] << ", "
                      << (int)firstPixel[1] << ", "
                      << (int)firstPixel[2] << ", "
                      << (int)firstPixel[3] << std::endl;
        }
        
        return Create(NewName, img.W, img.H, 4, img.RowsB[0][0], TRUE);
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error loading image from file " << NewName << ": " << e.what() << std::endl;
        return *this;
    }
}

arvk::texture* arvk::texture_manager::TexCreateWithFileCache(const std::string &NewName, const std::vector<BYTE> &ImageData)
{
    texture tex(RndRef);
    tex.CreateWithFileCache(NewName, ImageData);
    return resource_manager::Add(std::move(tex));
}

 /* END OF 'tex.cpp' FILE */
