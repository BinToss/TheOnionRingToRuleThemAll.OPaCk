/*

Software written by TheOnionRingToRuleThemAll, formerly known as Adolif2, or DumdogsWorld.

No copy-and-paste license here. I like the internet to be like the wild west, which is a memory of days long gone.

Just give me credit, damn it.

*/

//===================================================================================



#include "main.hpp"

opakUInt64 numCollectedFiles = 0;
ddsFile ** collectedFiles = opakNull;

void CleanUpCollectedFiles(void)
{
	if (collectedFiles)
	{
		for (unsigned int i = 0; i < numCollectedFiles; i++)
		{
			if (collectedFiles[i])
			{
				delete collectedFiles[i];
				collectedFiles[i] = opakNull;
			}
		}
		free(collectedFiles);
		collectedFiles = opakNull;
	}

	numCollectedFiles = 0;
}

