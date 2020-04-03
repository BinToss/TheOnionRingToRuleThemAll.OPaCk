/*

Software written by TheOnionRingToRuleThemAll, formerly known as Adolif2, or DumdogsWorld.

No copy-and-paste license here. I like the internet to be like the wild west, which is a memory of days long gone.

Just give me credit, damn it.

*/

//===================================================================================



#include "main.hpp"


#ifndef RAWFILE_INCLUDE_ONCE
#define RAWFILE_INCLUDE_ONCE

class rawFile : public ddsFile
{
public:
	virtual void Deserialize(opakFileMode_t mode);
	virtual void Serialize(void);
	virtual bool IsRawEntry(void);
	rawFile(const ipakEntry_t * data);
	rawFile(const char * path);
	~rawFile();
};

#endif