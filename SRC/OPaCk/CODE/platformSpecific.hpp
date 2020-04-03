/*

Software written by TheOnionRingToRuleThemAll, formerly known as Adolif2, or DumdogsWorld.

No copy-and-paste license here. I like the internet to be like the wild west, which is a memory of days long gone.

Just give me credit, damn it.

*/

//===================================================================================



#ifndef PLATFORMSPECIFIC_INCLUDE_ONCE
#define PLATFORMSPECIFIC_INCLUDE_ONCE

//Non-Windows support unimplemented, but I'll lay the groundwork for it

#ifdef _WINDOWS_VERSION_ //defined via Visual Studio project, not in code

#define WINVER 0x0600
#define _WIN32_WINNT 0x0600

#include <iostream>
#include <Windows.h>
#include "Shlwapi.h"
#include <string>

#define opakNull __nullptr

typedef unsigned __int8 opakByte;
typedef __int16 opakInt16;
typedef unsigned __int16 opakUInt16;
typedef __int32 opakInt32;
typedef unsigned __int32 opakUInt32;
typedef __int64 opakInt64;
typedef unsigned __int64 opakUInt64;

typedef _CoreCrtSecureSearchSortCompareFunction qsortFuncProto_t;

#else

//....

#endif

bool OpakFileExists(const char * fileName);
void EnsureFolderExists(const char * folderName);
void OpakDeleteFile(const char * fileName);
bool OpakCopyFile(const char * srcFolderName, const char * destFolderName, const char * fileName, unsigned int outPathSize, char * outPath);
FILE * OpakFopen(const char * filename, const char * mode);
opakInt64 OpakFtell(FILE * handle);
void OpakFseek(FILE * handle, opakInt64 offset, int origin);
void WrappedQSsort(ddsFile ** files, opakUInt64 count, int size, qsortFuncProto_t compareFunction);
int CompareFunction(void * context, void const * aIn, void const * bIn);
bool HasFileExtension(char * path, const char * extension);
void ShortenName(const char * path, char * outBuffer, int outBufferSize);
void CollectFiles(const char * directory, const char * fileExtension, opakFileSubClass_t subclass);
void CollectFilesFromBin(FILE * binFile, int entryCount, opakFileSubClass_t subclass);
void GatherTextures(opakImeta * imeta2);

#endif
