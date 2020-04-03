/*

Software written by TheOnionRingToRuleThemAll, formerly known as Adolif2, or DumdogsWorld.

No copy-and-paste license here. I like the internet to be like the wild west, which is a memory of days long gone.

Just give me credit, damn it.

*/

//===================================================================================



#include "main.hpp"


void ddsFile::Deserialize(opakFileMode_t mode)
{
	opakInt64 fileSize = 0;
	cDDS_HEADER_t ddsHeader;
	bool is16Bit = false;

	memset(&ddsHeader, 0, sizeof(cDDS_HEADER_t));

	OpakFseek(handle, 0, SEEK_END);

	fileSize = OpakFtell(handle);

	if (fileSize <= sizeof(cDDS_HEADER_t))
	{
		ErrorMessage("DDS file stream too small to be valid DDS file.");
	}

	fileSize -= sizeof(cDDS_HEADER_t);

	OpakFseek(handle, 0, SEEK_SET);

	fread(&ddsHeader, 1, sizeof(cDDS_HEADER_t), handle);

	if (ddsHeader.dwMagic != DDS_MAGIC)
	{
		ErrorMessage("DDS file contains invalid magic number. Is it really a DDS?");
	}

	if ((ddsHeader.ddspf.dwFlags & 1) && (ddsHeader.ddspf.dwFlags & 0x40))
	{
		pixFmt = uncompressed;
	}
	else if ((ddsHeader.ddspf.dwFlags & 0x40) && 
		(ddsHeader.ddspf.dwRBitMask == 0xF800) && 
		(ddsHeader.ddspf.dwGBitMask == 0x7E0) && 
		(ddsHeader.ddspf.dwBBitMask == 0x1F) &&
		(ddsHeader.ddspf.dwABitMask == 0) &&
		(ddsHeader.ddspf.dwRGBBitCount == 16))
	{
		pixFmt = uncompressed;
		is16Bit = true;
	}
	else
	{
		if ((ddsHeader.ddspf.dwFourCC != DXT1) &&
			(ddsHeader.ddspf.dwFourCC != DXT3) &&
			(ddsHeader.ddspf.dwFourCC != DXT5))
		{
			ErrorMessage("One of your DDS uses currently unsupported compression format. Right now, only DXT1, DXT3, DXT5, A8R8G8B8 and unmipmapped R5G6B5 are supported.");
		}
		if (ddsHeader.ddspf.dwFourCC == DXT1)
		{
			pixFmt = dxt1;
		}
		else if (ddsHeader.ddspf.dwFourCC == DXT3)
		{
			pixFmt = dxt3;
		}
		else
		{
			pixFmt = dxt5;
		}
	}

	dxtData = new unsigned char[fileSize];

	fread(dxtData, 1, fileSize, handle);
	dxtDataSize = fileSize;

	fclose(handle);
	handle = opakNull;

	width = ddsHeader.dwWidth;
	height = ddsHeader.dwHeight;

	if (ddsHeader.dwCaps & 0x400000)
	{
		mipmapCount = ddsHeader.dwMipMapCount;
		if (mipmapCount == 0)
		{
			noMipMaps = true;
			mipmapCount = 1;
		}
		else if(is16Bit)
		{			
			ErrorMessage("Mipmapped R5G6B5 textures are currently not supported.");
		}
	}
	else
	{
		noMipMaps = true;
		mipmapCount = 1;
	}

	if (is16Bit)
	{
		ConvertTo32Bit();
	}

	FillMetaEntry();
}

bool ddsFile::IsRawEntry(void)
{
	return false;
}

void ddsFile::FillMetaEntry(void)
{
	memcpy(&metaEntry, hce_sample_entry, ipakEntrySize);
	memset(metaEntry.name, 0, shortenedNameSize);
	memcpy(metaEntry.name, shortenedName, shortenedNameSize);

	if (!IsRawEntry())
	{
		metaEntry.offset = 0;
		Decompress();
		metaEntry.width = (opakUInt32)width;
		metaEntry.height = (opakUInt32)height;
		metaEntry.size1 = (opakUInt32)dxtDataSize;
		metaEntry.size2 = (opakUInt32)dxtDataSize;
		metaEntry.size3 = (opakUInt32)dxtDataSize;
		if (!noMipMaps)
		{
			metaEntry.mipmapCount = mipmapCount + 1;
		}
		else
		{
			metaEntry.mipmapCount = 1;
		}
	}
}

unsigned int ddsFile::CalculateCompressedSize(int width, int height)
{
	if (pixFmt == dxt1)
	{
		return ((width + 3) / 4) * ((height + 3) / 4) * 8;
	}
	return ((width + 3) / 4) * ((height + 3) / 4) * 16;
}

void ddsFile::ConvertTo32Bit(void)
{
	int N = 0;

	double R = 0.0;
	double G = 0.0;
	double B = 0.0;

	double maxRed = 31.0;
	double maxGreen = 63.0;
	double maxBlue = 31.0;


	unsigned char R8 = 0;
	unsigned char G8 = 0;
	unsigned char B8 = 0;

	opakUInt16 pixel16;
	opakUInt16 * data16 = opakNull;
	opakUInt32 pixel32;
	opakUInt32 * data32 = opakNull;

	N = width * height;

	data16 = (opakUInt16 *)dxtData;
	data32 = new opakUInt32[N];

	for (int i = 0; i < N; i++)
	{
		pixel16 = data16[i];

		R = (double)((pixel16 & 0xF800) >> 11);
		G = (double)((pixel16 & 0x7E0) >> 5);
		B = (double)(pixel16 & 0x1F);

		R /= maxRed;
		G /= maxGreen;
		B /= maxBlue;

		R *= 255.0;
		G *= 255.0;
		B *= 255.0;

		R8 = (unsigned char)R;
		G8 = (unsigned char)G;
		B8 = (unsigned char)B;

		pixel32 = 0xFF000000;

		pixel32 |= R8 << 16;
		pixel32 |= G8 << 8;
		pixel32 |= B8;

		data32[i] = pixel32;
	}

	delete dxtData;
	dxtData = (unsigned char *)data32;
	dxtDataSize = N * 4;
}

