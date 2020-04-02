/*

Software written by TheOnionRingToRuleThemAll, formerly known as Adolif2, or DumdogsWorld.

No copy-and-paste license here. I like the internet to be like the wild west, which is a memory of days long gone.

Just give me credit, damn it.

*/

//===================================================================================



#ifndef MAIN_INCLUDE_ONCE
#define MAIN_INCLUDE_ONCE

#define DEV_TOOLS //Program functionality for use in helping to write this program. Should normally be disabled.

class opakFile;
class ddsFile;
class opakImeta;
class opakIpak;
enum opakFileSubClass_t;

#include "platformSpecific.hpp"
#include "definitions.hpp"
#include "devTools.hpp"
#include "ofile.hpp"
#include "imeta.hpp"
#include "ipak.hpp"
#include "ddsFile.hpp"
#include "rawFile.hpp"
#include "globalVariables.hpp"
#include "stringSort.hpp"
#include "entryTemplate.hpp"
#include "tcipHeader.hpp"
#include "decompressDxt.hpp"

void ErrorMessage(const char * msg);

#endif