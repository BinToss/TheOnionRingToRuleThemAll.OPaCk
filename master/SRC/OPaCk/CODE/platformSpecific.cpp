/*

Software written by TheOnionRingToRuleThemAll, formerly known as Adolif2, or DumdogsWorld.

No copy-and-paste license here. I like the internet to be like the wild west, which is a memory of days long gone.

Just give me credit, damn it.

*/

//===================================================================================



#include "main.hpp"


//Non-Windows support unimplemented, but I'll lay the groundwork for it

#ifdef _WINDOWS_VERSION_ //defined via Visual Studio project, not in code

bool OpakFileExists(const char * fileName)
{
	return PathFileExists(fileName);
}

void EnsureFolderExists(const char * folderName)
{
	CreateDirectory(folderName, opakNull);
}

void OpakDeleteFile(const char * fileName)
{
	DeleteFile(fileName);
}

bool OpakCopyFile(const char * srcFolderName, const char * destFolderName, const char * fileName, unsigned int outPathSize, char * outPath)
{
	char workingStrSrc[1024];
	char workingStrDest[1024];

	memset(workingStrSrc, 0, 1024);
	memset(workingStrDest, 0, 1024);

	sprintf_s(workingStrSrc, 1024, "%s\\%s", srcFolderName, fileName);
	sprintf_s(workingStrDest, 1024, "%s\\%s", destFolderName, fileName);

	OpakDeleteFile(workingStrDest);

	if (outPath && outPathSize)
	{
		strcpy_s(outPath, outPathSize, workingStrDest);
	}

	return CopyFile(workingStrSrc, workingStrDest, TRUE);
}

FILE * OpakFopen(const char * filename, const char * mode)
{
	FILE * handle = opakNull;
	fopen_s(&handle, filename, mode);
	return handle;
}

opakInt64 OpakFtell(FILE * handle)
{
	return _ftelli64(handle);
}

void OpakFseek(FILE * handle, opakInt64 offset, int origin)
{
	_fseeki64(handle, offset, origin);
}

void WrappedQSsort(ddsFile ** files, opakUInt64 count, int size, qsortFuncProto_t compareFunction)
{
	qsort_s(files, count, size, compareFunction, opakNull);
}

int CompareFunction(void * context, void const * aInVoid, void const * bInVoid)
{
	int returnValue = 0;

	ddsFile ** aIn = opakNull;
	ddsFile ** bIn = opakNull;
	std::string A;
	std::string B;

	if (aInVoid)
	{
		aIn = (ddsFile **)aInVoid;
		if (aIn[0]->shortenedName)
		{
			A = aIn[0]->shortenedName;
		}
		else
		{
			A = "";
		}
	} 
	else
	{
		A = "";
	}

	if (bInVoid)
	{
		bIn = (ddsFile **)bInVoid;
		if (bIn[0]->shortenedName)
		{
			B = bIn[0]->shortenedName;
		}
		else
		{
			B = "";
		}
	}
	else
	{
		B = "";
	}

	if (A < B)
	{
		returnValue = -1;
	}
	else if (A > B)
	{
		returnValue = 1;
	}

	return returnValue;
}

bool HasFileExtension(char * path, const char * extension)
{
	char * pathExtensionStart = opakNull;
	size_t pathLen = 0;
	size_t extensionLen = 0;

	if (!path)
	{
		return false;
	}
	if (!extension)
	{
		return false;
	}
	if (extension[0] != '.')
	{
		return false;
	}

	pathLen = strlen(path);
	extensionLen = strlen(extension);

	if (extensionLen >= pathLen)
	{
		return false;
	}

	pathExtensionStart = &path[pathLen - extensionLen];

	if (_strnicmp(pathExtensionStart, extension, extensionLen) == 0)
	{
		return true;
	}

	return false;
}

void NullFileExtension(char * path)
{
	size_t pathLen = 0;
	size_t pathExtensionLen = 0;
	char * pathExtensionStart = opakNull;

	if (!path)
	{
		return;
	}

	pathLen = strlen(path);

	for (size_t i = pathLen - 1; i >= 0; i--)
	{
		if (path[i] == '.')
		{
			pathExtensionStart = &path[i];
			break;
		}
	}

	if (pathExtensionStart)
	{
		pathExtensionLen = strlen(pathExtensionStart);
		memset(pathExtensionStart, 0, pathExtensionLen);
	}
}

