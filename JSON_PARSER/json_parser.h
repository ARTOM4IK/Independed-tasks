/*************************************************************
 * Copyright (C) 2025
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : json_parser.h
 * PURPOSE     : Judjing Son.
 *               Main module.
 * PROGRAMMER  : AA4.
 *               
 * LAST UPDATE : 13.12.2025.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __json_parser_h_
#define __json_parser_h_

#include <cassert>
 
#ifndef WIN32
#define WIN32
#include <commondf.h>
#undef WIN32
#else
#include <commondf.h>
#endif /* WIN32 */
#define BOOL bool
typedef double DBL;
#include <string>
#include <vector>
#include <fstream>
#include <exception>
#include <map> 
#include <wincodec.h>  
#include <functional> 
#include <iostream>
#include <format>
#include <variant>
#include <filesystem>
#include <span>

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
    if (IsInt())
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
      return std::move(json_array{});
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
      return std::move(json_object{});
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
    //if (!IsObject())
    //  return ;
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
struct scene
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
 
  // Transformation
  BOOL IsMatrixUse = FALSE;  // Common matrix usage flag
  //dmatr Matrix = dmatr::Identity();  // Common transformation matrix
 
  //dvec3 Translation = dvec3(0);           // Translation vector
  //dvec4 Rotation = dvec4(0, 0, 0, 1);     // Rotation quaternion
  //dvec3 Scale = dvec3(1);                 // Scale vector (sx, sy, sz)
  //dmatr WorldMatrix = dmatr::Identity();  // World matrix (transformation from root)
}; /* End of 'node' structure */
 
/* Image representation type */
struct image
{
  std::string Name;            // Image name
  std::vector<BYTE> ImageData; // Image data bytes
}; /* End of 'image' structure */
 
/* Sampler representation type */
struct sampler
{
  sampler_filter_type MagFilter, MinFilter; // Magnify and minimize filters
  /* Sampler filter types */
  sampler_address_type AddressS, AddressT; // Sampler addressing types (by S and T)
}; /* End of 'sampler' structure */
 
