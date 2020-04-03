/*

Software written by TheOnionRingToRuleThemAll, formerly known as Adolif2, or DumdogsWorld.

No copy-and-paste license here. I like the internet to be like the wild west, which is a memory of days long gone.

Just give me credit, damn it.

*/

//===================================================================================



#ifndef DEFINITIONS_INCLUDE_ONCE
#define DEFINITIONS_INCLUDE_ONCE

extern const opakUInt32 DDS_MAGIC;

extern const opakUInt32 DXT1;
extern const opakUInt32 DXT2;
extern const opakUInt32 DXT3;
extern const opakUInt32 DXT4;
extern const opakUInt32 DXT5;

typedef struct {
	opakUInt32 dwSize;
	opakUInt32 dwFlags;
	opakUInt32 dwFourCC;
	opakUInt32 dwRGBBitCount;
	opakUInt32 dwRBitMask;
	opakUInt32 dwGBitMask;
	opakUInt32 dwBBitMask;
	opakUInt32 dwABitMask;
} cDDS_PIXELFORMAT_t;

typedef struct {
	opakUInt32           dwMagic;
	opakUInt32           dwSize;
	opakUInt32           dwFlags;
	opakUInt32           dwHeight;
	opakUInt32           dwWidth;
	opakUInt32           dwPitchOrLinearSize;
	opakUInt32           dwDepth;
	opakUInt32           dwMipMapCount;
	opakUInt32           dwReserved1[11];
	cDDS_PIXELFORMAT_t   ddspf;
	opakUInt32           dwCaps;
	opakUInt32           dwCaps2;
	opakUInt32           dwCaps3;
	opakUInt32           dwCaps4;
	opakUInt32           dwReserved2;
} cDDS_HEADER_t;

typedef enum
{
	uncompressed = 0,
	unsupported1 = 1,
	dxt1 = 0xD,
	unsupported2 = 0xE,
	dxt3 = 0xF,
	unsupported3 = 0x10,
	dxt5 = 0x11
} BitmapPixelFormat_t;

const unsigned int shortenedNameSize = 0x100;

extern const unsigned int shortenedNameMaxPrefixSize;

typedef struct
{
	char name[shortenedNameSize];
	
	opakByte unk1[0xC];
	opakUInt32 width;
	opakUInt32 height;
	opakUInt32 unk2;
	opakUInt32 mipmapCount;
	opakUInt32 faceCount;	
	opakByte unk3[12];
	opakUInt32 size1;
	opakUInt32 unk4;
	opakUInt32 size2;
	opakUInt64 offset;
	opakUInt32 size3;
	opakUInt32 unk5;
} ipakEntry_t;

const unsigned int ipakEntrySize = 328;

typedef struct
{
	opakByte TCIPcrap[16];
	opakUInt32 width;
	opakUInt32 height;
	opakUInt32 depth;
	opakUInt32 unk1;
	opakByte unk2[6];
	opakUInt16 format;
	opakByte unk3[8];
	opakUInt32 mipmapCount;
	opakByte unk4[6];
} ipakBitmapHeader_t;

const unsigned int ipakBitmapHeaderSize = 0x3A;

extern const unsigned int imetaEntryCount;

typedef enum
{
	opakFileModeImeta = 0,
	opakFileModeIpak = 1,
	opakFileModeOther = 2
} opakFileMode_t;

enum opakFileSubClass_t
{
	opakPlainFile = 0,
	opakRawTexture = 1,
	opakDDSTexture = 2,
	opakBitmapTag = 3
};

#endif