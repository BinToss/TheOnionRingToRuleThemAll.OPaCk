/*

Software written by TheOnionRingToRuleThemAll, formerly known as Adolif2, or DumdogsWorld.

No copy-and-paste license here. I like the internet to be like the wild west, which is a memory of days long gone.

Just give me credit, damn it.

*/

//===================================================================================



#include "main.hpp"


#ifndef OFILE_INCLUDE_ONCE
#define OFILE_INCLUDE_ONCE

class opakFile
{
	char * path;
public:
	char * shortenedName;
	FILE * handle;
	virtual void Deserialize(opakFileMode_t mode);
	virtual void Serialize(void);
	opakFile(const char * srcPath);
	opakFile(const ipakEntry_t * data);
	opakFile(const char * srcFolderName, const char * fileName, bool createNew);
	opakFile(const char * srcFolderName, const char * fileName, opakFileMode_t mode, bool createNew);
	opakFile(const char * srcFolderName, const char * destFolderName, const char * fileName, opakFileMode_t mode);
	~opakFile();
};

#endif