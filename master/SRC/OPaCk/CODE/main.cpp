/*

Software written by TheOnionRingToRuleThemAll, formerly known as Adolif2, or DumdogsWorld.

No copy-and-paste license here. I like the internet to be like the wild west, which is a memory of days long gone.

Just give me credit, damn it.

*/

//===================================================================================



#include "main.hpp"

void ErrorMessage(const char * msg)
{
	printf("\n\n"
		"=========\n"
		"ERROR!\n\n");
	printf(msg);
	printf("\n\n");
	printf("\n=========\n"
		"Program will abort.\n\n");

	CleanUpCollectedFiles();

	exit(1);
}

void Rebuild(const char * fname, opakImeta * imeta1, opakImeta * imeta2, opakIpak * ipak1)
{
	opakInt64 paddedSize = 0;

	GatherTextures(imeta2);

	paddedSize = ipak1->originalSize;
	paddedSize -= paddedSize % 16;
	paddedSize += 16;

	ipak1->Pad(paddedSize);

	if (imeta1 && imeta2)
	{
		imeta1->header = imeta2->header;

		imeta1->Serialize(ipak1, imeta2);

		printf("\n\nDone!\n\n");
	}
}

int main(int argc, char * argv[])
{
	opakIpak * ipak1 = opakNull;
	opakImeta * imeta1 = opakNull;
	opakImeta * imeta2 = opakNull;

	if (argc < 2)
	{
		printf("\n\n"
			"=========\n");
		printf("Program requires 1 parameter. The name (not path) of the imeta, including file extension.\n\n");
		printf("For example:\n\n");
		printf("OpAcK.exe sidewinder.imeta\n\n");
		printf("Make sure that your imeta is in the unmodded folder, as well as inplace1.uipak.\n\n");
		printf("\n=========\n");

		return 0;
	}

	EnsureFolderExists("dds");
	EnsureFolderExists("unmodded");
	EnsureFolderExists("rebuilt");

	ipak1 = new opakIpak("unmodded", "rebuilt", "inplace1.uipak", opakFileModeIpak);

#ifdef DEV_TOOLS
	//GenerateNamePrefixList(ipak1, ipak2);
	//ExportRawDataPathList();
#endif

	imeta1 = new opakImeta("rebuilt/", argv[1], opakFileModeImeta, true);

	imeta2 = new opakImeta("unmodded/", argv[1], opakFileModeImeta, false);

	Rebuild("sidewinder.imeta", imeta1, imeta2, ipak1);

	if (ipak1)
	{
		delete ipak1;
		ipak1 = opakNull;
	}
	if (imeta1)
	{
		delete imeta1;
		imeta1 = opakNull;
	}
	if (imeta2)
	{
		delete imeta2;
		imeta2 = opakNull;
	}

	CleanUpCollectedFiles();

	return 0;
}