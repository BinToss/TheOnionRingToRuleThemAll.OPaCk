/*

Software written by TheOnionRingToRuleThemAll, formerly known as Adolif2, or DumdogsWorld.

No copy-and-paste license here. I like the internet to be like the wild west, which is a memory of days long gone.

Just give me credit, damn it.

*/

//===================================================================================



#include "main.hpp"


void opakIpak::Serialize(void)
{
}

void opakIpak::Pad(opakUInt64 greaterSize)
{
	OpakFseek(handle, greaterSize, SEEK_SET);
}

void opakIpak::PosPad(void)
{
	opakUInt64 pos = 0;

	pos = PosTell();

	pos -= (pos % 8);
	pos += 8;

	OpakFseek(handle, pos, SEEK_SET);
}

opakUInt64 opakIpak::PosTell(void)
{
	return OpakFtell(handle);
}

void opakIpak::AppendTexture(ddsFile * tex)
{
	ipakBitmapHeader_t header;
	unsigned char footer[6] = { 0x1, 0x0, 0xFF, 0xFF, 0xFF, 0xFF };

	if (tex->metaEntry.offset)
	{
		return;
	}

	memcpy(&header, hce_sample_tcip_header, ipakBitmapHeaderSize);

	header.width = tex->width;
	header.height = tex->height;
	if (!tex->noMipMaps)
	{
		header.mipmapCount = tex->mipmapCount + 1;
	}
	else
	{
		header.mipmapCount = 1;
	}
	header.format = tex->pixFmt;

	PosPad();
	tex->metaEntry.offset = PosTell();

	fwrite(&header, 1, ipakBitmapHeaderSize, handle);
	fwrite(tex->dxtData, 1, tex->dxtDataSize, handle);
	fwrite(footer, 1, 6, handle);
}

opakIpak::opakIpak(const char * srcFolderName, const char * destFolderName, const char * fileName, opakFileMode_t mode) : opakImeta(srcFolderName, destFolderName, fileName, mode)
{
	OpakFseek(handle, 0, SEEK_END);
	originalSize = OpakFtell(handle);
}

opakIpak::~opakIpak()
{
}