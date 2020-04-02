/*

Software written by TheOnionRingToRuleThemAll, formerly known as Adolif2, or DumdogsWorld.

No copy-and-paste license here. I like the internet to be like the wild west, which is a memory of days long gone.

Just give me credit, damn it.

*/

//===================================================================================



#include "main.hpp"


#ifdef DEV_TOOLS

void ExportRawDataPathList(void)
{
#ifdef _WINDOWS_VERSION_

	FILE * outputFile = opakNull;

	CollectFiles("dds\\*", ".dds", opakDDSTexture);
	CollectFiles("raw\\sidewinder.imeta\\*", ".bin", opakRawTexture);

	SortStrings(collectedFiles, numCollectedFiles);

	OpakDeleteFile("out.txt");
	fopen_s(&outputFile, "out.txt", "w");
	if (outputFile)
	{
		if (collectedFiles)
		{
			for (unsigned int i = 0; i < numCollectedFiles; i++)
			{
				if (collectedFiles[i]->shortenedName)
				{
					fwrite(collectedFiles[i]->shortenedName, 1, strlen(collectedFiles[i]->shortenedName), outputFile);
					fwrite("\n", 1, 1, outputFile);
				}
			}
		}

		fclose(outputFile);
		outputFile = opakNull;
	}
#endif
}

#endif