void GeneratePrefix(const char * path, char * outBuffer)
{
	int count = 0;
	size_t len = 0;

	len = strlen(path);

	for (int i = 1; i < len; i++)
	{
		if (path[i - 1] == '\\')
		{
			outBuffer[count] = path[i];
			count++;
		}
	}

	if (count)
	{
		outBuffer[count - 1] = 0;
	}
}

bool GetNumericPortion(const char * fileName, char * outBuffer, int outBufferSize)
{
	size_t len = 0;
	char bitmapStr [9] = "_bitmap_";
	const char * comparePart = opakNull;
	const char * numericPortion = opakNull;
	char workingCopy[shortenedNameSize];
	int numericNum = 0;
	size_t i = 0;
	int compareResult = 0;

	len = strlen(fileName);

	memset(workingCopy, 0, shortenedNameSize);

	if (len <= 10)
	{
		return false;
	}

	for (i = len - 9; i > 0; i--)
	{
		comparePart = &fileName[i];
		compareResult = _strnicmp(comparePart, bitmapStr, 8);
		if (compareResult == 0)
		{
			numericPortion = &fileName[i + 8];
			memcpy(workingCopy, fileName, min(i, shortenedNameSize));
			break;
		}
	}

	if (!numericPortion)
	{
		return false;
	}

	numericNum = atoi(numericPortion);
	numericNum -= 1;
	numericNum = max(numericNum, 0);

	sprintf_s(outBuffer, outBufferSize, "%s%s%i", workingCopy, "_", numericNum);

	return true;
}

void ShortenName(const char * path, char * outBuffer, int outBufferSize)
{
	size_t outLen = 0;
	size_t pathLen = 0;
	size_t filenameLen = 0;
	const char * filenameStart = opakNull;
	char pathWorkingCopy [shortenedNameSize];
	char nameWorkingCopy [shortenedNameSize];
	char prefixWorkingCopy[shortenedNameSize];

	if (!path)
	{
		return;
	}
	if (!outBuffer)
	{
		return;
	}

	pathLen = strlen(path);

	memset(outBuffer, 0, shortenedNameSize);
	memset(nameWorkingCopy, 0, shortenedNameSize);
	memset(prefixWorkingCopy, 0, shortenedNameSize);

	memset(pathWorkingCopy, 0, shortenedNameSize);
	memcpy(pathWorkingCopy, path, pathLen);

	NullFileExtension(pathWorkingCopy);

	for (size_t i = pathLen - 1; i >= 1; i--)
	{
		if (path[i - 1] == '\\')
		{
			filenameStart = &pathWorkingCopy[i];
			break;
		}
	}

	if (filenameStart)
	{
		filenameLen = strlen(filenameStart);

		if (!GetNumericPortion(filenameStart, nameWorkingCopy, shortenedNameSize))
		{
			sprintf_s(nameWorkingCopy, shortenedNameSize, "%s%s", filenameStart, "_0");
		}

		GeneratePrefix(pathWorkingCopy, prefixWorkingCopy);

		sprintf_s(outBuffer, outBufferSize, "%s%s%s%s", "hce_", prefixWorkingCopy, "_", nameWorkingCopy);

		outLen = strlen(outBuffer);

		memset(&outBuffer[outLen], 0, outBufferSize - outLen);
	}
}

