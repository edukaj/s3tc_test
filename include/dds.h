#if 0
#ifndef __D3_DDS_H
#define __D3_DDS_H

#include <cstdint>

//
// Structures from Direct3D 9
//
struct D3D_PixelFormat // DDPIXELFORMAT
{
    int dwSize;
    int dwFlags;
    int dwFourCC;
    int dwRGBBitCount;
    int dwRBitMask, dwGBitMask, dwBBitMask;
    int dwRGBAlphaBitMask;
};

struct D3D_Caps2
{
    int dwCaps1;
    int dwCaps2;
    int Reserved[2];
};

struct D3D_SurfaceDesc2
{
    int dwSize;
    int dwFlags;
    int dwHeight;
    int dwWidth;
    int dwPitchOrLinearSize;
    int dwDepth;
    int dwMipMapCount;
    int dwReserved1[11];
    D3D_PixelFormat ddpfPixelFormat;
    D3D_Caps2 ddsCaps;
    int dwReserved2;
};

// Enums

#define FOURCC(a, b, c, d) \
    ((unsigned int)((unsigned int)(a) ) | \
    ((unsigned int)(b) << 8) | \
    ((unsigned int)(c) << 16) | \
    ((unsigned int)(d) << 24))

template<typename Integer>
Integer FourCC(Integer a, Integer b, Integer c, Integer d)
{
    return  ((Integer)
                ((Integer)(a) ) | \
                ((Integer)(b) << 8) | \
                ((Integer)(c) << 16) | \
                ((Integer)(d) << 24));
}

enum DDS_COMPRESSION_TYPE
{
    DDS_COMPRESS_NONE = 0,
    DDS_COMPRESS_BC1, /* DXT1 */
    DDS_COMPRESS_BC2, /* DXT3 */
    DDS_COMPRESS_BC3, /* DXT5 */
    DDS_COMPRESS_BC3N, /* DXT5n */
    DDS_COMPRESS_BC4, /* ATI1 */
    DDS_COMPRESS_BC5, /* ATI2 */
    DDS_COMPRESS_AEXP, /* DXT5 */
    DDS_COMPRESS_YCOCG, /* DXT5 */
    DDS_COMPRESS_YCOCGS, /* DXT5 */
    DDS_COMPRESS_MAX
};

enum DDS_SAVE_TYPE
{
    DDS_SAVE_SELECTED_LAYER = 0,
    DDS_SAVE_CUBEMAP,
    DDS_SAVE_VOLUMEMAP,
    DDS_SAVE_MAX
};

enum DDS_FORMAT_TYPE
{
    DDS_FORMAT_DEFAULT = 0,
    DDS_FORMAT_RGB8,
    DDS_FORMAT_RGBA8,
    DDS_FORMAT_BGR8,
    DDS_FORMAT_ABGR8,
    DDS_FORMAT_R5G6B5,
    DDS_FORMAT_RGBA4,
    DDS_FORMAT_RGB5A1,
    DDS_FORMAT_RGB10A2,
    DDS_FORMAT_R3G3B2,
    DDS_FORMAT_A8,
    DDS_FORMAT_L8,
    DDS_FORMAT_L8A8,
    DDS_FORMAT_AEXP,
    DDS_FORMAT_YCOCG,
    DDS_FORMAT_MAX
};

enum DDS_COLOR_TYPE
{
    DDS_COLOR_DEFAULT = 0,
    DDS_COLOR_DISTANCE,
    DDS_COLOR_LUMINANCE,
    DDS_COLOR_INSET_BBOX,
    DDS_COLOR_MAX
};

enum DDS_MIPMAP_TYPE
{
    DDS_MIPMAP_DEFAULT = 0,
    DDS_MIPMAP_NEAREST,
    DDS_MIPMAP_BOX,
    DDS_MIPMAP_BILINEAR,
    DDS_MIPMAP_BICUBIC,
    DDS_MIPMAP_LANCZOS,
    DDS_MIPMAP_MAX
};

const uint32_t DDS_HEADERSIZE               = 128;

const uint32_t DDSD_CAPS                    = 0x00000001;
const uint32_t DDSD_HEIGHT                  = 0x00000002;
const uint32_t DDSD_WIDTH                   = 0x00000004;
const uint32_t DDSD_PITCH                   = 0x00000008;
const uint32_t DDSD_PIXELFORMAT             = 0x00001000;
const uint32_t DDSD_MIPMAPCOUNT             = 0x00020000;
const uint32_t DDSD_LINEARSIZE              = 0x00080000;
const uint32_t DDSD_DEPTH                   = 0x00800000;

const uint32_t DDPF_ALPHAPIXELS             = 0x00000001;
const uint32_t DDPF_ALPHA                   = 0x00000002;
const uint32_t DDPF_FOURCC                  = 0x00000004;
const uint32_t DDPF_PALETTEINDEXED8         = 0x00000020;
const uint32_t DDPF_RGB                     = 0x00000040;
const uint32_t DDPF_LUMINANCE               = 0x00020000;

const uint32_t DDSCAPS_COMPLEX              = 0x00000008;
const uint32_t DDSCAPS_TEXTURE              = 0x00001000;
const uint32_t DDSCAPS_MIPMAP               = 0x00400000;

const uint32_t DDSCAPS2_CUBEMAP             = 0x00000200;
const uint32_t DDSCAPS2_CUBEMAP_POSITIVEX   = 0x00000400;
const uint32_t DDSCAPS2_CUBEMAP_NEGATIVEX   = 0x00000800;
const uint32_t DDSCAPS2_CUBEMAP_POSITIVEY   = 0x00001000;
const uint32_t DDSCAPS2_CUBEMAP_NEGATIVEY   = 0x00002000;
const uint32_t DDSCAPS2_CUBEMAP_POSITIVEZ   = 0x00004000;
const uint32_t DDSCAPS2_CUBEMAP_NEGATIVEZ   = 0x00008000;
const uint32_t DDSCAPS2_VOLUME              = 0x00200000;

class DDDS
// A cross-platform DDS loader
{
    enum Max
    {
        MAX_MIPMAP_LEVEL=16 // For 65536x65536 images (2^16)
    };

    unsigned char *pixels[MAX_MIPMAP_LEVEL]; // Texture data
    int bytes[MAX_MIPMAP_LEVEL];

    // Info extracted from file
    int wid,hgt;
    int mipmapLevels;
    int format;
    int internalFormat;
    int compressionType;
    int blockSize; // Used in passing compressed textures to OpenGL

public:
    DDDS();
    ~DDDS();

    int GetWidth(){ return wid; }
    int GetHeight(){ return hgt; }
    int GetMipMapLevels(){ return mipmapLevels; }

    bool Load(cstring fname);

    DTexture *CreateTexture();
};

#endif
#endif
