/*************************************************************
 * Copyright (C) 2025
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : gltf.h
 * PURPOSE     : Vulkan project.
 *               Precompiled header definition module.
 * PROGRAMMER  : AA4
 *               Artmey V. Arsentev.
 * LAST UPDATE : 25.12.2025.
 * NOTE        : Module namespace 'arvk'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __gltf_h_
#define __gltf_h_

#include "resources.h"

namespace arvk
{
  class json;

  using json_array = std::vector<json>;
  using json_object = std::map<std::string, json>;

  /* JSON class */
  class json : public std::variant<std::nullptr_t, BOOL, INT, DBL, std::string, json_array, json_object>
  {
    using variant::variant;

  public:
    /* Check json array function.
     * ARGUMENTS: None.
     * RETURNS:
     *   (BOOL) result value.
     */
    BOOL IsArray( VOID ) const
    {
      return std::holds_alternative<json_array>(*this);
    } /* End of 'IsArray' fucnction */

    /* Check json object function.
     * ARGUMENTS: None.
     * RETURNS:
     *   (BOOL) result value.
     */
    BOOL IsObject( VOID ) const
    {
      return std::holds_alternative<json_object>(*this);
    } /* End of 'IsObject' fucnction */

    /* Check json int function.
     * ARGUMENTS: None.
     * RETURNS:
     *   (BOOL) result value.
     */
    BOOL IsInt( VOID ) const
    {
      return std::holds_alternative<INT>(*this);
    } /* End of 'IsInt' fucnction */

    /* Check json double function.
     * ARGUMENTS: None.
     * RETURNS:
     *   (BOOL) result value.
     */
    BOOL IsDouble( VOID ) const
    {
      return std::holds_alternative<DBL>(*this);
    } /* End of 'IsDouble' fucnction */

    /* Check json string function.
     * ARGUMENTS: None.
     * RETURNS:
     *   (BOOL) result value.
     */
    BOOL IsString( VOID ) const
    {
      return std::holds_alternative<std::string>(*this);
    } /* End of 'IsString' fucnction */

    /* Check json array function.
     * ARGUMENTS: None.
     * RETURNS:
     *   (BOOL) result value.
     */
    BOOL IsBool( VOID ) const
    {
      return std::holds_alternative<BOOL>(*this);
    } /* End of 'IsBool' fucnction */

    /* Check json array function.
     * ARGUMENTS: None.
     * RETURNS:
     *   (BOOL) result value.
     */
    BOOL IsNull( VOID ) const
    {
      return std::holds_alternative<std::nullptr_t>(*this);
    } /* End of 'IsNull' fucnction */

    /* Get json bool function.
     * ARGUMENTS: None.
     * RETURNS:
     *   (INT) result value.
     */
    BOOL GetBool( BOOL ElseValue ) const
    {
      if (IsBool())
        return std::get<BOOL>(*this);
      else
        return ElseValue;
    } /* End of 'GetBool' function */

    /* Get json int function.
     * ARGUMENTS: None.
     * RETURNS:
     *   (INT) result value.
     */
    INT GetInt( INT ElseValue = 0 ) const
    {
      if (IsInt())
        return std::get<INT>(*this);
      else
        return ElseValue;
    } /* End of 'GetInt' function */

    /* Get json double function.
     * ARGUMENTS: None.
     * RETURNS:
     *   (DBL) result value.
     */
    DBL GetDouble( DBL ElseValue = 0 ) const
    {
      if (IsDouble())
        return std::get<DBL>(*this);
      else
        return ElseValue;
    } /* End of 'GetDouble' function */

    /* Get json string function.
     * ARGUMENTS: None.
     * RETURNS:
     *   (std::string) result value.
     */
    std::string GetString( std::string ElseValue = "" ) const
    {
      if (IsString())
        return std::get<std::string>(*this);
      else
        return ElseValue;
    } /* End of 'GetString' function */

    /* Get json array function.
     * ARGUMENTS: None.
     * RETURNS:
     *   (json_array) result value.
     */
    json_array GetArray( VOID ) const
    {
      if (IsArray())
        return std::get<json_array>(*this);
      else
        return (json_array{});
    } /* End of 'GetArray' function */

    /* Get json object function.
     * ARGUMENTS: None.
     * RETURNS:
     *   (json_object) result value.
     */
    json_object GetObj( VOID ) const
    {
      if (IsObject())
        return std::get<json_object>(*this);
      else
        return (json_object{});
    } /* End of 'GetObj' function */

    /* Get element from json array function.
     * ARGUMENTS:
     *   - Array index:
     *       size_t index;
     * RETURNS:
     *   (json&) Adress to json.
     */
    const json& operator[]( size_t index ) const 
    {
      if (!IsArray())
        throw std::runtime_error("Trying to get element from non a array");
      auto &arr = std::get<json_array>(*this);
      if (index < 0 || index >= arr.size())
        throw std::runtime_error("Index is out of range");
      return arr[index];
    } /* End of 'operator[]' function */

    /* Get element from json array function.
     * ARGUMENTS:
     *   - Array index:
     *       size_t index;
     * RETURNS:
     *   (json&) Adress to json.
     */
    json& operator[]( size_t index )
    {
      if (!IsArray())
        throw std::runtime_error("Trying to get element from non a array");
      auto &arr = std::get<json_array>(*this);
      if (index < 0 || index >= arr.size())
        throw std::runtime_error("Index is out of range");
      return arr[index];
    } /* End of 'operator[]' function */

    /* Get element from json object function.
     * ARGUMENTS:
     *   - Object element name:
     *       std::string Name;
     * RETURNS:
     *   (json&) Adress to json.
     */
    json& operator[]( std::string Name )
    {
      if (!IsObject())
        throw std::runtime_error("Trying to get element from non a object");
      auto &obj = std::get<json_object>(*this);
      return obj[Name];
    } /* End of 'operator[]' function */
  }; /* End of 'json' class */

  /* JSON visitior to read json loader */
  struct json_visitor
  {
    /* Output json nullptr function.
     * ARGUMENTS:
     *   - nullptr value:
     *       std::nullptr_t;
     * RETURNS: None.
     */
    VOID operator()( std::nullptr_t ) const
    {
      std::cout << "null\n";
    } /* End of 'operator()' function */

    /* Output json nullptr function.
     * ARGUMENTS:
     *   - nullptr value:
     *       std::nullptr_t;
     * RETURNS: None.
     */
    VOID operator()( BOOL F ) const
    {
      std::cout << "bool:\n" << F;
    } /* End of 'operator()' function */

    /* Output json int function.
     * ARGUMENTS:
     *   - int value:
     *       INT X;
     * RETURNS: None.
     */
    VOID operator()( INT X ) const
    {
      std::cout << "int:\n" << X;
    } /* End of 'operator()' function */

    /* Output json double function.
     * ARGUMENTS:
     *   - double value:
     *       DBL X;
     * RETURNS: None.
     */
    VOID operator()( DBL X ) const
    {
      std::cout << "double:\n" << X;
    } /* End of 'operator()' function */

    /* Output json string function.
     * ARGUMENTS:
     *   - string value:
     *       std::string S;
     * RETURNS: None.
     */
    VOID operator()( std::string S ) const
    {
      std::cout << "string:\n" << S;
    } /* End of 'operator()' function */

    /* Output json array function.
     * ARGUMENTS:
     *   - json array value:
     *       json_array A;
     * RETURNS: None.
     */
    VOID operator()( json_array A ) const
    {
      std::cout << "array:[\n";
      for (auto &val : A )
      {
        std::visit(json_visitor{}, val);
        std::cout << ", \n";
      }
      std::cout << "]\n";
    } /* End of 'operator()' function */

    /* Output json object function.
     * ARGUMENTS:
     *   - json object value:
     *       json_object Obj;
     * RETURNS: None.
     */
    VOID operator()( json_object Obj ) const
    {
      std::cout << "object{\n";
      for (auto &[key, val] : Obj )
      {
        std::cout << "\"" << key << "\": ";
        std::visit(json_visitor{}, val);
        std::cout << ", \n";
      }
      std::cout << "}";
    } /* End of 'operator()' function */
  }; /* End of 'json_visitor' strcutre */

  /* Wide character to ANSI string converter.
   * ARGUMENTS:
   *   - source string:
   *       const std::wstring &Str;
   *   - result code page (CP_ACP, CP_UTF8):
   *       UINT CodePage;
   * RETURNS:
   *   (std::string) result wide string.
   */
  inline std::string WStringToString( const std::wstring &WStr, UINT CodePage = CP_ACP )
  {
    if (WStr.empty())
      return "";
    
    INT BufferSize = WideCharToMultiByte(CodePage, 0, WStr.c_str(), -1, nullptr, 0, nullptr, nullptr);
    if (BufferSize == 0)
      return "";
    
    std::string Str(BufferSize - 1, '\0');
    WideCharToMultiByte(CodePage, 0, WStr.c_str(), -1, &Str[0], BufferSize, nullptr, nullptr);
    
    return Str;
  } /* End of 'WStringToString' function */

  /* Buffer representation type */
  struct data_buffer
  {
    std::vector<BYTE> Data; // Buffer data
  }; /* End of 'buffer' structure */
 
  /* Buffer view representation type */
  struct buffer_view
  {
    INT Buffer;        // Buffer number at buffers array
    SIZE_T Offset;     // Offset in buffer in bytes
    SIZE_T Length;     // Length of data in bytes
    INT Stride;        // Stride between stored data or 0  for comact packing
  }; /* End of 'buffer_view' structure */
 
  /* Component types */
  enum class component_type
  {
    // Type of components: BYTE, WORD, DWORD, FLT, etc.
    eI8 = 0x1400, eU8 = 0x1401, eI16 = 0x1402, eU16 = 0x1403, eI32 = 0x1404, eU32 = 0x1405, eF32 = 0x1406,
  }; /* End of 'component_type' enumeration */
 
  /* Accessor types */
  enum class accessor_type
  {
    // Type of accessors: "SCALAR", "VEC2", "VEC3", "VEC4", "MAT4", etc.
    eSCALAR, eVEC2, eVEC3, eVEC4, eMAT2, eMAT3, eMAT4,
  }; /* End of 'accessor_type' enumeration */
 
  /* Draw mode types */
  enum class draw_mode_type
  {
    // Type of primitive topology: point, triangle, etc.
    ePOINTS = 0, eLINES = 1, eLINE_LOOP = 2, eLINE_STRIP = 3, eTRIANGLES = 4,
    eTRIANGLE_STRIP = 5, eTRIANGLE_FAN = 6,
  }; /* End of 'accessor_type' enumeration */
 
  /* Sampler filter types */
  enum class sampler_filter_type
  {
    // Type of filters: "NEAREST", "LINEAR", etc.
    eNEAREST = 0x2600, eLINEAR = 0x2601, eNEAREST_MIPMAP_NEAREST = 0x2700,
    eLINEAR_MIPMAP_NEAREST = 0x2701, eNEAREST_MIPMAP_LINEAR = 0x2702,
    eLINEAR_MIPMAP_LINEAR = 0x2703
  }; /* End of 'sampler_filter_type' enumeration */
 
  /* Sampler addressing types */
  enum class sampler_address_type
  {
    // Type of addressing: "REPEAT", "CLAMP", etc.
    eCLAMP = 0x2900, eREPEAT = 0x2901, eCLAMP_TO_EDGE = 0x812F
  }; /* End of 'sampler_address_type' enumeration */

  template<size_t N>
  struct byte_array
  {
      BYTE data[N];
    
      BYTE& operator[](size_t i) 
      { 
        return data[i];
      } /* End of 'BYTE& operator[]' function */

      const BYTE& operator[](size_t i) const 
      { 
        return data[i]; 
      } /* End of 'const BYTE& operator[]' function */
    
      operator BYTE*( VOID ) 
      { 
        return data; 
      } /* End of 'operator BYTE*' function */

      operator const BYTE*( VOID ) const 
      {
        return data; 
      } /* End of 'operator const BYTE*' function */
  }; /* End of 'byte_array' structure */

  using byte8 = byte_array<8>;   // Для vec2 (2 * 4 байта)
  using byte12 = byte_array<12>; // Для vec3 (3 * 4 байта)  
  using byte16 = byte_array<16>; // Для vec4 (4 * 4 байта)
  using byte32 = byte_array<32>; // Для mat4 (16 * 2 байта для UINT16)

  /* Accessor representation type */
  struct accessor
  {
    INT BufferView;               // Buffer view index
    SIZE_T ByteOffset;            // Offset from buffer view offset
    component_type ComponentType; // Stored component type
    accessor_type Type;           // Accessor type
    SIZE_T Count;                 // Data unit count
    BOOL IsNormalized;            // Normalized flag
  }; /* End of 'accessor' structure */ 

  /* Primitive representation type */
  struct primitive
  {
    INT PositionAccessor;   // Position accessor number or -1 if abcent
    INT NormalAccessor;     // Normal accessor number or -1 if abcent
    INT TexCoord0Accessor;  // Texture coordinates set 0 accessor number or -1 if abcent
    INT TexCoord1Accessor;  // Texture coordinates set 1 accessor number or -1 if abcent
    INT Color0Accessor;     // Color accessor number or -1 if abcent
    INT Joints0Accessor;    // Joint bone accessor
    INT Weights0Accessor;   // Weight accessor
    INT IndexAccessor;      // Index buffer accessor number or -1 if abcent
    INT MaterialNo;         // Material number
    draw_mode_type Mode;    // OpenGL primitive mode: 4 - GL_TRIANGLES etc.
  }; /* End of 'primitive' structure */
 
  /* Mesh representation type */
  struct mesh
  {
    std::string Name;             // Mesh name
    std::vector<primitive> Prims; // Mesh primitives
  }; /* End of 'mesh' structure */

  /* Scene representation type */
  struct scena
  {
    std::string Name;           // Scene name
    std::vector<INT> RootNodes; // Root nodes index
  }; /* End of 'scene' structure */
 
  /* Scene node representation type */
  struct node
  {
    std::string Name;          // Node name
    INT Mesh = -1;             // Mesh index
    std::vector<INT> Subnodes; // Subnode array
    INT Skin;

    // Transformation
    BOOL IsMatrixUse = FALSE;  // Common matrix usage flag
    dmatr Matrix = dmatr::Identity();  // Common transformation matrix
 
    dvec3 Translation = dvec3(0);           // Translation vector
    dvec4 Rotation = dvec4(0, 0, 0, 1);     // Rotation quaternion
    dvec3 Scale = dvec3(1);                 // Scale vector (sx, sy, sz)
    dmatr WorldMatrix = dmatr::Identity();  // World matrix (transformation from root)
  }; /* End of 'node' structure */
 
  /* Image representation type */
  struct imaga
  {
    std::string Name;            // Imaga name
    std::vector<BYTE> ImageData; // Imaga data bytes
  }; /* End of 'imaga' structure */
 
  /* Sampler representation type */
  struct sampler
  {
    sampler_filter_type MagFilter, MinFilter; // Magnify and minimize filters
    /* Sampler filter types */
    sampler_address_type AddressS, AddressT; // Sampler addressing types (by S and T)
  }; /* End of 'sampler' structure */
 
  /* Texture representation type */
  struct textura
  {
    std::string Name;  // Texture name
    INT ImageNo;       // Image number
    INT SamplerNo;     // Sampler number
  }; /* End of 'texture' structure */

  struct material_gltf
  {
    std::string Name;          // Material name
  
    // PBR metallic-roughness parameters
    vec4 BaseColorFactor = vec4(1, 1, 1, 1);  // RGBA
    INT BaseColorTexture = -1;                // Base color texture index
    FLT MetallicFactor = 1.0f;
    FLT RoughnessFactor = 1.0f;
    INT MetallicRoughnessTexture = -1;        // Metallic-roughness texture index
  
    // Other parameters
    vec3 SpecularFactor = vec3(0);
    FLT GlossinesFactor = 0;
    vec3 EmissiveFactor = vec3(0, 0, 0);
    INT EmissiveTexture = -1;
    INT NormalTexture = -1;
    INT OcclusionTexture = -1;
  
    std::string AlphaMode = "OPAQUE";         // "OPAQUE", "MASK", "BLEND"
    FLT AlphaCutoff = 0.5f;
    BOOL DoubleSided = FALSE;
  
    // Для конвертации в ваш material класс
    vec3 GetKa() const { return vec3(0.1f); } // Ambient
    vec3 GetKd() const { return vec3(BaseColorFactor.X, BaseColorFactor.Y, BaseColorFactor.Z); }
    vec3 GetKs() const { return vec3(0.5f); } // Specular
    FLT GetPh() const { return 32.0f; }       // Phong
    FLT GetTrans() const { return BaseColorFactor.W; } // Transparency from alpha
  };

  //Joint bone
  struct bone
  {
      INT NodeIndex;            // node index
      dmatr InverseBindMatrix;  // inversed bind matrix
      dmatr CurrentMatrix;      // current matrix
  };

  //set of bones
  struct skin
  {
      std::string Name;                       // name
      INT SkeletonRoot;                       // root bone
      std::vector<INT> Joints;                // node indexes
      INT InverseBindMatricesAccessor;        // Accessor for inversed matrix bind
      std::vector<matr::matr_data> InverseBindMatrices; // inversed bind matrixes
  };

  //animation
  struct animation
  {
      std::string Name;  // animation name
    
      struct channel
      {
          INT Sampler;      // sampler index
          INT Node;         // node index
          std::string Path; // "translation", "rotation", "scale"
      };
    
      struct sampler
      {
          INT Input;                 // Accessor for time binds
          INT Output;                // Accessor for values
          std::string Interpolation; // "LINEAR", "STEP", "CUBICSPLINE"
      };
    
      std::vector<channel> Channels;
      std::vector<sampler> Samplers;
      std::vector<FLT> InputTimes;           // time binds
      std::vector<dvec3> OutputTranslations; // translations
      std::vector<dvec4> OutputRotations;    // quat rotations
      std::vector<dvec3> OutputScales;       // scales
  };

  /* JSON files loader class */
  class loader
  {
  public:
    std::string File;
    SIZE_T Pos;
    std::vector<data_buffer> Buffers;
    std::vector<buffer_view> BufferViews;
    std::vector<accessor> Accessors;
    std::vector<mesh> Meshes;
    std::vector<node> Nodes;
    std::vector<scena> Scenes;
    std::vector<sampler> Samplers;
    std::vector<textura> Textures;
    std::vector<material_gltf> Materials;
    //std::vector<material> Materials;
    std::vector<imaga> Images;
    INT SceneNo;
    std::map<std::string, accessor_type> AccessorTypes;
    std::map<accessor_type, INT> AccessorTypesCount;
    std::map<component_type, INT> ComponentTypes;
    std::map<component_type, SIZE_T> ComponentSizes;
    std::vector<skin> Skins;
    std::vector<animation> Animations;

    loader( VOID ) : Pos(0), SceneNo(0)
    {
      AccessorTypes["SCALAR"] = accessor_type::eSCALAR;
      AccessorTypes["VEC2"] = accessor_type::eVEC2;
      AccessorTypes["VEC3"] = accessor_type::eVEC3;
      AccessorTypes["VEC4"] = accessor_type::eVEC4;
      AccessorTypes["MAT2"] = accessor_type::eMAT2;
      AccessorTypes["MAT3"] = accessor_type::eMAT3;
      AccessorTypes["MAT4"] = accessor_type::eMAT4;
      AccessorTypesCount[accessor_type::eSCALAR] = 1;
      AccessorTypesCount[accessor_type::eVEC2] = 2;
      AccessorTypesCount[accessor_type::eVEC3] = 3;
      AccessorTypesCount[accessor_type::eVEC4] = 4;
      AccessorTypesCount[accessor_type::eMAT2] = 4;
      AccessorTypesCount[accessor_type::eMAT3] = 9;
      AccessorTypesCount[accessor_type::eMAT4] = 16;
      ComponentTypes[component_type::eI8] = 0x1400;
      ComponentTypes[component_type::eU8] = 0x1401;
      ComponentTypes[component_type::eI16] = 0x1402;
      ComponentTypes[component_type::eU16] = 0x1403;
      ComponentTypes[component_type::eI32] = 0x1404;
      ComponentTypes[component_type::eU32] = 0x1405;
      ComponentTypes[component_type::eF32] = 0x1406;
      ComponentSizes[component_type::eI8] = 1;
      ComponentSizes[component_type::eU8] = 1;
      ComponentSizes[component_type::eI16] = 2;
      ComponentSizes[component_type::eU16] = 2;
      ComponentSizes[component_type::eI32] = 4;
      ComponentSizes[component_type::eU32] = 4;
      ComponentSizes[component_type::eF32] = 4;
    }

    loader(const loader& other) 
    {
        *this = other;
    }
    
    loader& operator=(const loader& other) 
    {
        if (this == &other) return *this;
        
        File = other.File;
        Pos = other.Pos;
        Buffers = other.Buffers;
        BufferViews = other.BufferViews;
        Accessors = other.Accessors;
        Meshes = other.Meshes;
        Nodes = other.Nodes;
        Scenes = other.Scenes;
        SceneNo = other.SceneNo;
        Images = other.Images;
        Samplers = other.Samplers;
        Textures = other.Textures;
        Materials = other.Materials;
        AccessorTypes = other.AccessorTypes;
        AccessorTypesCount = other.AccessorTypesCount;
        ComponentTypes = other.ComponentTypes;
        ComponentSizes = other.ComponentSizes;
        Skins = other.Skins;
        Animations = other.Animations;
        
        return *this;
    }
  
    VOID LoadAnimations( json &Model )
    {
      if (!Model["animations"].IsArray())
        return;
            
      for (auto &animJson : Model["animations"].GetArray())
      {
        animation anim;
        anim.Name = animJson["name"].GetString("");
            
        if (animJson["samplers"].IsArray())
        {
          for (auto &samplerJson : animJson["samplers"].GetArray())
          {
            animation::sampler sampler;
            sampler.Input = samplerJson["input"].GetInt(-1);
            sampler.Output = samplerJson["output"].GetInt(-1);
            sampler.Interpolation = samplerJson["interpolation"].GetString("LINEAR");
            anim.Samplers.push_back(sampler);
          }
        }
            
        if (animJson["channels"].IsArray())
        {
          for (auto &channelJson : animJson["channels"].GetArray())
          {
            animation::channel channel;
            channel.Sampler = channelJson["sampler"].GetInt(-1);
            channel.Node = channelJson["target"]["node"].GetInt(-1);
            channel.Path = channelJson["target"]["path"].GetString("");
            anim.Channels.push_back(channel);
          }
        }
            
        Animations.push_back(anim);
      }
    }
    //VOID LoadSkins( json &Model )
    //{
    //  if (!Model["skins"].IsArray())
    //      return;
    //        
    //  for (auto &skinJson : Model["skins"].GetArray())
    //  {
    //    skin sk;
    //    sk.Name = skinJson["name"].GetString("");
    //    sk.SkeletonRoot = skinJson["skeleton"].GetInt(-1);
    //    sk.InverseBindMatricesAccessor = skinJson["inverseBindMatrices"].GetInt(-1);
    //        
    //    if (skinJson["joints"].IsArray())
    //    {
    //      for (auto &joint : skinJson["joints"].GetArray())
    //      {
    //        sk.Joints.push_back(joint.GetInt(-1));
    //      }
    //    }
    //        
    //    if (sk.InverseBindMatricesAccessor != -1)
    //    {
    //      auto matrices = GetAccessorData<matr>(sk.InverseBindMatricesAccessor);
    //      sk.InverseBindMatrices = std::move(matrices);
    //    }
    //        
    //    Skins.push_back(sk);
    //  }
    //}

    /* Parse JSON file function.
     * ARGUMENTS:
     *   - Json text:
     *       const std::string &JsonText;
     * RETURNS:
     *   (json) Result of opening file.
     */
    json Parse( const std::string &JsonText = "" )
    {
      if (JsonText != "")
        File = JsonText;
      Pos = 0;
      SkipCommentWhiteSpace();
      json result = ParseValue();
      SkipCommentWhiteSpace();

      if (Pos < File.length())
        throw std::runtime_error("File hasn't been read parsed entirely");

      return result;
    } /* End of 'Load' function */

    /* Get accessor data span function.
     * ARGUMENTS:
     *   - accessor index:
     *       INT AccessorIndex;
     * RETURNS:
     *   (std::vector<type>) result span value (slice from buffer).
     */
    //template<typename type>
    //  std::vector<type> GetAccessorData( INT AccessorIndex )
    //  {
    //    std::vector<type> &&res {};
    //    if (AccessorIndex == -1)
    //      return res;
    //    accessor &ac = Accessors[AccessorIndex];
    //    //if (AccessorTypesCount[ac.Type] * /*std::get<0>*/(ComponentTypes[ac.ComponentType]) != sizeof(type))
    //    //  return res;
    //    if (AccessorTypesCount[ac.Type] * sizeof(component_type) != sizeof(type))
    //      return res;
    //    buffer_view &bv = BufferViews[ac.BufferView];
    //    INT stride = bv.Stride;
    //    if (stride == 0)
    //      stride = AccessorTypesCount[ac.Type] * /*std::get<0>*/(ComponentTypes[ac.ComponentType]);
    //    std::span<BYTE> bv_data(&Buffers[bv.Buffer].Data[bv.Offset], bv.Length);
    //    std::span<BYTE> ac_data(&bv_data[ac.ByteOffset], ac.Count * stride);
    //    res.resize(ac.Count);
    //    if (bv.Stride == 0)
    //      CopyMemory(reinterpret_cast<VOID *>(&res[0]), reinterpret_cast<VOID *>(&ac_data[0]), ac.Count * sizeof(type));
    //    else
    //      for (INT i = 0; i < ac.Count; i++)
    //        CopyMemory(reinterpret_cast<VOID *>(&res[i]), reinterpret_cast<VOID *>(&ac_data[stride * i]), sizeof(type));
    //    return res;
    //  } /* End of 'GetAccessorData' function */
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Для float (обычно VEC3 для позиций)

  //template<typename type>
  //std::vector<type> GetAccessorData( INT AccessorIndex )
  //{
  //    std::vector<type> res;
  //  
  //    if (AccessorIndex < 0 || AccessorIndex >= (INT)Accessors.size())
  //        return res;
  //  
  //    const accessor &ac = Accessors[AccessorIndex];
  //  
  //    auto compSizeIt = ComponentSizes.find(ac.ComponentType);
  //    if (compSizeIt == ComponentSizes.end())
  //    {
  //        std::cerr << "Unknown component type: " << (INT)ac.ComponentType << "\n";
  //        return res;
  //    }
  //    SIZE_T componentSize = compSizeIt->second;
  //  
  //    auto typeCountIt = AccessorTypesCount.find(ac.Type);
  //    if (typeCountIt == AccessorTypesCount.end())
  //    {
  //        std::cerr << "Unknown accessor type\n";
  //        return res;
  //    }
  //    INT componentsPerElement = typeCountIt->second;
  //  
  //    SIZE_T expectedElementSize = componentSize * componentsPerElement;
  //    if (sizeof(type) != expectedElementSize)
  //    {
  //        std::cerr << "Type size mismatch. Expected: " << expectedElementSize 
  //                  << ", got: " << sizeof(type) << "\n";
  //        return res;
  //    }
  //  
  //    if (ac.BufferView < 0 || ac.BufferView >= (INT)BufferViews.size())
  //        return res;
  //  
  //    const buffer_view &bv = BufferViews[ac.BufferView];
  //  
  //    if (bv.Buffer < 0 || bv.Buffer >= (INT)Buffers.size())
  //        return res;
  //  
  //    const data_buffer &buffer = Buffers[bv.Buffer];
  //  
  //    SIZE_T startOffset = bv.Offset + ac.ByteOffset;
  //    SIZE_T totalNeededBytes = ac.Count * (bv.Stride > 0 ? bv.Stride : expectedElementSize);
  //  
  //    if (startOffset + totalNeededBytes > buffer.Data.size())
  //    {
  //        std::cerr << "Buffer access out of bounds\n";
  //        return res;
  //    }
  //  
  //    res.resize(ac.Count);
  //    const BYTE* srcData = buffer.Data.data() + startOffset;
  //  
  //    if (bv.Stride == 0 || bv.Stride == (INT)expectedElementSize)
  //    {
  //        memcpy(res.data(), srcData, ac.Count * expectedElementSize);
  //    }
  //    else
  //    {
  //        for (SIZE_T i = 0; i < ac.Count; i++)
  //        {
  //            memcpy(&res[i], srcData + i * bv.Stride, expectedElementSize);
  //        }
  //    }
  //  
  //    return res;
  //}

  //std::vector<float> GetFloatData(INT AccessorIndex)
  //{
  //    return GetAccessorData<float>(AccessorIndex);
  //}

  //struct vec3 { float x, y, z; };
  //std::vector<vec3> GetVec3Data(INT AccessorIndex)
  //{
  //    const accessor &ac = Accessors[AccessorIndex];
  //    if (ac.Type != accessor_type::eVEC3 || ac.ComponentType != component_type::eF32)
  //        return {};
  //    return GetAccessorData<vec3>(AccessorIndex);
  //}

  //struct vec2 { float x, y; };
  //std::vector<vec2> GetVec2Data(INT AccessorIndex)
  //{
  //    const accessor &ac = Accessors[AccessorIndex];
  //    if (ac.Type != accessor_type::eVEC2 || ac.ComponentType != component_type::eF32)
  //        return {};
  //    return GetAccessorData<vec2>(AccessorIndex);
  //}

  //std::vector<uint32_t> GetIndexData(INT AccessorIndex)
  //{
  //    const accessor &ac = Accessors[AccessorIndex];
  //  
  //    if (ac.ComponentType == component_type::eU16)
  //    {
  //        auto data16 = GetAccessorData<uint16_t>(AccessorIndex);
  //        std::vector<uint32_t> result(data16.begin(), data16.end());
  //        return result;
  //    }
  //    else if (ac.ComponentType == component_type::eU32)
  //    {
  //        return GetAccessorData<uint32_t>(AccessorIndex);
  //    }
  //  
  //    return {};
  //}

  /* Get accessor data span function. 
   * ARGUMENTS: 
   *   - accessor index: 
   *       INT AccessorIndex; 
   * RETURNS: 
   *   (std::vector<type>) result span value (slice from buffer). 
   */ 
  template<typename type> 
  std::vector<type> GetAccessorData( INT AccessorIndex ) 
  { 
      std::vector<type> res; 
    
      if (AccessorIndex == -1 || AccessorIndex >= (INT)Accessors.size()) 
        return res; 
    
      accessor &ac = Accessors[AccessorIndex]; 
    
      auto compSizeIt = ComponentSizes.find(ac.ComponentType);
      if (compSizeIt == ComponentSizes.end())
        return res;
      SIZE_T componentSize = compSizeIt->second;
    
      auto typeCountIt = AccessorTypesCount.find(ac.Type);
      if (typeCountIt == AccessorTypesCount.end())
        return res;
      INT componentsPerElement = typeCountIt->second;
    
      buffer_view &bv = BufferViews[ac.BufferView]; 
      INT stride = bv.Stride; 
      if (stride == 0) 
        stride = componentsPerElement * componentSize; 
    
      // check data size
      SIZE_T expectedDataSize = componentsPerElement * componentSize * ac.Count;
      if (bv.Offset + ac.ByteOffset + expectedDataSize > Buffers[bv.Buffer].Data.size())
          return res;
    
      BYTE* dataPtr = &Buffers[bv.Buffer].Data[bv.Offset + ac.ByteOffset];
    
      res.resize(ac.Count);
    
      if (bv.Stride == 0)
      {
          if (sizeof(type) == componentsPerElement * componentSize)
          {
              CopyMemory(reinterpret_cast<VOID *>(&res[0]), reinterpret_cast<VOID *>(dataPtr), ac.Count * sizeof(type));
          }
          else
          {
              for (SIZE_T i = 0; i < ac.Count; i++)
              {
                  CopyMemory(reinterpret_cast<VOID *>(&res[i]), reinterpret_cast<VOID *>(dataPtr + i * componentsPerElement * componentSize), sizeof(type));
              }
          }
      }
      else
      {
          for (SIZE_T i = 0; i < ac.Count; i++)
          {
              CopyMemory(reinterpret_cast<VOID *>(&res[i]), reinterpret_cast<VOID *>(dataPtr + i * stride), sizeof(type));
          }
      }
    
      return res; 
  } /* End of 'GetAccessorData' function */

  VOID LoadSkins( json &Model )
  {
      if (!Model["skins"].IsArray())
        return;
    
      for (auto &skinJson : Model["skins"].GetArray())
      {
        skin sk;
        sk.Name = skinJson["name"].GetString("");
        sk.SkeletonRoot = skinJson["skeleton"].GetInt(-1);
        sk.InverseBindMatricesAccessor = skinJson["inverseBindMatrices"].GetInt(-1);
        
        if (skinJson["joints"].IsArray())
        {
          for (auto &joint : skinJson["joints"].GetArray())
          {
            sk.Joints.push_back(joint.GetInt(-1));
          }
        }
        
        if (sk.InverseBindMatricesAccessor != -1)
        {
          auto matrices = GetAccessorData<matr::matr_data>(sk.InverseBindMatricesAccessor);
            
          std::cout << "Loading skin '" << sk.Name << "' with " 
                    << sk.Joints.size() << " joints, loaded " 
                    << matrices.size() << " matrices\n";
            
          if (matrices.size() != sk.Joints.size())
          {
            std::cerr << "WARNING: Mismatch! " << sk.Joints.size() 
                      << " joints but " << matrices.size() << " matrices\n";
          }
            
          sk.InverseBindMatrices = std::move(matrices);
        }
        else
        {
          std::cout << "Skin '" << sk.Name << "' has no inverse bind matrices (identity matrices will be used)\n";
          sk.InverseBindMatrices.resize(sk.Joints.size(), matr::Identity());
        }
        
        Skins.push_back(sk);
      }
    
    std::cout << "Loaded " << Skins.size() << " skins\n";
  }

  std::vector<UINT> GetIndexData(INT AccessorIndex)
  {
      std::vector<UINT> res;
    
      if (AccessorIndex < 0 || AccessorIndex >= (INT)Accessors.size())
          return res;
    
      const accessor& ac = Accessors[AccessorIndex];
    
      if (ac.Type != accessor_type::eSCALAR)
          return res;
    
      if (ac.ComponentType == component_type::eU8)
      {
          auto data8 = GetAccessorData<UINT8>(AccessorIndex);
          res.reserve(data8.size());
          for (auto val : data8)
              res.push_back(static_cast<UINT>(val));
      }
      else if (ac.ComponentType == component_type::eU16)
      {
          auto data16 = GetAccessorData<UINT16>(AccessorIndex);
          res.reserve(data16.size());
          for (auto val : data16)
              res.push_back(static_cast<UINT>(val));
      }
      else if (ac.ComponentType == component_type::eU32)
      {
          return GetAccessorData<UINT>(AccessorIndex);
      }
    
      return res;
  }
    /* Loads glTF from file function.
     * ARGUMENTS:
     *   - path to glTF file:
     *       const std::string &FileName;
     * RETURNS: None.
     */
    VOID LoadG( const std::string &FileName )
    {
      try
      {
        std::string path = std::filesystem::path(FileName).parent_path().string() + "\\";
        std::optional<json> ModelP = loader::Load(FileName);
        if (ModelP.has_value())
        {
          json &Model = *ModelP;
 
          // Read buffers
          for (auto &bf : Model["buffers"].GetArray())
          {
            const std::string uri = bf["uri"].GetString();
            INT buffer_length = bf["byteLength"].GetInt();
            data_buffer buf;
 
            if (std::filesystem::exists(path + uri))
            {
              // Read buffer from file
              std::ifstream f(path + uri, std::ios::binary | std::ios::ate);
              auto flen = f.tellg();
              std::vector<BYTE> filebuf(flen);
              f.seekg(0, std::ios::beg);
              f.read(reinterpret_cast<char*>(filebuf.data()), flen);
              buf.Data = std::move(filebuf);
            }
            else if (uri.find(";base64,") != std::string::npos)
              // Decode buffer from string
                buf.Data = ConvertBase64(uri, buffer_length);
            else
              throw std::runtime_error("File (buffer) " + uri + " is not found");
            Buffers.emplace_back(buf);
          }
 
          // Read buffer views
          for (auto &view : Model["bufferViews"].GetArray())
            BufferViews.push_back(buffer_view
            {
              .Buffer = view["buffer"].GetInt(),
              .Offset = (SIZE_T)view["byteOffset"].GetInt(),
              .Length = (SIZE_T)view["byteLength"].GetInt(),
              .Stride = view["byteStride"].GetInt(),
            });
 
          // Read accessories
          for (auto &acs : Model["accessors"].GetArray())
          {
            Accessors.push_back(accessor
            {
              .BufferView = acs["bufferView"].GetInt(),
              .ByteOffset = (SIZE_T)acs["byteOffset"].GetInt(),
              .ComponentType = component_type(acs["componentType"].GetInt()),
              .Type = accessor_type(/*std::get<0>*/(AccessorTypes[acs["type"].GetString()])),
              .Count = (SIZE_T)acs["count"].GetInt(),
              .IsNormalized = FALSE,
            });
          }
 
          // Read meshes with primitives
          for (auto &ms : Model["meshes"].GetArray())
          {
            std::vector<primitive> Prims;
            for (auto &pr : ms["primitives"].GetArray())
            {
              Prims.push_back(primitive
              {
                .PositionAccessor = pr["attributes"]["POSITION"].GetInt(-1),
                .NormalAccessor = pr["attributes"]["NORMAL"].GetInt(-1),
                .TexCoord0Accessor = pr["attributes"]["TEXCOORD_0"].GetInt(-1),
                .TexCoord1Accessor = pr["attributes"]["TEXCOORD_1"].GetInt(-1),
                .Color0Accessor = pr["attributes"]["COLOR_0"].GetInt(-1),
                .Joints0Accessor = pr["attributes"]["JOINTS_0"].GetInt(-1),
                .Weights0Accessor = pr["attributes"]["WEIGHTS_0"].GetInt(-1),
                .IndexAccessor = pr["indices"].GetInt(-1),
                .MaterialNo = pr["material"].GetInt(-1),
                .Mode = draw_mode_type(pr["mode"].GetInt(static_cast<INT>(draw_mode_type::eTRIANGLES))),
              });
            }
            Meshes.push_back(mesh
            {
              .Name = ms["name"].GetString(),
              .Prims = std::move(Prims),
            });
          }
 
          // Read nodes
          for (auto &nd : Model["nodes"].GetArray())
          {
            std::vector<INT> SubnodeIndexes;
            for (auto &chld : nd["children"].GetArray())
              SubnodeIndexes.push_back(chld.GetInt(-1));
            std::vector<DBL> Matrix;
            for (auto &mte : nd["matrix"].GetArray())
              Matrix.push_back(mte.GetDouble());
            //std::for_each()
            auto rot = nd["rotation"].GetArray();
            auto scl = nd["scale"].GetArray();
            auto tra = nd["translation"].GetArray();
            Nodes.push_back(node
            {
              .Name = nd["name"].GetString(),
              .Mesh = nd["mesh"].GetInt(-1),
              .Subnodes = std::move(SubnodeIndexes),
              .Skin = nd["skin"].GetInt(-1),
              .IsMatrixUse = Matrix.size() != 0,
              .Matrix = Matrix.size() != 0 ? dmatr(reinterpret_cast<DBL (*)[4]>(Matrix.data())) : dmatr::Identity(),
              .Translation = tra.size() == 0 ? dvec3(0) : dvec3{tra[0].GetDouble(), tra[1].GetDouble(), tra[2].GetDouble()},
              //.Rotation = rot.size() == 0 ? dvec4(0, 0, 0, 1) : dvec4{rot[0].GetDouble(0), rot[1].GetDouble(0), rot[2].GetDouble(0), rot[3].GetDouble(1)},
              .Rotation = rot.size() < 4 ? dvec4(0, 0, 0, 1) : dvec4{
                  rot[0].GetDouble(0.0),  // x
                  rot[1].GetDouble(0.0),  // y
                  rot[2].GetDouble(0.0),  // z
                  rot[3].GetDouble(1.0)   // w
              },
              .Scale = scl.size() == 0 ? dvec3(1) : dvec3{scl[0].GetDouble(), scl[1].GetDouble(), scl[2].GetDouble()},
            });
            if (!Nodes.back().IsMatrixUse)
                Nodes.back().Matrix =
                    dmatr::Scale(Nodes.back().Scale) *
                    dmatr::RotateQuat(Nodes.back().Rotation) *
                    dmatr::Translate(Nodes.back().Translation);
          }
 
          // Read scenes
          for (auto &sc : Model["scenes"].GetArray())
          {
            std::vector<INT> NodeIndexes;
            for (auto &nd : sc["nodes"].GetArray())
              NodeIndexes.push_back(nd.GetInt(-1));
            Scenes.push_back(scena
            {
              .Name = sc["name"].GetString(),
              .RootNodes = std::move(NodeIndexes),
            });
          }
          SceneNo = Model["scene"].GetInt(-1);
          if (SceneNo == -1 && Scenes.size() > 0)
            SceneNo = 0;
 
          std::function<VOID( INT, const dmatr & )> ComputeWorldMatrix =
            [this, &ComputeWorldMatrix]( INT NodeIndex, const dmatr &ParentWorld )
            {
              const node &nd = Nodes[NodeIndex];
              dmatr world = nd.Matrix * ParentWorld;
              Nodes[NodeIndex].WorldMatrix = world;
              for (INT subnode : nd.Subnodes)
                ComputeWorldMatrix(subnode, world);
            };
          for (auto &sc : Scenes)
            for (auto &rootnd : sc.RootNodes)
              ComputeWorldMatrix(rootnd, dmatr::Identity());

          // Read materials
          for (auto &mtl : Model["materials"].GetArray())
          {
            material_gltf mat;
            mat.Name = mtl["name"].GetString("Unnamed Material");
  
            // PBR Metallic-Roughness
            auto pbr = mtl["pbrMetallicRoughness"];
            if (!pbr.IsNull())
            {
              // Base color texture
              auto bct = pbr["baseColorTexture"];
              if (!bct.IsNull())
                mat.BaseColorTexture = bct["index"].GetInt(-1);

              // Metallic-roughness texture  
              auto mrt = pbr["metallicRoughnessTexture"];
              if (!mrt.IsNull())
                mat.MetallicRoughnessTexture = mrt["index"].GetInt(-1);
              // Base color factor (RGBA)
              auto bcf = pbr["baseColorFactor"];
              if (!bcf.IsNull() && bcf.IsArray())
              {
                auto arr = bcf.GetArray();
                if (arr.size() >= 4)
                {
                  mat.BaseColorFactor = vec4(
                    static_cast<FLT>(arr[0].GetDouble(1.0)),
                    static_cast<FLT>(arr[1].GetDouble(1.0)),
                    static_cast<FLT>(arr[2].GetDouble(1.0)),
                    static_cast<FLT>(arr[3].GetDouble(1.0))
                  );
                }
              }
              // Metallic and roughness factors
              mat.MetallicFactor = static_cast<FLT>(pbr["metallicFactor"].GetDouble(1.0));
              mat.RoughnessFactor = static_cast<FLT>(pbr["roughnessFactor"].GetDouble(1.0));
            }
            else //KHR_materials_pbrSpecularGlossiness
            {
              pbr = mtl["extensions"]["KHR_materials_pbrSpecularGlossiness"];
              auto bct = pbr["diffuseTexture"];
              if (!pbr.IsNull())
                mat.BaseColorTexture = bct["index"].GetInt(-1);

              auto bcf = pbr["diffuseFactor"];
              if (!bcf.IsNull() && bcf.IsArray())
              {
                auto arr = bcf.GetArray();
                if (arr.size() >= 4)
                {
                  mat.BaseColorFactor = vec4(
                    static_cast<FLT>(arr[0].GetDouble(1.0)),
                    static_cast<FLT>(arr[1].GetDouble(1.0)),
                    static_cast<FLT>(arr[2].GetDouble(1.0)),
                    static_cast<FLT>(arr[3].GetDouble(1.0))
                  );
                }
              }

              auto spf = mtl["specularFactor"];
              if (!spf.IsNull() && spf.IsArray())
              {
                auto arr = spf.GetArray();
                if (arr.size() >= 3)
                {
                  mat.SpecularFactor.X = static_cast<FLT>(arr[0].GetDouble(1.0));
                  mat.SpecularFactor.Y = static_cast<FLT>(arr[1].GetDouble(1.0));
                  mat.SpecularFactor.Z = static_cast<FLT>(arr[2].GetDouble(1.0));
                }
              }
            }
  
            // Normal texture
            auto nt = mtl["normalTexture"];
            if (!nt.IsNull())
              mat.NormalTexture = nt["index"].GetInt(-1);
  
            // Emissive texture
            auto et = mtl["emissiveTexture"];
            if (!et.IsNull())
              mat.EmissiveTexture = et["index"].GetInt(-1);
            // Emissive factor
            auto ef = mtl["emissiveFactor"];
            if (!ef.IsNull() && ef.IsArray())
            {
                auto arr = ef.GetArray();
                if (arr.size() >= 3)
                {
                    mat.EmissiveFactor.X = static_cast<FLT>(arr[0].GetDouble(0.0));
                    mat.EmissiveFactor.Y = static_cast<FLT>(arr[1].GetDouble(0.0));
                    mat.EmissiveFactor.Z = static_cast<FLT>(arr[2].GetDouble(0.0));
                }
            }  
            // Occlusion texture  
            auto ot = mtl["occlusionTexture"];
            if (!ot.IsNull())
              mat.OcclusionTexture = ot["index"].GetInt(-1);
            // Alpha mode and cutoff
            mat.AlphaMode = mtl["alphaMode"].GetString("OPAQUE");
            mat.AlphaCutoff = static_cast<FLT>(mtl["alphaCutoff"].GetDouble(0.5));
            mat.DoubleSided = mtl["doubleSided"].GetBool(FALSE);

            Materials.push_back(mat);
          }

          // Read images
          for (auto &img : Model["images"].GetArray())
          {
            //      "uri": "textures/08___Default_baseColor.jpeg"
            //========================
            //      "mimeType": "image/png",
            //      "uri": "data:image/png;base64,iVBORw0KGgoAAAANSUhE...=="
            std::string Name {};
            std::string uri = img["uri"].GetString();
            std::string mime = img["mimeType"].GetString();
            INT bv_no = img["bufferView"].GetInt(-1);
            std::string name = img["name"].GetString();
            std::string postfix;
            std::vector<BYTE> data;
            if (uri != "" && std::filesystem::exists(path + uri))
            {
              // Read image from file
              std::ifstream f(path + uri, std::ios::binary | std::ios::ate);
              auto flen = f.tellg();
              std::vector<BYTE> filebuf(flen);
              f.seekg(0, std::ios::beg);
              f.read(reinterpret_cast<char*>(filebuf.data()), flen);
              data = std::move(filebuf);
              Name = uri.erase(0, uri.find_last_of('/') + 1);
              // vivk::image img(filebuf);
            }
            else if (/*mime.find("image/") != std::string::npos && */uri.find(";base64,") != std::string::npos)
            {
              // Decode image from string
              // vivk::image img(DecodeBase64(uri, -1));
              Name = name + '.' + mime.erase(0, mime.find_last_of('/') + 1);
              data = ConvertBase64(uri, -1);
            }
            else if (bv_no != -1)
            {
              buffer_view &bv = BufferViews[bv_no];
              std::span<BYTE> bv_data(&Buffers[bv.Buffer].Data[bv.Offset], bv.Length);
              data.resize(bv.Length);
              memcpy(reinterpret_cast<VOID *>(&data[0]), reinterpret_cast<VOID *>(&bv_data[0]), bv.Length);
              Name = name + '.' + mime.erase(0, mime.find_last_of('/') + 1);
            }
            else
              throw std::runtime_error("Image data is not found/load");
            Images.emplace_back(imaga
            {
              .Name = Name,
              .ImageData = std::move(data),
            });
          }
 
          // Read samplers
          for (auto &smpl : Model["samplers"].GetArray())
          {
            //    {
            //      "magFilter": 9729,
            //      "minFilter": 9987,
            //      "wrapS": 10497,
            //      "wrapT": 10497
            //    }
            Samplers.push_back(sampler
            {
              .MagFilter = static_cast<sampler_filter_type>(smpl["magFilter"].GetInt(static_cast<INT>(sampler_filter_type::eNEAREST))),
              .MinFilter = static_cast<sampler_filter_type>(smpl["minFilter"].GetInt(static_cast<INT>(sampler_filter_type::eNEAREST))),
              .AddressS = static_cast<sampler_address_type>(smpl["wrapS"].GetInt(static_cast<INT>(sampler_address_type::eREPEAT))),
              .AddressT = static_cast<sampler_address_type>(smpl["wrapT"].GetInt(static_cast<INT>(sampler_address_type::eREPEAT))),
            });
          }
 
          // Read textures
          for (auto &tex : Model["textures"].GetArray())
          {
            //    {
            //      "sampler": 1,
            //      "source": 1,
            //      "name": "base_color_texture"
            //    }
            Textures.push_back(textura
            {
              .Name = tex["name"].GetString(),
              .ImageNo = tex["source"].GetInt(-1),
              .SamplerNo = tex["sampler"].GetInt(-1),
            });
          }

          LoadSkins(Model);
          LoadAnimations(Model);



          //for (auto &sk : Skins)
          //{
          //    if (sk.InverseBindMatricesAccessor != -1 && !sk.InverseBindMatrices.empty())
          //    {
          //        std::cout << "Processing skin: " << sk.Name 
          //                  << " with " << sk.Joints.size() << " joints\n";
        
          //        if (sk.Joints.size() != sk.InverseBindMatrices.size())
          //        {
          //            std::cerr << "ERROR: Skin " << sk.Name 
          //                      << " has " << sk.Joints.size() << " joints but " 
          //                      << sk.InverseBindMatrices.size() << " inverse bind matrices!\n";
          //            continue;
          //        }
        
          //        // FinalMatrix = WorldMatrix(joint) * InverseBindMatrix
        
          //        // std::vector<matr::matr_data> FinalMatrices;
        
          //        for (size_t i = 0; i < sk.Joints.size(); i++)
          //        {
          //            INT jointIndex = sk.Joints[i];
          //            if (jointIndex >= 0 && jointIndex < (INT)Nodes.size())
          //            {
          //                const node &jointNode = Nodes[jointIndex];
          //      
          //                matr worldMat;
          //                matr::matr_data invBindMat = sk.InverseBindMatrices[i];
          //      
          //                for (int row = 0; row < 4; row++)
          //                {
          //                    for (int col = 0; col < 4; col++)
          //                    {
          //                        worldMat.M[row][col] = static_cast<FLT>(jointNode.WorldMatrix.M[row][col]);
          //                    }
          //                }
          //      
          //                matr finalMat = worldMat * invBindMat;
          //                invBindMat = finalMat.M;
          //      
          //      
          //                if (i < 3)
          //                {
          //                    std::cout << "  Joint " << i << " (node " << jointIndex 
          //                              << "): " << jointNode.Name << "\n";
          //                    std::cout << "  InverseBindMatrix[" << i << "]:\n";
          //                    for (int row = 0; row < 4; row++)
          //                    {
          //                        std::cout << "    ";
          //                        for (int col = 0; col < 4; col++)
          //                            std::cout << invBindMat.M[row][col] << " ";
          //                        std::cout << "\n";
          //                    }
          //                    std::cout << "  WorldMatrix:\n";
          //                    for (int row = 0; row < 4; row++)
          //                    {
          //                        std::cout << "    ";
          //                        for (int col = 0; col < 4; col++)
          //                            std::cout << worldMat.M[row][col] << " ";
          //                        std::cout << "\n";
          //                    }
          //                }
          //            }
          //            else
          //            {
          //                std::cerr << "ERROR: Invalid joint index " << jointIndex 
          //                          << " in skin " << sk.Name << "\n";
          //            }
          //        }
          //    }
          //}
          for (auto &anim : Animations)
          {
              for (auto &sampler : anim.Samplers)
              {
                  if (sampler.Input != -1)
                  {
                      auto times = GetAccessorData<FLT>(sampler.Input);
                      anim.InputTimes.insert(anim.InputTimes.end(), times.begin(), times.end());
                  }
        
                  if (sampler.Output != -1)
                  {
                      const auto &acc = Accessors[sampler.Output];
                      if (acc.Type == accessor_type::eVEC3)
                      {
                          auto vecs = GetAccessorData<dvec3>(sampler.Output);
                          anim.OutputTranslations.insert(anim.OutputTranslations.end(), 
                                                         vecs.begin(), vecs.end());
                      }
                      else if (acc.Type == accessor_type::eVEC4)
                      {
                          auto vecs = GetAccessorData<dvec4>(sampler.Output);
                          anim.OutputRotations.insert(anim.OutputRotations.end(), 
                                                      vecs.begin(), vecs.end());
                      }
                      else if (acc.Type == accessor_type::eVEC3)
                      {
                          auto vecs = GetAccessorData<dvec3>(sampler.Output);
                          anim.OutputScales.insert(anim.OutputScales.end(), 
                                                   vecs.begin(), vecs.end());
                      }
                  }
              }
          }
 
          // Read materials
          for (auto &mtl : Model["materials"].GetArray())
          {
            //    {
            //      "doubleSided": true,
            //      "emissiveFactor": [
            //        1.0,
            //        1.0,
            //        1.0
            //      ],
            //      "emissiveTexture": {
            //        "index": 0
            //      },
            //      "extensions": {
            //        "KHR_materials_clearcoat": {
            //          "clearcoatFactor": 1.0,
            //          "clearcoatRoughnessFactor": 0.04
            //        }
            //      },
            //      "name": "918rsr_brake_lights",
            //      "pbrMetallicRoughness": {
            //        "baseColorTexture": {
            //          "index": 0
            //        },
            //        "metallicFactor": 0.0,
            //        "roughnessFactor": 0.6
            //      }
            //    },
            //=============================
            //    {
            //      "alphaMode": "BLEND",
            //      "doubleSided": true,
            //      "name": "918rsr_exterior_mm_badges",
            //      "pbrMetallicRoughness": {
            //        "baseColorTexture": {
            //          "index": 1
            //        },
            //        "metallicFactor": 0.0,
            //        "roughnessFactor": 0.6
            //      }
            //    },
            //=============================
            //    {
            //      "alphaMode": "BLEND",
            //      "doubleSided": true,
            //      "name": "gauges",
            //      "pbrMetallicRoughness": {
            //        "baseColorFactor": [
            //          1.0,
            //          1.0,
            //          1.0,
            //          0.0
            //        ],
            //        "metallicFactor": 0.0,
            //        "roughnessFactor": 0.6
            //      }
            //    },
            //=============================
            //    {
            //      "doubleSided": true,
            //      "name": "mirror",
            //      "pbrMetallicRoughness": {
            //        "roughnessFactor": 0.0
            //      }
            //    },
            //=============================
            //    {
            //      "doubleSided": true,
            //      "name": "motec_Slot_1",
            //      "pbrMetallicRoughness": {
            //        "baseColorTexture": {
            //          "index": 9
            //        },
            //        "metallicFactor": 0.0,
            //        "roughnessFactor": 0.6
            //      }
            //    },
            
            /*auto bcf = mtl["pbrMetallicRoughness"]["baseColorFactor"].GetArray();
            if (bcf.size() == 0)
              bcf = mtl["extensions"]["KHR_materials_pbrSpecularGlossiness"]["diffuseFactor"].GetArray();
            auto tex = mtl["pbrMetallicRoughness"]["baseColorTexture"]["index"].GetInt(-1);
            if (tex == -1)
              tex = mtl["extensions"]["KHR_materials_pbrSpecularGlossiness"]["diffuseTexture"]["index"].GetInt(-1);*/
 
          //  Materials.push_back(material
          //  {
          //    .Name = mtl["name"].GetString(),
          //    .TextureNo = tex,
          //    .BaseColorFactor = bcf.size() == 0 ? dvec4(1, 1, 1, 1) : dvec4{bcf[0].GetDouble(), bcf[1].GetDouble(), bcf[2].GetDouble(), bcf[3].GetDouble(1)},
          //  });
          }
          std::cout << std::format("Loaded: '{}' model\n", FileName);
        }
      }
      catch( std::exception &Ex )
      {
        std::cout << "NOT LOADED: " << FileName << " --> " << Ex.what() << "\n";
        Buffers.clear();
        BufferViews.clear();
        Accessors.clear();
        Meshes.clear();
        Nodes.clear();
        Scenes.clear();
        SceneNo = -1;
        Images.clear();
        Samplers.clear();
        Textures.clear();
        //Materials.clear();
      }
    } /* End of 'Load' function */

    /* Open JSON file function.
     * ARGUMENTS:
     *   - Filename:
     *       const std::string &FileName;
     * RETURNS:
     *   (json) Result of opening file.
     */
    json Load( const std::string &FileName )
    {
      std::fstream f(FileName, std::fstream::in | std::fstream::binary);
      if (!f.is_open())
        return json{};

      f.seekg(0, std::fstream::end);
      int TextSize = f.tellg();
      f.seekg(0, std::fstream::beg);
      File.resize(TextSize);
      f.read(File.data(), TextSize);
      f.close();
      return Parse();
    } /* End of 'Load' function */

    /* Convert from Base64 to byte function.
     * ARGUMENTS:
     *   - In source string:
     *       const std::string &InString;
     *   - Data size:
     *       const INT &InDataSize;
     * RETURNS:
     *   (std::vector<BYTE>) converted code.
     */
    std::vector<BYTE> ConvertBase64( const std::string &InString, const INT &InDataSize )
    {
      std::vector<BYTE> &&res = {};
      static const std::string bs("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/");

      res.resize(InDataSize);
      auto inpos = InString.find(";base64,");
      if (inpos == std::string::npos)
        return {};
      inpos += 8;
      SIZE_T outpos = 0;

      BYTE N[4] {};
      DWORD BR;
      INT k = 0;
      auto i = inpos;
      for (; i < InString.length(); i++)
        if (auto pos = bs.find(InString[i]); pos != std::string::npos)
        {
          N[k++] = static_cast<BYTE>(pos);
          if (k == 4)
          {
            k = 0;
            BR = (N[0] << 18) | (N[1] << 12) | (N[2] << 6) | N[3];
            N[0] = N[1] = N[2] = N[3] = 0;
            for (INT p = 0; p < 3; p++)
              if (outpos < InDataSize)
                res[outpos++] = reinterpret_cast<BYTE *>(&BR)[2 - p];
          }
        }

      if (k != 4)
      {
        k = 0;
        BR = (N[0] << 18) | (N[1] << 12) | (N[2] << 6) | N[3];
        N[0] = N[1] = N[2] = N[3] = 0;
        for (INT p = 0; p < 3; p++)
          if (outpos < InDataSize)
            res[outpos++] = reinterpret_cast<BYTE *>(&BR)[2 - p];
      }
      return res;
    } /* End of 'ConvertBase64' function */

    /* Load gltf function.
     * ARGUMENTS:
     *   - GLTF file:
     *       const std::string &FileName;
     * RETURNS: None.
     */
    VOID LoadGLTF( const std::string &FileName )
    {
      json js = loader::Load(FileName);
      json_array InDataBuf = js["buffers"].GetArray();
      std::vector<data_buffer> Bufs;

      for( auto &Buf : InDataBuf)
      {
        std::string Data {};
        std::string Uri = Buf["uri"].GetString("");

        if (std::filesystem::exists(Uri))
        {
          std::fstream f(Uri, std::fstream::in | std::fstream::binary);
          f.seekg(std::fstream::end);
          Data.resize(f.tellg());
          f.seekg(std::fstream::beg);
          f.read(Data.data(), Data.size());
        }
        else
          Data = Uri;

        Bufs.emplace_back(ConvertBase64(Data, Buf["byteLength"].GetInt(-1)));
      }

      InDataBuf = js["bufferViews"].GetArray();
      std::vector<buffer_view> BufView;

      for( auto &view : InDataBuf)
      {
        BufView.emplace_back(buffer_view
          {
            .Buffer = view["buffer"].GetInt(-1),
            .Offset = SIZE_T(view["byteOffset"].GetInt(-1)),
            .Length = SIZE_T(view["byteLength"].GetInt(-1)),
            .Stride = view["byteStride"].GetInt(-1)
          });
      }

      InDataBuf = js["accessors"].GetArray();
      std::vector<accessor> Acc;

      for( auto &Access : InDataBuf)
      {
        Acc.emplace_back(accessor
          {
            .BufferView = Access["bufferView"].GetInt(-1),
            .ByteOffset = SIZE_T(Access["byteOffset"].GetInt(-1)),
            .ComponentType = component_type(Access["componentType"].GetInt(-1)),
            .Type = Access["type"].GetString("") == "SCALAR" ? accessor_type::eSCALAR :
                    Access["type"].GetString("") == "VEC2" ? accessor_type::eVEC2 :
                    Access["type"].GetString("") == "VEC3" ? accessor_type::eVEC3 : 
                    Access["type"].GetString("") == "VEC4" ? accessor_type::eVEC4 : 
                    Access["type"].GetString("") == "MAT2" ? accessor_type::eMAT2 :
                    Access["type"].GetString("") == "MAT3" ? accessor_type::eMAT3 : accessor_type::eSCALAR,
            .Count = SIZE_T(Access["count"].GetInt(-1)),
            .IsNormalized = Access["isNormalized"].GetBool(FALSE),
          });
      }

      InDataBuf = js["meshes"].GetArray();
      std::vector<mesh> meshes;
      std::vector<primitive> prms;

      for(auto &meshy : InDataBuf)
      {
        for (auto &prims : meshy["primitives"].GetArray())
          prms.emplace_back(primitive
            {
              .PositionAccessor = prims["attributes"].GetObj()["POSITION"].GetInt(-1),
              .NormalAccessor = prims["attributes"].GetObj()["NORMAL"].GetInt(-1),
              .TexCoord0Accessor = prims["attributes"].GetObj()["TEXCOORD_0"].GetInt(-1),
              .TexCoord1Accessor = prims["attributes"].GetObj()["TEXCOORD_1"].GetInt(-1),
              .Color0Accessor = prims["color"].GetInt(-1),
              .IndexAccessor = prims["indices"].GetInt(-1),
            });

        meshes.emplace_back(mesh
          {
            .Name = meshy["name"].GetString(""),
            .Prims = prms,
          });
      }

      InDataBuf = js["scenes"].GetArray();
      std::vector<scena> scns;
      std::vector<INT> nds;

      for (auto &scn : InDataBuf)
      {
        for (auto &nd : scn["nodes"].GetArray())
          nds.emplace_back(nd.GetInt(-1));
        scns.emplace_back(scena
          {
            .Name = scn["name"].GetString(""),
            .RootNodes = nds,
          });
      }

      InDataBuf = js["nodes"].GetArray();
      std::vector<node> nodes;
      std::vector<INT> SubNodes;
      std::vector<DBL> Translation, Rotation, Scale, WorldMatrix;

      for(auto &nodec : InDataBuf)
      {
        for (auto &val : nodec["subNodes"].GetArray())
          SubNodes.emplace_back(val.GetInt(-1));
        for (auto &val : nodec["rotation"].GetArray())
          Rotation.emplace_back(val.GetDouble(0));
        for (auto &val : nodec["translation"].GetArray())
          Translation.emplace_back(val.GetDouble(0));
        for (auto &val : nodec["scale"].GetArray())
          Scale.emplace_back(val.GetDouble(0));
        for (auto &val : nodec["worldMatrix"].GetArray())
          WorldMatrix.emplace_back(val.GetDouble(0));

        nodes.emplace_back(node
          {
            .Name = nodec["name"].GetString(""),
            .Mesh = nodec["mesh"].GetInt(-1),
            .Subnodes = SubNodes,
            //.Translation = Translation,
            //.Rotaion = Rotation,
            //.Scale = Scale,
            //.WorldMatrix = WorldMatrix,          
          });
      }       
    } /* End of 'LoadGLTF' function */

    /* Skip empty space in JSON file function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID SkipWhiteSpaces( VOID )
    {
      while (Pos < File.length() && std::isspace(static_cast<UCHAR>(File[Pos])))
        Pos++;
    } /* End of 'SkipWhiteSpaces' function */

    /* Skip comments in JSON file function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID SkipComment( VOID )
    {
      if (Pos + 1 < File.length() && File[Pos] == '/')
        if (File[Pos + 1] == '/')
	  while (Pos < File.length() && File[Pos] != '\n')
	    Pos++;
        else if (File[Pos + 1] == '*')
        {
	  Pos += 2;
	  while (Pos + 1 < File.length() && !(File[Pos] == '*' && File[Pos + 1] == '/'))
	    Pos++;
	  if (Pos + 1 < File.length())
	    Pos += 2;
        }
    } /* End of 'SkipComment' function */

    /* Skip comments and white space in JSON file function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID SkipCommentWhiteSpace( VOID )
    {
      size_t OldPos;

      do
      {
        OldPos = Pos;
        SkipWhiteSpaces();
        SkipComment();
      } while (OldPos != Pos);
    } /* End of 'SkipCommentWhiteSpace' function */

    /* Parse JSON file string function.
     * ARGUMENTS:	None.
     * RETURNS:
     *   (std::string) Parsed string.
     */
    std::string ParseString( VOID )
    {
      std::string res;

      if (File[Pos] != '"')
        throw std::runtime_error("Invalid string parsing");
      Pos++;

      while (Pos < File.length() && File[Pos] != '"')
      {
        if (File[Pos] == '\\')
        {
          Pos++;
          if (Pos >= File.length())
            return "";
          switch (File[Pos])
          {
          case '"':
            res += '"';
            break;
          case '\\':
            res += '\\';
            break;
          case '/':
            res += '/';
            break;
          case 'b':
            res += '\b';
            break;
          case 'f': 
            res += '\f';
            break;
          case 'n': 
            res += '\n';
            break;
          case 'r': 
            res += '\r';
            break;
          case 't': 
            res += '\t';
            break;
          case 'u':
            if (Pos + 4 < File.length())
            {
              std::string hex = File.substr(Pos + 1, 4);
              INT code = std::stoi(hex, nullptr, 16);
              if (code < 0x80)
                res += static_cast<CHAR>(code);
              else if (code < 0x800)
              {
                res += static_cast<CHAR>(0xF0 | (code >> 6));
                res += static_cast<CHAR>(0x80 | (code & 0x3F));
              }
              else if (code < 0x10000)
              {
                res += static_cast<CHAR>(0xE0 | (code >> 12));
                res += static_cast<CHAR>(0x80 | ((code >> 6) & 0x3F));
                res += static_cast<CHAR>(0x80 | (code & 0x3F));
              }
            }
            Pos += 4;
            break;
          }
        }
        else
        {
          res += File[Pos];
        }
        Pos++;
      }
      if (Pos >= File.length() || File[Pos] != '"')
        throw std::runtime_error("String hasn't been parsed entirely");
      Pos++;

      return res;
    } /* End of 'ParseString' function */

    /* Parse JSON file number function.
     * ARGUMENTS:	None.
     * RETURNS:
     *   (json) Parsed number.
     */
    json ParseNumber( VOID )
    {
      size_t start = Pos;
      BOOL IsDouble = FALSE;

      if (File[Pos] == '-')
        Pos++;
      if (File[Pos] == '0')
        Pos++;
      else if (std::isdigit(File[Pos]))
        while (Pos < File.length() && std::isdigit(File[Pos]))
          Pos++;
      else
        throw std::runtime_error("Invalid number parsing");

      //double parsing
      if (Pos < File.length() && File[Pos] == '.')
      {
        IsDouble = TRUE;
        Pos++;
        if (!std::isdigit(File[Pos]))
          throw std::runtime_error("Invalid number parsing");

        while (Pos < File.length() && std::isdigit(File[Pos]))
          Pos++;
      }

      //exponent parsing
      if (Pos < File.length() && (File[Pos] == 'e' || File[Pos] == 'E'))
      {
        IsDouble = TRUE;
        Pos++;
        if (Pos < File.length() && (File[Pos] == '+' || File[Pos] == '-'))
          Pos++;
        if (Pos >= File.length() || !std::isdigit(File[Pos]))
          throw std::runtime_error("Invalid exponent parsing");
        while (Pos < File.length() && std::isdigit(File[Pos]))
          Pos++;
      }

      std::string NumStr = File.substr(start, Pos - start);
      if (IsDouble)
        return std::stod(NumStr);
      else
        return std::stoi(NumStr);

    } /* End of 'ParseNumber' function */

    /* Parse JSON file key word function.
     * ARGUMENTS:	None.
     * RETURNS:
     *   (json) Parsed key word.
     */
    json ParseKeyWord( VOID )
    {
      std::string KeyWord;

      while (Pos < File.length() && std::isalpha(File[Pos]))
      {
        KeyWord += File[Pos];
        Pos++;
      }

      if (KeyWord == "true")
        return TRUE;
      if (KeyWord == "false")
        return FALSE;
      if (KeyWord == "null")
        return nullptr;

      throw std::runtime_error("Invalid parsing of key word");
    } /* End of 'ParseKeyWord' function */

    /* Parse JSON file array function.
     * ARGUMENTS:	None.
     * RETURNS:
     *   (json) Parsed array.
     */
    json ParseArray( VOID )
    {
      json_array arr;

      if (File[Pos] != '[')
        throw std::runtime_error("Invalid array parsing");
      Pos++;

      SkipCommentWhiteSpace();

      if (File[Pos] == ']')
      {
        Pos++;
        return arr;
      }
      while (TRUE)
      {
        arr.push_back(ParseValue());
        SkipCommentWhiteSpace();
        if (File[Pos] == ']')
        {
          Pos++;
          break;
        }
        else if (File[Pos] == ',')
        {
          Pos++;
          SkipCommentWhiteSpace();

          if (File[Pos] == ']')
          {
            Pos++;
            break;
          }
        }
        else
          throw std::runtime_error("Invalid array parsing");
      }

      return arr;
    } /* End of 'ParseArray' function */

    /* Parse JSON file object function.
     * ARGUMENTS:	None.
     * RETURNS:
     *   (json) Parsed object.
     */
    json ParseObject( VOID )
    {
      json_object obj;
      std::string key;

      if (File[Pos] != '{')
        throw std::runtime_error("Invalid object parsing");
      Pos++;

      SkipCommentWhiteSpace();

      if (File[Pos] == '}')
      {
        Pos++;
        return obj;
      }
      while(TRUE)
      {
        SkipCommentWhiteSpace();
        key = ParseString();
        SkipCommentWhiteSpace();

        if (File[Pos] != ':')
          throw std::runtime_error("Invalid object parsing");
        Pos++;
        SkipCommentWhiteSpace();
        json value = ParseValue();
        obj[key] = value;
        SkipCommentWhiteSpace();
        if (File[Pos] == '}')
        {
          Pos++;
          break;
        }
        else if (File[Pos] == ',')
        {
          Pos++;
          SkipCommentWhiteSpace();
          if (File[Pos] == '}')
          {
            Pos++;
            break;
          }
        }
        else
        {
          throw std::runtime_error("Invalid object parsing");
        }
      }
      return obj;
    } /* End of 'ParseObject' function */

    /* Parse values in JSON file function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    json ParseValue( VOID )
    {
      SkipCommentWhiteSpace();

      if (Pos >= File.length())
        throw std::runtime_error("Invalid value parsing");
      switch(File[Pos])
      {
      case '[':
        return ParseArray();
      case '"':
        return ParseString();
      case '{':
        return ParseObject();
      case 't':
      case 'f':
      case 'n':
        return ParseKeyWord();
      case '-':
      case '0':
      case '1':
      case '2':
      case '3':
      case '4':
      case '5':
      case '6':
      case '7':
      case '8':
      case '9':
        return ParseNumber();
      }
      throw std::runtime_error("Error while parsing values");
    } /* End of 'ParseValue' function */
  }; /* End of 'loader' class */
};

#endif /* __gltf_h_ */

/* END OF 'gltf.h' FILE */                                 
