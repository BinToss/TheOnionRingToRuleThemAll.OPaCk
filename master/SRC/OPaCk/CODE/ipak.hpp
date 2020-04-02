/*

Software written by TheOnionRingToRuleThemAll, formerly known as Adolif2, or DumdogsWorld.

No copy-and-paste license here. I like the internet to be like the wild west, which is a memory of days long gone.

Just give me credit, damn it.

*/

//===================================================================================



#include "main.hpp"


#ifndef IPAK_INCLUDE_ONCE
#define IPAK_INCLUDE_ONCE

class opakIpak : public opakImeta
{
public:
	opakUInt64 originalSize;
	virtual void Serialize(void);
	void AppendTexture(ddsFile * tex);
	void Pad(opakUInt64 greaterSize);
	void PosPad(void);
	opakUInt64 PosTell(void);
	opakIpak(const char * srcFolderName, const char * destFolderName, const char * fileName, opakFileMode_t mode);
	~opakIpak();
};

#endif