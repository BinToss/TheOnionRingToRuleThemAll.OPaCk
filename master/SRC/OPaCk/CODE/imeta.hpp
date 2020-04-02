/*

Software written by TheOnionRingToRuleThemAll, formerly known as Adolif2, or DumdogsWorld.

No copy-and-paste license here. I like the internet to be like the wild west, which is a memory of days long gone.

Just give me credit, damn it.

*/

//===================================================================================



#include "main.hpp"


#ifndef IMETA_INCLUDE_ONCE
#define IMETA_INCLUDE_ONCE

class opakImeta : public opakFile
{
public:
	opakUInt64 header;
	opakUInt32 entryCount1;
	ipakEntry_t * entries;
	virtual void Deserialize(opakFileMode_t mode);
	virtual void Serialize(void);
	virtual void Serialize(opakIpak * ipak1, opakImeta * imeta2);
	opakImeta(const char * srcFolderName, const char * fileName, opakFileMode_t mode, bool createNew);
	opakImeta(const char * srcFolderName, const char * destFolderName, const char * fileName, opakFileMode_t mode);
	~opakImeta();
};

#endif