void CollectFilesIteration(const char * fileExtension, opakUInt64 * count, const char * directory, bool countingFiles, opakFileSubClass_t subclass)
{
	WIN32_FIND_DATA FindFileData;
	HANDLE hFind = 0;
	char workingString[4096];
	ddsFile * ddsToCopy = opakNull;

	if (!fileExtension)
	{
		return;
	}
	if (!count)
	{
		return;
	}

	if ((!countingFiles) && (!collectedFiles))
	{
		return;
	}

	hFind = FindFirstFile(directory, &FindFileData);
	if (hFind == INVALID_HANDLE_VALUE) {
		ErrorMessage("FindFirstFile failed.");
		return;
	}

	do {
		if (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			if ((_stricmp(".", FindFileData.cFileName) != 0) &&
				(_stricmp("..", FindFileData.cFileName) != 0))
			{
				size_t dLen = 0;
				size_t sLen = 0;

				memset(workingString, 0, 4096);

				dLen = strlen(directory) - 1;
				sLen = strlen(FindFileData.cFileName);

				memcpy(workingString, directory, dLen);				

				memcpy(&workingString[dLen], FindFileData.cFileName, sLen);
				workingString[dLen + sLen] = '\\';
				workingString[dLen + sLen + 1] = '*';

				CollectFilesIteration(fileExtension, count, workingString, countingFiles, subclass);
			}
		} 
		else
		{
			if (HasFileExtension(FindFileData.cFileName, fileExtension))
			{
				if (!countingFiles)
				{
					size_t dLen = 0;
					size_t sLen = 0;

					memset(workingString, 0, 4096);

					dLen = strlen(directory) - 1;
					sLen = strlen(FindFileData.cFileName);

					memcpy(workingString, directory, dLen);

					memcpy(&workingString[dLen], FindFileData.cFileName, sLen);

					if (subclass == opakDDSTexture)
					{		
						ddsToCopy = new ddsFile(workingString, false);
						collectedFiles[*count] = ddsToCopy;
						*count += 1;
					} 
					else if (subclass == opakRawTexture)
					{
						collectedFiles[*count] = new rawFile(workingString);
						*count += 1;
					}
				}
				else
				{
					*count += 1;
				}
			}
		}
	} while (FindNextFile(hFind, &FindFileData) != 0);
	
	FindClose(hFind);
	hFind = 0;
}

void CollectFiles(const char * directory, const char * fileExtension, opakFileSubClass_t subclass)
{
	opakUInt64 i = 0;
	opakUInt64 count = 0;
	opakUInt64 oldCount = 0;

	oldCount = numCollectedFiles;
	count = numCollectedFiles;

	CollectFilesIteration(fileExtension, &count, directory, true, subclass);

	if (!collectedFiles)
	{
		collectedFiles = (ddsFile **)malloc(sizeof(ddsFile *) * count);
		memset(collectedFiles, 0, sizeof(ddsFile *) * count);
	}
	else
	{
		opakUInt64 N = count - oldCount;

		collectedFiles = (ddsFile **)realloc(collectedFiles, sizeof(ddsFile *) * count);
		memset(&collectedFiles[oldCount], 0, sizeof(ddsFile *) * N);
	}

	i = oldCount;
	CollectFilesIteration(fileExtension, &i, directory, false, subclass);

	numCollectedFiles = count;
}

void CollectFilesFromBin(FILE * binFile, int entryCount, opakFileSubClass_t subclass)
{
	opakInt64 count = 0;
	opakInt64 oldCount = 0;
	ipakEntry_t entry;
	opakUInt64 startOffset = 0;

	oldCount = numCollectedFiles;

	count = entryCount + numCollectedFiles;
	startOffset = 8;

	opakInt64 N = count - oldCount;

	collectedFiles = (ddsFile **)realloc(collectedFiles, sizeof(ddsFile *) * count);
	memset(&collectedFiles[oldCount], 0, sizeof(ddsFile *) * N);

	OpakFseek(binFile, startOffset, SEEK_SET);

	for (opakInt64 i = oldCount; i < count; i++)
	{
		fread(&entry, 1, ipakEntrySize, binFile);
		collectedFiles[i] = new rawFile(&entry);
	}

	numCollectedFiles = count;
}

void GatherTextures(opakImeta * imeta2)
{
	FILE * outputFile = opakNull;

	CollectFiles("dds\\*", ".dds", opakDDSTexture);
	CollectFilesFromBin(imeta2->handle, imeta2->entryCount1, opakRawTexture);

	SortStrings(collectedFiles, numCollectedFiles);
}

#else

//....

#endif