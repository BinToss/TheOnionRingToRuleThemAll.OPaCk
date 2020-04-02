/*

Software written by TheOnionRingToRuleThemAll, formerly known as Adolif2, or DumdogsWorld.

No copy-and-paste license here. I like the internet to be like the wild west, which is a memory of days long gone.

Just give me credit, damn it.

*/

//===================================================================================



#include "main.hpp"

void SortStrings(ddsFile ** files, opakUInt64 count)
{
	WrappedQSsort(files, count, sizeof(opakFile *), CompareFunction);
}