/* Texture representation type */
struct texture
{
  std::string Name;  // Texture name
  INT ImageNo;       // Image number
  INT SamplerNo;     // Sampler number
}; /* End of 'texture' structure */

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
  std::vector<scene> Scenes;
  std::vector<sampler> Samplers;
  std::vector<texture> Textures;
  //std::vector<material> Materials;
  std::vector<image> Images;
  INT SceneNo;
  std::map<std::string, accessor_type> AccessorTypes;

  loader( VOID ) : Pos(0), SceneNo(0)
  {
    AccessorTypes["SCALAR"] = accessor_type::eSCALAR;
    AccessorTypes["VEC2"] = accessor_type::eVEC2;
    AccessorTypes["VEC3"] = accessor_type::eVEC3;
    AccessorTypes["VEC4"] = accessor_type::eVEC4;
    AccessorTypes["MAT2"] = accessor_type::eMAT2;
    AccessorTypes["MAT3"] = accessor_type::eMAT3;
    AccessorTypes["MAT4"] = accessor_type::eMAT4;
  }

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
      std::vector<type> &&res {};
      if (AccessorIndex == -1)
        return res;
      accessor &ac = Accessors[AccessorIndex];
      if (AccessorTypesCount[ac.Type] * std::get<0>(ComponentTypes[ac.ComponentType]) != sizeof(type))
        return res;
      buffer_view &bv = BufferViews[ac.BufferView];
      INT stride = bv.Stride;
      if (stride == 0)
        stride = AccessorTypesCount[ac.Type] * std::get<0>(ComponentTypes[ac.ComponentType]);
      std::span<BYTE> bv_data(&Buffers[bv.Buffer].Data[bv.Offset], bv.Length);
      std::span<BYTE> ac_data(&bv_data[ac.ByteOffset], ac.Count * stride);
      res.resize(ac.Count);
      if (bv.Stride == 0)
        CopyMemory(reinterpret_cast<VOID *>(&res[0]), reinterpret_cast<VOID *>(&ac_data[0]), ac.Count * sizeof(type));
      else
        for (INT i = 0; i < ac.Count; i++)
          CopyMemory(reinterpret_cast<VOID *>(&res[i]), reinterpret_cast<VOID *>(&ac_data[stride * i]), sizeof(type));
      return res;
    } /* End of 'GetAccessorData' function */

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
 
          //// Read nodes
          //for (auto &nd : Model["nodes"].GetArray())
          //{
          //  std::vector<INT> SubnodeIndexes;
          //  for (auto &chld : nd["children"].GetArray())
          //    SubnodeIndexes.push_back(chld.GetInt(-1));
          //  std::vector<DBL> Matrix;
          //  for (auto &mte : nd["matrix"].GetArray())
          //    Matrix.push_back(mte.GetDouble());
          //  //std::for_each()
          //  auto rot = nd["rotation"].GetArray();
          //  auto scl = nd["scale"].GetArray();
          //  auto tra = nd["translation"].GetArray();
          //  Nodes.push_back(node
          //  {
          //    .Name = nd["name"].GetString(),
          //    .Mesh = nd["mesh"].GetInt(-1),
          //    .Subnodes = std::move(SubnodeIndexes),
          //    .IsMatrixUse = Matrix.size() != 0,
          //    .Matrix = Matrix.size() != 0 ? dmatr(reinterpret_cast<DBL (*)[4]>(Matrix.data())) : dmatr::Identity(),
          //    .Translation = tra.size() == 0 ? dvec3(0) : dvec3{tra[0].GetDouble(), tra[1].GetDouble(), tra[2].GetDouble()},
          //    //.Rotation = rot.size() == 0 ? dvec4(0, 0, 0, 1) : dvec4{rot[1].GetDouble(), rot[2].GetDouble(), rot[3].GetDouble(), rot[0].GetDouble(1)},
          //    .Rotation = rot.size() == 0 ? dvec4(0, 0, 0, 1) : dvec4{rot[0].GetDouble(1), rot[1].GetDouble(), rot[2].GetDouble(), rot[3].GetDouble()},
          //    .Scale = scl.size() == 0 ? dvec3(1) : dvec3{scl[0].GetDouble(), scl[1].GetDouble(), scl[2].GetDouble()},
          //  });
          //  if (!Nodes.back().IsMatrixUse)
          //    Nodes.back().Matrix =
          //      dmatr::Scale(Nodes.back().Scale) *
          //      dmatr::RotateQuat(Nodes.back().Rotation) *
          //      dmatr::Translate(Nodes.back().Translation);
          //}
 
          //// Read scenes
          //for (auto &sc : Model["scenes"].GetArray())
          //{
          //  std::vector<INT> NodeIndexes;
          //  for (auto &nd : sc["nodes"].GetArray())
          //    NodeIndexes.push_back(nd.GetInt(-1));
          //  Scenes.push_back(scene
          //  {
          //    .Name = sc["name"].GetString(),
          //    .RootNodes = std::move(NodeIndexes),
          //  });
          //}
          //SceneNo = Model["scene"].GetInt(-1);
          //if (SceneNo == -1 && Scenes.size() > 0)
          //  SceneNo = 0;
 
          //std::function<VOID( INT, const dmatr & )> ComputeWorldMatrix =
          //  [this, &ComputeWorldMatrix]( INT NodeIndex, const dmatr &ParentWorld )
          //  {
          //    const node &nd = Nodes[NodeIndex];
          //    dmatr world = nd.Matrix * ParentWorld;
          //    Nodes[NodeIndex].WorldMatrix = world;
          //    for (INT subnode : nd.Subnodes)
          //      ComputeWorldMatrix(subnode, world);
          //  };
          //for (auto &sc : Scenes)
          //  for (auto &rootnd : sc.RootNodes)
          //    ComputeWorldMatrix(rootnd, dmatr::Identity());
 
          // Read images
          for (auto &img : Model["images"].GetArray())
          {
            //      "uri": "textures/08___Default_baseColor.jpeg"
            //========================
            //      "mimeType": "image/png",
            //      "uri": "data:image/png;base64,iVBORw0KGgoAAAANSUhE...=="
            std::string Name {};
            const std::string uri = img["uri"].GetString();
            const std::string mime = img["mimeType"].GetString();
            INT bv_no = img["bufferView"].GetInt(-1);
            const std::string name = img["name"].GetString();
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
              Name = "File: " + uri;
              // vivk::image img(filebuf);
            }
            else if (/*mime.find("image/") != std::string::npos && */uri.find(";base64,") != std::string::npos)
            {
              // Decode image from string
              // vivk::image img(DecodeBase64(uri, -1));
              Name = "From string encoding uri Base64";
              data = ConvertBase64(uri, -1);
            }
            else if (bv_no != -1)
            {
              buffer_view &bv = BufferViews[bv_no];
              std::span<BYTE> bv_data(&Buffers[bv.Buffer].Data[bv.Offset], bv.Length);
              data.resize(bv.Length);
              memcpy(reinterpret_cast<VOID *>(&data[0]), reinterpret_cast<VOID *>(&bv_data[0]), bv.Length);
              Name = "From buffer:" + Name;
            }
            else
              throw std::runtime_error("Image data is not found/load");
            Images.emplace_back(image
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
            Textures.push_back(texture
            {
              .Name = tex["name"].GetString(),
              .ImageNo = tex["source"].GetInt(-1),
              .SamplerNo = tex["sampler"].GetInt(-1),
            });
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
    std::vector<scene> scns;
    std::vector<INT> nds;

    for (auto &scn : InDataBuf)
    {
      for (auto &nd : scn["nodes"].GetArray())
        nds.emplace_back(nd.GetInt(-1));
      scns.emplace_back(scene
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
  } /* End of 'LoadBuffer' function */

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
    if (Pos < File.length() && File[Pos] == 'e' || File[Pos] == 'E')
    {
      IsDouble = TRUE;
      Pos++;
      if (File[Pos] == '+' || File[Pos] == '-')
        Pos++;
      if (!std::isdigit(File[Pos]))
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

#endif /* __json_parser_h_ */

/* END OF 'json_parser.h' FILE */                                 
