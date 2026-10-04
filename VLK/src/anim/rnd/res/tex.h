/*************************************************************
 * Copyright (C) 2025
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : tex.h
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

#ifndef __tex_h_
#define __tex_h_

#include "resources.h"
#include "utils/images/image.h"

/* Animation namespace*/
namespace arvk
{
  /* texture class */
  class texture : public resource
  {
  public:
    std::string Name; // Texture name
    INT W = 0, H = 0; // Image size
    UINT TexNo = 0;   // OpenGL texture Id

    VkImage Image = VK_NULL_HANDLE;
    VkImageView ImageView = VK_NULL_HANDLE;
    VmaAllocation Allocation = VK_NULL_HANDLE;
    VkSampler Sampler = VK_NULL_HANDLE;
    VkFormat Format = VK_FORMAT_R8G8B8A8_SRGB;

    /* Class cinstructor.
     * ARGUMENTS: None.
     */
    texture( render &rnd )
    {
      Rnd = &rnd;
    } /* End of 'texture' function */

    texture( VOID ) 
    {
    } /* End of 'buffer' function */


    /* Class cinstructor.
     * ARGUMENTS:
     *   - texture name:
     *      const std::string &FileName;
     */
    texture( const std::string &FileName, render &rnd ) : Name(FileName)
    {
      Rnd = &rnd;
    } /* End of 'texture' function */

    /* Class destructor */
    ~texture( VOID )
    {
    } /* End of '~texture' function */

    texture & CreateFromMemory( const std::string &NewName, const std::vector<BYTE> &ImageData );

    /* Create texture function.
     * ARGUMENTS:
     *   - texture name:
     *      const std::string &NewName;
     *   - texture size:
     *      INT NewW, INT NewH;
     *   - pixels:
     *      INT BytesPerPixel, BYTE *Pixels, BOOL IsMips;
     * RETURNS:
     *   (texture &) texture.
     */
    texture & Create( const std::string &NewName, INT NewW, INT NewH, INT BytesPerPixel, BYTE *Pixels, BOOL IsMips = TRUE );
    /* Create texture function.
     * ARGUMENTS:
     *   - texture name:
     *      const std::string &FileName;
     * RETURNS:
     *   (texture &) texture.
     */
    texture & Create( const std::string &FileName );
    /* Load texture function.
     * ARGUMENTS:
     * RETURNS: None.
     *   (texture &) texture.
     */
    texture & Load( VOID );
    /* Create texture format function.
     * ARGUMENTS:
     *   - texture name:
     *      const std::string &NewName;
     *   - texture size:
     *      INT NewW, INT NewH;
     *   - texture format:
     *      INT Format;
     * RETURNS:
     *   (texture &) texture.
     */
    texture & CreateFmt( const std::string &NewName, INT NewW, INT NewH, INT Format );
    /* Create cubemap texture function.
     * ARGUMENTS:
     *   - texture name:
     *      const std::string &TextureName;
     * RETURNS:
     *   (texture &) cubemap texture.
     */
    texture & CreateCubeMap( const std::string &TextureName );
    texture & CreateWithFileCache(const std::string &NewName, const std::vector<BYTE> &ImageData);

    /* Free texture function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Free( VOID );

    /* Apply texture function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Apply( VOID )
    {
      //glBindTexture(GL_TEXTURE_2D, TexNo);
    } /* End of 'Apply' function */
  }; /* End of 'texture' class */
 
  class texture_manager : public resource_manager<texture, std::string>
  {
  public:
    /* Create texture function.
     * ARGUMENTS:
     *   - texture name:
     *      const std::string &NewName;
     * RETURNS:
     *   (texture *) pointer to texture.
     */
    texture * TexCreate( const std::string &FileName );
    /* Create texture cubemap function.
     * ARGUMENTS:
     *   - texture name:
     *      const std::string &NewName;
     * RETURNS:
     *   (texture *) pointer to texture.
     */
    texture * TexCreateCubeMap( const std::string &FileName );
    /* Create texture function.
     * ARGUMENTS:
     *   - texture name:
     *      const std::string &NewName;
     *   - texture size:
     *      INT NewW, INT NewH;
     *   - pixels:
     *      INT BytesPerPixel, BYTE *Pixels, BOOL IsMips;
     * RETURNS:
     *   (texture *) pointer to texture.
     */
    texture * TexCreate( const std::string &NewName, INT NewW, INT NewH, INT BytesPerPixel, BYTE *Pixels, BOOL IsMips = TRUE );
    /* Create texture format function.
     * ARGUMENTS:
     *   - texture name:
     *      const std::string &NewName;
     *   - texture size:
     *      INT NewW, INT NewH;
     *   - texture format:
     *      INT Format;
     * RETURNS:
     *   (texture *) pointer to texture.
     */
    texture * TexCreateFmt( const std::string &NewName, INT NewW, INT NewH, INT Format );
    texture* TexCreateWithFileCache(const std::string &NewName, const std::vector<BYTE> &ImageData);

    texture * TexCreateFromMemory( const std::string &NewName, const std::vector<BYTE> &ImageData );
    /* Class constructor
     * ARGUMENTS:
     *   - render reference:
     *      render &Rnd;
     */
    texture_manager( render &Rnd ) : resource_manager(Rnd)
    {
    } /* End of 'texture_manager' function */

    /* Class destructor */
    ~texture_manager( VOID )
    {
    } /* End of '~texture_manager' function */
  }; /* End of 'texture_manager' class */
} /* End of 'arg;' namespace */
#endif /* __tex_h_ */

/* END OF 'tex.h' FILE */
