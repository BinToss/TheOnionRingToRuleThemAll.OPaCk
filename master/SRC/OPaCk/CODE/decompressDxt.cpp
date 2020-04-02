/*

Software written by TheOnionRingToRuleThemAll, formerly known as Adolif2, or DumdogsWorld.

No copy-and-paste license here. I like the internet to be like the wild west, which is a memory of days long gone.

Just give me credit, damn it.

*/

//===================================================================================



#include "main.hpp"
#include <libSquish\squish.h>

void DecompressDxt(unsigned char * uncompressedBuffer, unsigned char * compressedBuffer, int width, int height, int dxtType)
{
	int flags = 0;

	if (dxtType == dxt1)
	{
		flags = squish::kDxt1;
	}
	if (dxtType == dxt3)
	{
		flags = squish::kDxt3;
	}
	if (dxtType == dxt5)
	{
		flags = squish::kDxt5;
	}
	squish::DecompressImage(uncompressedBuffer, width, height, compressedBuffer, flags);
}