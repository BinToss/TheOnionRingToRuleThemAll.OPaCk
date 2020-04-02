/*

Software written by TheOnionRingToRuleThemAll, formerly known as Adolif2, or DumdogsWorld.

No copy-and-paste license here. I like the internet to be like the wild west, which is a memory of days long gone.

Just give me credit, damn it.

*/

//===================================================================================



#include "main.hpp"


void rawFile::Deserialize(opakFileMode_t mode)
{
	if (handle)
	{
		fread(&metaEntry, 1, sizeof(ipakEntry_t), handle);
		fclose(handle);
		handle = opakNull;
	}
}

bool rawFile::IsRawEntry(void)
{
	return true;
}

void rawFile::Serialize(void)
{
}

rawFile::rawFile(const ipakEntry_t * data) : ddsFile(data)
{
	Deserialize(opakFileModeOther);
}

rawFile::rawFile(const char * path) : ddsFile(path, true)
{
	Deserialize(opakFileModeOther);
}

rawFile::~rawFile()
{
}