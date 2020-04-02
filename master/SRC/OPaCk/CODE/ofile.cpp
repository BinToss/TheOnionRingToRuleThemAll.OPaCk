/*

Software written by TheOnionRingToRuleThemAll, formerly known as Adolif2, or DumdogsWorld.

No copy-and-paste license here. I like the internet to be like the wild west, which is a memory of days long gone.

Just give me credit, damn it.

*/

//===================================================================================



#include "main.hpp"


void opakFile::Deserialize(opakFileMode_t mode)
{
}

void opakFile::Serialize(void)
{
}

opakFile::opakFile(const char * srcFolderName, const char * destFolderName, const char * fileName, opakFileMode_t mode)
{
	shortenedName = opakNull;
	path = new char[1024];
	memset(path, 0, 1024);
	handle = opakNull;

	if (!OpakCopyFile(srcFolderName, destFolderName, fileName, 1024, path))
	{
		printf("\n\n"
			"=========\n"
			"Error when copying file ");
		printf(fileName);
		printf(" from directory ");
		printf(srcFolderName);
		printf(" to directory ");
		printf(destFolderName);
		printf("\n=========\n"
			"Program will abort.\n\n");

		CleanUpCollectedFiles();
		exit(5);
	}

	handle = OpakFopen(path, "rb+");

	if (!handle)
	{
		OpakDeleteFile(path);

		printf("\n\n"
			"=========\n"
			"Error when opening file ");
		printf(fileName);
		printf(" from directory ");
		printf(srcFolderName);
		printf("\n=========\n"
			"Program will abort.\n\n");

		CleanUpCollectedFiles();
		exit(6);
	}
}

opakFile::opakFile(const char * srcFolderName, const char * fileName, bool createNew)
{
	shortenedName = opakNull;
	path = new char[1024];
	memset(path, 0, 1024);

	if (srcFolderName && fileName)
	{
		size_t slen = strlen(srcFolderName);

		memcpy(path, srcFolderName, slen);
		memcpy(&path[slen], fileName, strlen(fileName));
	}

	if (!createNew)
	{
		handle = OpakFopen(path, "rb+");
	}
	else
	{
		OpakDeleteFile(path);
		handle = OpakFopen(path, "wb+");
	}

	if (!handle)
	{
		printf("\n\n"
			"=========\n"
			"Error when opening file ");
		printf(fileName);
		printf(" from directory ");
		printf(srcFolderName);
		printf("\n=========\n"
			"Program will abort.\n\n");

		CleanUpCollectedFiles();
		exit(4);
	}
}

opakFile::opakFile(const char * srcFolderName, const char * fileName, opakFileMode_t mode, bool createNew) : opakFile(srcFolderName, fileName, createNew)
{
}

opakFile::opakFile(const ipakEntry_t * data)
{
	int errCode = 0;

	shortenedName = opakNull;
	path = opakNull;

	handle = opakNull;
	errCode = errno;
}

opakFile::opakFile(const char * srcPath)
{
	shortenedName = opakNull;
	path = new char[1024];
	memset(path, 0, 1024);

	if (srcPath)
	{
		memcpy(path, srcPath, strlen(srcPath));
	}

	handle = OpakFopen(path, "rb");

	if (!handle)
	{
		printf("\n\n"
			"=========\n"
			"Error when opening file from path ");
		printf(srcPath);
		printf("\n=========\n"
			"Program will abort.\n\n");

		CleanUpCollectedFiles();
		exit(3);
	}
}

opakFile::~opakFile()
{
	if (shortenedName)
	{
		delete[] shortenedName;
		shortenedName = opakNull;
	}
	if (path)
	{
		delete[] path;
		path = opakNull;
	}
	if (handle)
	{
		fclose(handle);
		handle = opakNull;
	}
}