/*

Software written by TheOnionRingToRuleThemAll, formerly known as Adolif2, or DumdogsWorld.

No copy-and-paste license here. I like the internet to be like the wild west, which is a memory of days long gone.

Just give me credit, damn it.

*/

//===================================================================================



#include "main.hpp"


#ifndef DDSFILE_INCLUDE_ONCE
#define DDSFILE_INCLUDE_ONCE

class ddsFile : public opakFile
{
public:
	BitmapPixelFormat_t pixFmt;
	ipakBitmapHeader_t header;
	ipakEntry_t metaEntry;
	unsigned char * dxtData;
	opakInt64 dxtDataSize;
	int width;
	int height;
	int mipmapCount;
	opakUInt64 avgColor[4];
	bool noMipMaps;

	virtual void Deserialize(opakFileMode_t mode);
	virtual void Serialize(void);
	virtual bool IsRawEntry(void);
	void FillMetaEntry(void);
	unsigned int CalculateCompressedSize(int width, int height);
	void ConvertTo32Bit(void);
	void SwapColorChannels(int width, int height, unsigned char * data, int pass);
	void Decompress(void);
	ddsFile(const ipakEntry_t * data);
	ddsFile(const char * path, bool raw);
	~ddsFile();
};

#endif