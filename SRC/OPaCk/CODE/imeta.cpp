/*

Software written by TheOnionRingToRuleThemAll, formerly known as Adolif2, or DumdogsWorld.

No copy-and-paste license here. I like the internet to be like the wild west, which is a memory of days long gone.

Just give me credit, damn it.

*/

//===================================================================================



#include "main.hpp"


void opakImeta::Deserialize(opakFileMode_t mode)
{
	if (mode == opakFileModeIpak)
	{
#ifdef DEV_TOOLS
		fread(&entryCount1, 4, 1, handle);
#else
		return;
#endif
	}
	else
	{
		entryCount1 = imetaEntryCount;
	}

	fread(&header, 1, 8, handle);

	entryCount1 = (opakUInt32)header;

	if (!entryCount1)
	{
		printf("\n\n"
			"=========\n"
			"EntryCount was zero? This ain't right..."
			"\n=========\n"
			"Program will abort.\n\n");
		CleanUpCollectedFiles();
		exit(2);
	}

	entries = new ipakEntry_t [entryCount1];
	for (unsigned int i = 0; i < entryCount1; i++)
	{
		fread(&entries[i], 1, ipakEntrySize, handle);
	}
}

void opakImeta::Serialize(void)
{
}

void opakImeta::Serialize(opakIpak * ipak1, opakImeta * imeta2)
{
	unsigned int i = 0;
	ipakEntry_t nullEntry;
	
	if (numCollectedFiles > imetaEntryCount)
	{
		ErrorMessage("numCollectedFiles > imetaEntryCount");
	}
	if (!collectedFiles)
	{
		ErrorMessage("collectedFiles was null...");
	}
	if (!imeta2)
	{
		ErrorMessage("imeta2 was null...");
	}

	header = numCollectedFiles;

	memset(&nullEntry, 0, ipakEntrySize);

	fwrite(&header, 1, 8, handle);

	for (i = 0; i < numCollectedFiles; i++)
	{
		if (collectedFiles[i]->IsRawEntry())
		{
			opakUInt64 offsetBak = 0;

			if (!collectedFiles[i]->metaEntry.offset)
			{
				continue;
			}
			fwrite(&collectedFiles[i]->metaEntry, 1, ipakEntrySize, handle);
		}
		else
		{
			if (!collectedFiles[i]->metaEntry.offset)
			{
				ipak1->AppendTexture(collectedFiles[i]);
			}
			fwrite(&collectedFiles[i]->metaEntry, 1, ipakEntrySize, handle);
		}
	}

	for (; i < imetaEntryCount; i++)
	{
		fwrite(&nullEntry, 1, ipakEntrySize, handle);
	}
}

opakImeta::opakImeta(const char * srcFolderName, const char * fileName, opakFileMode_t mode, bool createNew) : opakFile(srcFolderName, fileName, mode, createNew)
{
	entries = opakNull;
	entryCount1 = 0;

	if (createNew)
	{
		entries = new ipakEntry_t[imetaEntryCount];
		entryCount1 = imetaEntryCount;
	}
	if ((mode != opakFileModeIpak) && (!createNew))
	{
		Deserialize(mode);
	}
}

opakImeta::opakImeta(const char * srcFolderName, const char * destFolderName, const char * fileName, opakFileMode_t mode) : opakFile(srcFolderName, destFolderName, fileName, mode)
{
	entries = opakNull;
	entryCount1 = 0;

	if (mode != opakFileModeIpak)
	{
		Deserialize(mode);
	}
}

opakImeta::~opakImeta()
{
	if (entries)
	{
		delete[] entries;
		entries = opakNull;
	}
}