void ddsFile::SwapColorChannels(int width, int height, unsigned char * data, int pass)
{
	unsigned char t = 0;
	int N = 0;

	N = width * height;

	if (pass == 0)
	{
		avgColor[0] = 0;
		avgColor[1] = 0;
		avgColor[2] = 0;
		avgColor[3] = 0;
	}

	for (int i = 0; i < N * 4; i+=4)
	{
		unsigned char * tdata = &data[i];

		t = tdata[2];
		tdata[2] = tdata[0];
		tdata[0] = t;

		if (pass == 0)
		{
			avgColor[0] += tdata[0];
			avgColor[1] += tdata[1];
			avgColor[2] += tdata[2];
			avgColor[3] += tdata[3];
		}
	}

	if (pass == 0)
	{
		avgColor[0] /= N;
		avgColor[1] /= N;
		avgColor[2] /= N;
		avgColor[3] /= N;
	}
}

void ddsFile::Decompress(void)
{
	int w = 0;
	int h = 0;
	unsigned int * umipOffsets = opakNull;
	unsigned int * cmipOffsets = opakNull;
	unsigned int totalCSize = 0;

	unsigned int totalUSize = 0;
	unsigned char * uData = opakNull;

	if ((pixFmt == uncompressed) && noMipMaps)
	{
		return;
	}

	umipOffsets = new unsigned int[mipmapCount];

	if (pixFmt != uncompressed)
	{
		cmipOffsets = new unsigned int[mipmapCount];
	}

	w = width;
	h = height;
	for (int i = 0; i < mipmapCount; i++)
	{
		umipOffsets[i] = totalUSize;
		totalUSize += w * h * 4;
		if (pixFmt != uncompressed)
		{
			cmipOffsets[i] = totalCSize;
			totalCSize += CalculateCompressedSize(w, h);
		}
		if ((w == 1) || (h == 1))
		{
			break;
		}
		w /= 2;
		h /= 2;
	}

	if (width == height)
	{
		totalUSize += 4;
	}

	uData = new unsigned char [totalUSize];
	memset(uData, 0, totalUSize);

	w = width;
	h = height;
	for (int i = 0; i < mipmapCount; i++)
	{
		if (pixFmt != uncompressed)
		{
			DecompressDxt(&uData[umipOffsets[i]], &dxtData[cmipOffsets[i]], w, h, pixFmt);
		}
		else
		{
			memcpy(&uData[umipOffsets[i]], &dxtData[umipOffsets[i]], w * h * 4);
		}
		SwapColorChannels(w, h, &uData[umipOffsets[i]], i);
		if ((w == 1) || (h == 1))
		{
			break;
		}
		w /= 2;
		h /= 2;
	}

	delete[] umipOffsets;
	delete[] cmipOffsets;

	delete[] dxtData;
	dxtData = uData;

	if (width == height)
	{
		dxtData[totalUSize - 4] = (unsigned char)avgColor[0];
		dxtData[totalUSize - 3] = (unsigned char)avgColor[1];
		dxtData[totalUSize - 2] = (unsigned char)avgColor[2];
		dxtData[totalUSize - 1] = (unsigned char)avgColor[3];
	}

	pixFmt = uncompressed;
	dxtDataSize = totalUSize;
}

void ddsFile::Serialize(void)
{
}

ddsFile::ddsFile(const char * path, bool raw) : opakFile(path)
{
	pixFmt = unsupported1;

	width = 0;
	height = 0;
	dxtDataSize = 0;
	mipmapCount = 1;

	avgColor[0] = 0;
	avgColor[1] = 0;
	avgColor[2] = 0;
	avgColor[3] = 0;

	noMipMaps = false;

	memset(&metaEntry, 0, sizeof(ipakEntry_t));
	memset(&header, 0, sizeof(ipakBitmapHeader_t));
	dxtData = opakNull;

	shortenedName = new char [shortenedNameSize + 1];

	memset(shortenedName, 0, shortenedNameSize + 1);

	ShortenName(path, shortenedName, shortenedNameSize);

	if (!raw)
	{
		Deserialize(opakFileModeOther);
	}
}

ddsFile::ddsFile(const ipakEntry_t * data) : opakFile(data)
{
	pixFmt = unsupported1;

	avgColor[0] = 0;
	avgColor[1] = 0;
	avgColor[2] = 0;
	avgColor[3] = 0;

	width = 0;
	height = 0;
	dxtDataSize = 0;
	mipmapCount = 1;

	noMipMaps = false;

	shortenedName = new char[shortenedNameSize + 1];
	memcpy(shortenedName, data->name, shortenedNameSize);

	memcpy(&metaEntry, data, sizeof(ipakEntry_t));
}

ddsFile::~ddsFile()
{
	if (dxtData)
	{
		delete[] dxtData;
		dxtData = opakNull;
	}
}